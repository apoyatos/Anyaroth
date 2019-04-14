#pragma once
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <vector>

typedef unsigned int uint;

class GameObject;

struct AnimationStateImage
{
	uint name;
	uint numFrames;
	bool loop;
	bool animationFinished;
	uint lapse;
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
private:
	GameObject* _obj = nullptr;
protected:
	vector<AnimationStateImage> _animations = {};

	uint _currentAnim = 0;
	uint _frame = 0;
	double _timer = 0.0;
	bool _animationFinished = false;

public:
	enum Player { Idle, Walk, WalkBack, MeleeKnife, ReloadPistol, BeforeJump, Jump, StartFalling, Falling, Hurt, Dash, DashDown, DashBack, ReloadShotgun, PlayerDie };
	enum Gun { None, Shoot, NoAmmo };
	enum Enemy { EnemyIdle, EnemyWalk, EnemyAttack, EnemyDie };
	enum Coin { Main };
	enum Bullet { Default, Destroy };
	enum Spenta {
		SpentaIdle, SpentaSwordLeft, SpentaSwordRight, SpentaStartShield, SpentaLoopShield, SpentaEndShield,
		SpentaDie, SpentaStartBomb, SpentaLoopBomb, SpentaEndBomb, SpentaOrb, SpentaWing
	};
	enum MissileTurret { Deactivated, Activating, Active, Used };

	AnimatedSpriteComponent(GameObject* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component(), _obj(obj) {}
	virtual ~AnimatedSpriteComponent() {}

	virtual void render(Camera* c) const;
	virtual void update(const double& deltaTime);

	void addAnim(uint name, uint numFrames, bool loop, uint lapse = 60);
	void playAnim(uint name);

	inline bool animationFinished() { return _animations[_currentAnim].animationFinished; }
	inline uint getCurrentAnim() const { return _currentAnim; }
	inline bool isLooping() { return _animations[_currentAnim].loop; }

	void reset();
};