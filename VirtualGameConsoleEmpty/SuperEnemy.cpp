#include "SuperEnemy.h"

SuperEnemy::SuperEnemy()
{
	shotInterval = 0;
	width = 32;
	height = 32;
	x = rand() % (int)(VGCDisplay::getWidth() - width);
	y = -width;
	damage = 3;
	speedX = (double)(rand() % 5 - 2) / 4;
	speedY = ((double)(rand() % 5 + 1) / 20);
	image = VGCDisplay::openImage("SuperInvader.png", 1, 1);
}

SuperEnemy::~SuperEnemy(){}

bool SuperEnemy::readyToShoot() {
	if (shotInterval == 0) {
		shotInterval = 20;
		return true;
	}
	return false;
}

Projectile* SuperEnemy::shoot() {
	return new Projectile(x + width / 2, y + height, 0, 5);
}