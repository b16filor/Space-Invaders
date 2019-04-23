#include "Explosion.h"
#include "VGCVirtualGameConsole.h"

Explosion::Explosion(int x, int y, int width, int height) :
exploded(false), explosionTime(100){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	image = VGCDisplay::openImage("Explosion.png", 1, 1);
}

Explosion::~Explosion() {

}

void Explosion::update() {
	if (explosionTime <= 0)
		exploded = true;
	else
		explosionTime--;
}

void Explosion::draw() const {
	VGCDisplay::renderImage(image, VGCVector(0, 0), VGCVector(x, y), VGCAdjustment(0, 0));
}

bool Explosion::doneExploding() {
	return exploded;
}

