#ifndef DEF_PLAYER
#define DEF_PLAYER
#include <vector>
#include "Projectile.h"
#include "Entity.h"

class Ship : public Entity{
public:
	Ship();
	~Ship();
	int getHealth() const;
	void setHealth(const int h);
	std::vector<Projectile*> &getShots();
	void draw() const;
	void update();
private:
	double speed;
	int shotInterval, health;
	enum Direction
	{
		LEFT, RIGHT, UP, DOWN
	};
	std::vector<Projectile*> shots;
	int maxMove(int speed, Direction direction);
};
#endif 