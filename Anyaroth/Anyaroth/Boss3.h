#include "Boss.h"
#include "GravityBombCannon.h"
#include "BounceOrbCannon.h"
#include "BossSensor.h"

class Boss3 : public Boss
{
	private:
		int _stopRange = 40;
		int _velocity = 8;
		bool _invulnerable = false;
		Vector2D _dir = Vector2D(1, 0);

		//Cosas del disparo circular
		int _num = 0, _timeOnShooting = 0, _timeBeetwenBullets = 0, _timeBeetwenCircularShoot = 1000;
		int _numBullets = 40, _actualBullet = 0;
		double _angleIncrease = 360/ _numBullets, _angle = 180;

		void shoot();
		void shootBullet(int numBullets, double angleIncrease);
		void circularShoot(const double& deltaTime);

		//Cosas de la fase soldado
		Gun* _otherGun = nullptr;
		void changeGun();

		int _numBulletsRifle = 0, _rifleBulletsCount = 0, _rifleCadence = 250;
		void rifleShoot();

		//Cosas del Dash
		double _dashTime = 500, _dashTimer = _dashTime, _gravity = 3, _damping = 3, _force = 40;
		void dash();
		void checkDash(double deltaTime);


		bool _bulletApproaching = false;
		BossSensor* _sensor = nullptr;
		//Cosas del salto
		double _jumpForce = 300;
		int _onFloor = 0;
		void jump();

		//Cosas del disparo de agujeros negros
		GravityBombCannon* _gravGun = nullptr;
		void shootGrav();

		//Cosas del ataque Portal
		int timeToReapear = 2000, timeToShowPortal = 1000, _timeOut = 0;
		int _explosionRange = 60, _impulse = 15, _explosionDamage = 15;
		void portalAttack(const double& deltaTime);
		bool portalVisible = false;

	public:
		Boss3(Game* g, Player* player, Vector2D pos, BulletPool* pool);
		virtual ~Boss3();

		virtual void movement(const double& deltaTime);
		virtual void beginCollision(GameObject* other, b2Contact* contact);
		virtual void endCollision(GameObject * other, b2Contact* contact);

		inline void setBulletApproaching(bool bA) { _bulletApproaching = bA; }
		virtual void fase1(const double& deltaTime);
		virtual void fase2(const double& deltaTime);
		virtual void fase3(const double& deltaTime);
		virtual void beetwenFases(const double& deltaTime);
		void subLife(int damage);
};