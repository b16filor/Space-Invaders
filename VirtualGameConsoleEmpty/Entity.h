#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY
#include "VGCVirtualGameConsole.h"
class Entity {
public:
	virtual ~Entity();
	virtual void draw() const = 0;
	virtual void update() = 0;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
protected:
	double x, y;
	int width, height;
	VGCImage image;
};
#endif