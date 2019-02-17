#pragma once
#include "GameComponent.h"

class Player;

class Enemy : public GameComponent
{
private:
	int life;
public:
	Enemy(Texture* texture,Vector2D posIni, Player* player, Game* g);
	virtual ~Enemy();

	void update();
};