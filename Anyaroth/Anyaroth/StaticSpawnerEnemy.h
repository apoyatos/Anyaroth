#pragma once
#include "Enemy.h"
class StaticSpawnerEnemy : public Enemy
{
private:
	bool _spawning = false, _activated = false;
	double _spawnTime = 3000, maxEnemies= 4, currentEnemies=0;
	vector<Enemy*> enemies;
public:
	StaticSpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual ~StaticSpawnerEnemy() { enemies.clear(); };
	virtual void update(double time);
	int activeEnemies();
};

