#ifndef DEF_EXPLOSION
#define DEF_EXPLOSION
#include "Entity.h"
class Explosion : public Entity {
public:
	Explosion(int x, int y, int width, int height);
	~Explosion();
	void draw() const;
	void update();
	bool doneExploding();
private:
	int explosionTime;
	bool exploded;
};
#endif