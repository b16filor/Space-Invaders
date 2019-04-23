#ifndef DEF_PROJECTILE
#define DEF_PROJECTILE
#include "Entity.h"
class Projectile : public Entity{
private:
	int speedX, speedY, damage;
public:
	Projectile(int x, int y, int speedX, int speedY);
	~Projectile();
	void update();
	void draw() const;
	int getDamage() const;
};
#endif 