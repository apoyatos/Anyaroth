#include "ImprovedRifle.h"



ImprovedRifle::ImprovedRifle(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 20, 1000, 36, 160, 100,  &_effect, true, ImprovedRifle_Weapon)
{
	_offset = { 24, -1 };
}


ImprovedRifle::~ImprovedRifle()
{
}
