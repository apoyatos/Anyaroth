﻿#include "DistanceStaticEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include"Game.h"

DistanceStaticEnemy::DistanceStaticEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceEnemy(g, player, pos, g->getTexture("EnemyMelee"), pool), Enemy(g, player, pos, g->getTexture("EnemyMelee"))
{
	_vision = 500;
	_life = 50;
	_attackRangeX = _attackRangeY = _vision; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS);

	//Ajustes del arma
	_myGun->setMaxCadence(700);
	_myGun->setBulletSpeed(30);
}

void DistanceStaticEnemy::update(const double& deltaTime)
{
	DistanceEnemy::update(deltaTime);

	if (!isStunned() && !isDead() && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

		if (inVision) //Jugador en el rango
		{
			raycast();
			shoot();
		}
	}
}