#pragma once
#include "GameComponent.h"
#include "Arm.h"
#include "Gun.h"
#include "Shooter.h"
#include "Money.h"
#include "PlayState.h"

class Arm;
class Game;

class AnimatedSpriteComponent;
class PlayerControllerComponent;
class PlayState;

class Player : public GameComponent
{
private:
	PlayState* _play = nullptr;
	int _life;
	int AmountOfCollision;
	uint _currentState = 0;
	Arm* _weaponArm = nullptr;
	AnimatedSpriteComponent* _anim;
	PlayerControllerComponent* _controller;
	TransformComponent * _transform;
	BodyComponent * _body;
	uint32 _dashCD = 3000;
	uint32 _timer = 0;
	int _MaxDash = 2;
	Money * _money = nullptr;
public:

	enum states { Idle, Attacking, Walking, Reloading, Dashing, Falling, Jumping };

	Player(Texture* texture, Game* g, PlayState* play, string tag);
	~Player();

	void update();
	virtual void beginCollision(GameComponent* other);
	virtual void endCollision(GameComponent* other);

	void setLife(double amount);
	void addLife(double amount);
	void subLife(double amount);
	void die();

	void setArm(Arm* arm) { _weaponArm = arm; };
	Arm* getWeaponArm() { return _weaponArm; }
	void equipGun(int gunIndex, int bulletPoolIndex = 0);

	void reload();

	uint getCurrentState() { return _currentState; };
	void setCurrentState(uint n) { _currentState = n; };
};