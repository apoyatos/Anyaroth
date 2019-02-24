#include "PlayState.h"
#include "Game.h"
#include "BodyComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"
#include "Coin.h"

PlayState::PlayState(Game* g) : GameState(g)
{
	//Tilemap

	_colLayer = new Layer("Capa de Patrones 1", g->getTexture("tileset"), TILEMAP_PATH + "level.json", g, "Suelo");
	_colLayer->addComponent<BodyComponent>();
	_stages.push_back(_colLayer);

	

	//cuerpo
	_player = new Player(g->getTexture("Mk"), g, "Player");
	_stages.push_back(_player);

	_mainCamera->fixCameraToObject(_player);

	//Enemy
	/*_enemy = new Enemy(_player, g, g->getTexture("Mk"), Vector2D(50, 10), "Enemy");
	_stages.push_back(_enemy);*/

	Coin* coin = new Coin(this, g, g->getTexture("Coin"), Vector2D(100, 75), 20);
	_stages.push_back(coin);

	auto itFR = --(_stages.end());
	coin->setItList(itFR);

	_enemy = new MartyrEnemy(_player, g, this, g->getTexture("Mk"), Vector2D(50, 100));
	_stages.push_back(_enemy);

	itFR = --(_stages.end());
	_enemy->setItList(itFR);
}

void PlayState::KillObject(list<GameObject*>::iterator itList)
{
	items_ToDelete.push_back(itList);
}


void PlayState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PlayState::update()
{
	GameState::update();

	int i = items_ToDelete.size() - 1;
	while (i >= 0)
	{
		delete *items_ToDelete[i];
		_stages.erase(items_ToDelete[i]);
		items_ToDelete.pop_back();
		i--;
	}
}