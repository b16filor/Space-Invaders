#include "Game.h"



Game::Game(int screenWidth, int screenHeight) {
	VGCVirtualGameConsole::initialize("Invaders", screenWidth, screenHeight);
	uiColor = VGCColor(255, 255, 65, 0);
	srand(GetTickCount());
	ship = new Ship();
	update();
}

Game::~Game(){}

void Game::drawGame() const {
	VGCDisplay::beginFrame();
	VGCColor color = VGCColor(255, 0, 0, 0);
	VGCDisplay::clear(color);
	ship->draw();
	for (int i = 0; i < explosions.size(); i++)
		explosions.at(i)->draw();
	for (int i = 0; i < enemies.size(); i++)
		enemies.at(i)->draw();
	for (int i = 0; i < enemyShots.size(); i++)
		enemyShots.at(i)->draw();
	if(ship->getHealth() < 1)
		VGCDisplay::renderString(VGCDisplay::openFont("Times New Roman", 20), "Game over!\nPress enter to restart.",
			uiColor, VGCVector(VGCDisplay::getWidth() / 2 - 100, VGCDisplay::getHeight() / 2), VGCAdjustment(0.0, 0.0));
	VGCDisplay::renderString(VGCDisplay::openFont("Times New Roman", 20), "Score: " + to_string(score),
		uiColor, VGCVector(10, 10), VGCAdjustment(0.0, 0.0));
	VGCDisplay::renderString(VGCDisplay::openFont("Times New Roman", 20), "Life: " + to_string(ship->getHealth()),
		uiColor, VGCVector(VGCDisplay::getWidth() - 100, 10), VGCAdjustment(0.0, 0.0));
	VGCDisplay::renderString(VGCDisplay::openFont("Times New Roman", 20), "Wave: " + to_string(wave),
		uiColor, VGCVector(VGCDisplay::getWidth() / 2, 10), VGCAdjustment(0.0, 0.0));
	VGCDisplay::endFrame();
}

void Game::destoyObjects() {
	for (vector<Explosion*>::iterator i = explosions.begin(); i != explosions.end();) {
		if ((*i)->doneExploding()) {
			delete *i;
			i = explosions.erase(i);
		}
		else
			i++;
	}
	for (vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();) {
		if ((*i)->reachedEnd(ship) || (*i)->collision(ship, ship->getShots(), score, wave)) {
			explosions.push_back(new Explosion((*i)->getX(), (*i)->getY(), (*i)->getWidth(),
				(*i)->getHeight()));
			delete *i;
			i = enemies.erase(i);
		}
		else
			i++;
	}

	for (vector<Projectile*>::iterator i = enemyShots.begin(); i != enemyShots.end();) {
		if (ship->getX() + ship->getWidth() > (*i)->getX() && ship->getX() < (*i)->getX() + (*i)->getWidth() && ship->getY()
			+ ship->getHeight() > (*i)->getY() && ship->getY() < (*i)->getY() + (*i)->getHeight()) {
			ship->setHealth(ship->getHealth() - (*i)->getDamage());
			delete (*i);
			i = enemyShots.erase(i);
		}
		else if ((*i)->getY() > VGCDisplay::getHeight()) {
			delete (*i);
			i = enemyShots.erase(i);
		}
		else
			i++;
	}
}

void Game::update() {
	VGCTimer timer = VGCClock::openTimer(1.0 / 85);
	VGCTimer spawnTimer = VGCClock::openTimer(0.5);
	int spawnsLeft = 0;
	while (VGCVirtualGameConsole::beginLoop())
	{
		VGCClock::reset(timer);
		if (ship->getHealth() > 0) {
			if (enemies.size() == 0 && spawnsLeft == 0) {
				wave++;
				spawnsLeft = 5 + wave * 5;
				for(int i = 0; i < wave; i++)
					enemies.push_back(new SuperEnemy());
			}
			if (VGCClock::isExpired(spawnTimer) && spawnsLeft != 0) {
				enemies.push_back(new Enemy());
				spawnsLeft--;
				VGCClock::reset(spawnTimer);
			}

			ship->update();
			for (int i = 0; i < explosions.size(); i++)
				explosions.at(i)->update();
			for (int i = 0; i < enemies.size(); i++){
				enemies.at(i)->update();
				if (enemies.at(i)->readyToShoot())
					enemyShots.push_back(enemies.at(i)->shoot());
			}
			for (int i = 0; i < enemyShots.size(); i++)
				enemyShots.at(i)->update();
			destoyObjects();
		}
		else {
			if (VGCKeyboard::isPressed(VGCKey::RETURN_KEY)) {
 				restart();
			}
			
			
		}
		
		drawGame();
		VGCVirtualGameConsole::endLoop();
		VGCClock::wait(timer);
		
	}
}


void Game::restart() {
	delete ship;
	for (vector<Explosion*>::iterator i = explosions.begin(); i != explosions.end();) {
		delete *i;
		i = explosions.erase(i);
	}
	for (vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();) {
		delete *i;
		i = enemies.erase(i);
	}
	for (vector<Projectile*>::iterator i = enemyShots.begin(); i != enemyShots.end();) {
		delete *i;
		i = enemyShots.erase(i);
	}
	score = 0;
	wave = 0;
	ship = new Ship();
}