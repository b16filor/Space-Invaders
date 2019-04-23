#include "Ship.h"
#include "VGCVirtualGameConsole.h"
#include <vector>

Ship::Ship():
speed(7), health(20), shotInterval(0){
	width = 32;
	height = 32;
	this->x = VGCDisplay::getWidth() / 2 - width / 2;
	this->y = VGCDisplay::getHeight() - height;
	image = VGCDisplay::openImage("Ship.png", 1, 1);
}

Ship::~Ship() {
	for (std::vector<Projectile*>::iterator i = shots.begin(); i != shots.end();) {
		delete *i;
		i = shots.erase(i);
	}
}

int Ship::getHealth() const {
	return health;
}

void Ship::setHealth(const int h) {
	health = h;
}

std::vector<Projectile*> &Ship::getShots() {
	return shots;
}

void Ship::draw() const {
	VGCDisplay::renderImage(image, VGCVector(0, 0), VGCVector(x, y), VGCAdjustment(0, 0));
	for (int i = 0; i < shots.size(); i++)
		shots.at(i)->draw();
}

int Ship::maxMove(int speed, Direction direction) {
	if (direction == UP && y - speed >= 0) {
		return speed;
	}
	if (direction == LEFT && x - speed >= 0) {
		return speed;
	}
	if (direction == RIGHT && x + speed + width <= VGCDisplay::getWidth()) {
		return speed;
	}
	if (direction == DOWN && y + speed + height <= VGCDisplay::getHeight()) {
		return speed;
	}
	return maxMove(speed - 1, direction);
}

void Ship::update() {
	if (VGCKeyboard::isPressed(VGCKey::SPACE_KEY) && shotInterval == 0) {
		Projectile *projectile1 = new Projectile(x + width / 2, y, 0, -5);
		shots.push_back(projectile1);
		Projectile *projectile2 = new Projectile(x + width / 2, y, -1, -5);
		shots.push_back(projectile2);
		Projectile *projectile3 = new Projectile(x + width / 2, y, 1, -5);
		shots.push_back(projectile3);
		shotInterval = 50;
	}
	if (shotInterval > 0) {
		shotInterval--;
	}
	if (VGCKeyboard::isPressed(VGCKey::W_KEY) )
		y -= maxMove(speed, UP);
	if (VGCKeyboard::isPressed(VGCKey::A_KEY))
		x -= maxMove(speed, LEFT);
	if (VGCKeyboard::isPressed(VGCKey::D_KEY))
		x += maxMove(speed, RIGHT);
	if (VGCKeyboard::isPressed(VGCKey::S_KEY))
		y += maxMove(speed, DOWN);
	for (std::vector<Projectile*>::iterator i = shots.begin(); i != shots.end();) {
		if ((*i)->getY() < 0) {
			delete (*i);
			i = shots.erase(i);
		}
		else
			i++;
	}
	for (int i = 0; i < shots.size(); i++) {
		shots.at(i)->update();
	}
		
}