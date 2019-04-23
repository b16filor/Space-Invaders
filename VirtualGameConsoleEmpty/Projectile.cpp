#include "VGCVirtualGameConsole.h"
#include "Projectile.h"

Projectile::Projectile(int x, int y, int speedX, int speedY):
speedX(speedX), speedY(speedY), damage(1){
	this->x = x;
	this->y = y;
	width = 8;
	height = 8;
	image = VGCDisplay::openImage("Bullet.png", 1, 1);
}

Projectile::~Projectile(){}

void Projectile::update() {
	x += speedX;
	y += speedY;
}

void Projectile::draw() const {
	VGCDisplay::renderImage(image, VGCVector(0, 0), VGCVector(x, y), VGCAdjustment(0, 0));
}

int Projectile::getDamage() const {
	return damage;
}