﻿#include "Map.h"
#include "BodyComponent.h"
#include "MeleeEnemy.h"
#include "MartyrEnemy.h"
#include "DistanceStaticEnemy.h"
#include "StaticFlyingEnemy.h"
#include "DistanceDynamicEnemy.h"
#include "BomberEnemy.h"
#include "NormalSpawner.h"
#include "DistanceSpawner.h"
#include "StaticSpawnerEnemy.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Player.h"
#include "NPC.h"
#include "Shop.h"
#include "MissileTurret.h"
#include "SpawnerBoss.h"
#include "FloatingHead.h"
#include <json.hpp>

using namespace nlohmann;

Map::Map(string filename, Game* game, Player* player, Texture* tileset, BulletPool* bulletPool) : GameObject(game), _player(player), _bulletPool(bulletPool)
{
	_tilemap = new Tilemap(game, tileset);
	_tilemap->loadTileMap(filename);
	addChild(_tilemap);

	_objects = new GameObject(_game);
	addChild(_objects);

	json j;
	fstream file;
	file.open(filename);

	if (file.is_open())
	{
		file >> j;
		j = j["layers"];

		for (int i = 0; i < j.size(); i++)
		{
			auto it = j[i].find("name");
			if (it != j[i].end())
			{
				if (*it != "Map" && *it != "Ground" && *it != "Platform" && *it != "Door" && *it != "Death")
					_objectLayers.push_back(new ObjectLayer(filename, *it));
				else if (*it == "Map")
				{
					it = j[i].find("height");
					_height = *it;
					_height = _height * TILES_SIZE;

					it = j[i].find("width");
					_width = *it;
					_width = _width * TILES_SIZE;
				}
			}
		}
		file.close();
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	createObjects();
}

Map::~Map()
{
	for (int i = 0; i < _objectLayers.size(); i++)
		delete _objectLayers[i];

	_objectLayers.clear();
}

void Map::createObjects()
{
	Boss1* spenta = nullptr;
	Boss2* azura = nullptr;
	Boss3* angra = nullptr;

	for (int i = 0; i < _objectLayers.size(); i++)
	{
		string name = _objectLayers[i]->getName();
		vector<pair<Vector2D, string>> objectData = _objectLayers[i]->getObjectsData();

		for (int j = 0; j < objectData.size(); j++)
		{
			Vector2D pos = objectData[j].first;
			string data = objectData[j].second;

			if (name == "Player")
			{
				_player->setPlayerPosition(Vector2D(pos.getX() / M_TO_PIXEL, (pos.getY() - TILES_SIZE * 2) / M_TO_PIXEL));
			}
			else if (name == "Melee")
			{
				_objects->addChild(new MeleeEnemy(_game, _player, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "Martyr")
			{
				_objects->addChild(new MartyrEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStatic")
			{
				_objects->addChild(new DistanceStaticEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "FlyingDistance")
			{
				_objects->addChild(new StaticFlyingEnemy(_game, _player, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "DistanceDynamic")
			{
				_objects->addChild(new DistanceDynamicEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Spawner")
			{
				_objects->addChild(new StaticSpawnerEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "MeleeShip")
			{
				_objects->addChild(new NormalSpawner<MeleeEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2)));
			}
			else if (name == "DistanceStaticShip")
			{
				_objects->addChild(new DistanceSpawner<DistanceStaticEnemy>(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Bomber")
			{
				_objects->addChild(new BomberEnemy(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
			}
			else if (name == "Boss1")
			{
				spenta = (new Boss1(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(spenta);
				spenta->setBossPanel(_game->getCurrentState()->getPlayHUD()->getBossPanel());
			}
			else if (name == "Boss2")
			{
				azura = (new Boss2(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(azura);
				azura->setBossPanel(_game->getCurrentState()->getPlayHUD()->getBossPanel());
			}
			else if (name == "Boss3")
			{
				angra = (new Boss3(_game, _player, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2), _bulletPool));
				_objects->addChild(angra);
				angra->setBoss3Panel(_game->getCurrentState()->getPlayHUD()->getBoss3Panel());
			}
			else if (name == "Lasers")
			{
				LaserHandler* l = new LaserHandler(_game, _game->getTexture("LaserContainer"), _game->getTexture("Laser"), _player, 8, stoi(data), pos + Vector2D{0, -40});
				addChildFront(l);
				azura->setLasers(l);
			}
			else if (name == "Misil")
			{
				_objects->addChild(new MissileTurret(_game, spenta, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2.8), stoi(data)));
			}
			else if (name == "NPC")
			{
				NPC* npc = new NPC(_game, Vector2D(pos.getX() - TILES_SIZE, pos.getY() - TILES_SIZE * 2), _game->getDialogue(data));
				npc->setDialoguePanel(_game->getCurrentState()->getPlayHUD()->getDialoguePanel());
				_objects->addChild(npc);
			}
			else if (name == "Shop")
			{
				Shop* tienda = new Shop(_game, Vector2D(pos.getX(), pos.getY() - TILES_SIZE * 2.6), _game->getCurrentState()->getPlayHUD()->getShop());
				_objects->addChild(tienda);
			}
			else if (name == "FloatingHead")
			{
				FloatingHead* head = new FloatingHead(_game, _player, Vector2D(pos.getX() - TILES_SIZE * 2, pos.getY() - TILES_SIZE * 2), _bulletPool, angra);

				_game->getCurrentState()->getPlayHUD()->getEnemyLifePanel()->addEnemy(head);
				head->setLifePanel(_game->getCurrentState()->getPlayHUD()->getEnemyLifePanel());

				angra->addChild(head);
				angra->push_backHead(head);
			}
			else if (name == "SpawnerBoss")
			{
				SpawnerBoss* spawner= new SpawnerBoss(_game, _player, _game->getTexture("MissileTurret"), Vector2D(pos.getX() - TILES_SIZE * 2, pos.getY() - TILES_SIZE * 2), _spawnType, _bulletPool);

				angra->addChild(spawner);
				angra->push_backSpawner(spawner);
				_spawnType++;
			}
			else if (name == "Throne")
			{
				SpriteObject* throne = new SpriteObject(_game, _game->getTexture("Throne"), Vector2D(pos.getX() - TILES_SIZE * 2, pos.getY() - TILES_SIZE * 2));
				AnimatedSpriteComponent* throneAnim = throne->getComponent<AnimatedSpriteComponent>();
				throneAnim->reset();
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneIdle, 14, true);
				throneAnim->addAnim(AnimatedSpriteComponent::ThroneEnd, 27, false);

				throneAnim->playAnim(AnimatedSpriteComponent::ThroneIdle);
				angra->setAnimThrone(throneAnim);
				_objects->addChildFront(throne);
			}
		}
	}
}

void Map::restartLevel()
{
	if (_objects->getChildren().size() != 0)
	{
		_objects->destroyAllChildren();
		createObjects();
	}
}

bool Map::handleEvent(const SDL_Event & event)
{
	GameObject::handleEvent(event);
	return false;
}

void Map::update(const double& deltaTime)
{
	GameObject::update(deltaTime);
}

void Map::render(Camera * c) const
{
	GameObject::render(c);
}