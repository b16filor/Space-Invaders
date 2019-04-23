#ifndef DEF_GAME
#define DEF_GAME
#include "VGCVirtualGameConsole.h"
#include "Entity.h"
#include "Ship.h"
#include "Enemy.h"
#include "Explosion.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include "SuperEnemy.h"
using namespace std;
class Game {
private:
	Ship *ship;
	vector<Enemy*> enemies;
	vector<Projectile*> enemyShots;
	vector<Explosion*> explosions;
	VGCColor uiColor;
	unsigned int score = 0;
	unsigned int wave = 0;
	void drawGame() const;
	void update();
	void destoyObjects();
	void restart();
public:
	Game(int screenWidth, int screenHeight);
	~Game();
};
#endif 