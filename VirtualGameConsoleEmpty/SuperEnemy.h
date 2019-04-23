#ifndef INCLUDED_SUPERENEMY
#define INCLUDED_SUPERENEMY
#include "Enemy.h"
class SuperEnemy : public Enemy {
public:
	SuperEnemy();
	~SuperEnemy();
	Projectile* shoot();
	bool readyToShoot();
};
#endif
