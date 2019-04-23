#include "VGCVirtualGameConsole.h"
#include "Enemy.h"

Enemy::Enemy() : 
shotInterval(0), damage(2){
	width = 32;
	height = 32;
	x = rand() % (int)(VGCDisplay::getWidth() - width);
	y = -width;
	speedX = (double)(rand() % 5 - 2)/ 2;
	speedY = ((double)(rand() % 5 + 1) / 10);
	image = VGCDisplay::openImage("Invader.png", 1, 1);
}

Enemy::~Enemy(){

}

void Enemy::update() {
	x += speedX;
	y += speedY;
	if (x + width >= VGCDisplay::getWidth() || x <= 0)
		speedX *= -1;
	if (shotInterval > 0) 
		shotInterval--;
}

bool Enemy::readyToShoot() {
	if (shotInterval == 0) {
		shotInterval = 100;
		return true;
	}
	return false;
}

Projectile* Enemy::shoot() {
	return new Projectile(x + width / 2, y + height, 0, 3);
}

bool Enemy::reachedEnd(Ship *ship) {
	if (y > VGCDisplay::getHeight()) {
		ship->setHealth(ship->getHealth() - 1);
		return true;
	}
	return false;
}

bool Enemy::collision(Ship *ship, std::vector<Projectile*> &shots, unsigned int &score, unsigned int wave) {
	for (std::vector<Projectile*>::iterator i = shots.begin(); i != shots.end(); i++) {
		if ((*i)->getX() + (*i)->getWidth() > x && (*i)->getX() < x + width && (*i)->getY()
			+ (*i)->getHeight() > y && (*i)->getY() < y + width) {
			delete (*i);
			i = shots.erase(i);
			score += 10 * wave;
			return true;
		}
	}
	if (ship->getX() + ship->getWidth() > x && ship->getX() < x + width && ship->getY()
		+ ship->getHeight() > y && ship->getY() < y + width) {
		ship->setHealth(ship->getHealth() - damage);
		return true;
	}
	return false;
}

void Enemy::draw() const {
	VGCDisplay::renderImage(image, VGCVector(0, 0), VGCVector(x, y), VGCAdjustment(0, 0));
}