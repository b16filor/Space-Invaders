#ifndef DEF_ENEMY
#define DEF_ENEMY
#include "Ship.h"
#include "Projectile.h"
#include "Entity.h"
#include <vector>
class Enemy : public Entity{
protected:
	double speedY, speedX;
	int shotInterval, damage;
public:
	Enemy();
	virtual ~Enemy();
	void update();
	bool reachedEnd(Ship *ship);
	void draw() const;
	virtual Projectile* shoot();
	virtual bool readyToShoot();
	bool collision(Ship *ship, std::vector<Projectile*> &shots, unsigned int &score, unsigned int wave);
};

#endif 

