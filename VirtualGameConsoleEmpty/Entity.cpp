#include "Entity.h"

Entity::~Entity() {

}

int Entity::getX() const {
	return x;
}

int Entity::getY() const {
	return y;
}

int Entity::getWidth() const {
	return width;
}

int Entity::getHeight() const {
	return height;
}