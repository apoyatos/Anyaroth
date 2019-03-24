#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "CoinsCounter.h"
#include "AmmoViewer.h"
#include "WeaponryViewer.h"
#include "DashViewer.h"

class PlayerPanel : public PanelUI
{
	private:
		ImageUI* _marco = nullptr;

		LifeBar* _lifeBar = nullptr;
		AmmoViewer* _ammoViewer = nullptr;
		CoinsCounter* _coinsCounter = nullptr;
		WeaponryViewer* _weaponryViewer = nullptr;
		DashViewer* _dashViewer = nullptr;

	public:
		PlayerPanel() {};
		PlayerPanel(Game* game);
		~PlayerPanel() {}

		inline void updateLifeBar(const int& life, const int& maxLife) { _lifeBar->updateLifeBar(life, maxLife); }
		inline void updateAmmoViewer(const int& clip, const int& magazine) { _ammoViewer->updateAmmoViewer(clip, magazine); }
		inline void updateCoinsCounter(const int& cant) { _coinsCounter->updateCoinsCounter(cant); }
		inline void updateWeaponryViewer() { _weaponryViewer->updateWeaponryViewer(); }
		inline void updateDashViewer(const uint& cant) { _dashViewer->setDashes(cant); }
};