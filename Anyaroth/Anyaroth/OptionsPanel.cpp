#include "OptionsPanel.h"
#include "Game.h"


OptionsPanel::OptionsPanel(Game* g, bool mainMenu) : _menu(mainMenu)
{
	//----BOTONES----//

	//Cambiar valores
		//Volumen
	_moreVolume = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreVolume(game); }, { 0, 1, 2, 2, 2 });
	buttonW = _moreVolume->getW();
	buttonH = _moreVolume->getH();
	_moreVolume->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW, CAMERA_RESOLUTION_Y - 212);

	_lessVolume = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessVolume(game); }, { 0, 1, 2, 2, 2 });
	_lessVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW * 2, CAMERA_RESOLUTION_Y - 212);
		
		//Efectos
	_moreSFXVolume = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreSFXVolume(game); }, { 0, 1, 2, 2, 2 });
	_moreSFXVolume->setPosition(_moreVolume->getX(), CAMERA_RESOLUTION_Y - 137);

	_lessSFXVolume = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessSFXVolume(game); }, { 0, 1, 2, 2, 2 });
	_lessSFXVolume->setPosition(_lessVolume->getX(), CAMERA_RESOLUTION_Y - 137);
	
		//Brillo
	_moreBright = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreBright(game); }, { 0, 1, 2, 2, 2 });
	_moreBright->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW / 4, CAMERA_RESOLUTION_Y - 61);

	_lessBright = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessBright(game); }, { 0, 1, 2, 2, 2 });
	_lessBright->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 4 - buttonW, CAMERA_RESOLUTION_Y - 61);

	//Volver menu
	_backButton = new ButtonUI(g, g->getTexture("MenuReturnButton"), [this](Game* game) { back(game); }, { 0, 1, 2, 2, 2 });
	_backButton->setPosition(CAMERA_RESOLUTION_X / 2 + 150 - _backButton->getW(), CAMERA_RESOLUTION_Y - 34);

	//Pantalla completa
	_screenButton = new ButtonUI(g, g->getTexture("MenuFullScreenButton"), [this](Game* game) { fullScreen(game); }, { 0, 1, 2, 2, 2 });
	_screenButton->setPosition(CAMERA_RESOLUTION_X / 2 - 150, _backButton->getY());

	_buttons.push_back(_lessVolume);
	_buttons.push_back(_moreVolume);
	_buttons.push_back(_lessSFXVolume);
	_buttons.push_back(_moreSFXVolume);
	_buttons.push_back(_lessBright);
	_buttons.push_back(_moreBright);
	_buttons.push_back(_screenButton);
	_buttons.push_back(_backButton);
	//----TEXTOS----//

	//Valores
	_volumeText = new TextUI(g, "100", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
							_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);

	_volumeSFXText = new TextUI(g, "100", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
								_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);

	//Nombres
	_nameVolumeText = new TextUI(g, "Volumen Musica", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameVolumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameVolumeText->getW() / 2,
								_moreVolume->getY() - 30);

	_nameVolumeSFXText = new TextUI(g, "Volumen Efectos", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameVolumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameVolumeSFXText->getW() / 2,
									_moreSFXVolume->getY() - 30);

	_nameBrightText = new TextUI(g, "Brillo", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameBrightText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameBrightText->getW() / 2,
								_moreBright->getY() - 30);

	addChild(_moreVolume);
	addChild(_lessVolume);
	addChild(_moreSFXVolume);
	addChild(_lessSFXVolume);
	addChild(_moreBright);
	addChild(_lessBright);
	addChild(_backButton);
	addChild(_screenButton);
	addChild(_volumeSFXText);
	addChild(_volumeText);
	addChild(_nameVolumeSFXText);
	addChild(_nameVolumeText);
	addChild(_nameBrightText);

	_visible = false;
}


OptionsPanel::~OptionsPanel()
{
}

void OptionsPanel::moreVolume(Game * g)
{
	float _volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume + 0.1 > 1)
		_volume = 1;
	else
		_volume += 0.1;

	g->getSoundManager()->setMusicVolume(_volume);

	_volume *= 10;
	_volume = ceil(_volume);
	_volume *= 10;
	_volume = ceil(_volume);

	int vol = _volume;

	_volumeText->setText(to_string(vol));
	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
		_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);
}

void OptionsPanel::lessVolume(Game * g)
{
	float _volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume - 0.1 < 0)
		_volume = 0;
	else
		_volume -= 0.1;

	g->getSoundManager()->setMusicVolume(_volume);

	_volume *= 10;
	_volume = ceil(_volume);
	_volume *= 10;
	_volume = ceil(_volume);

	int vol = _volume;

	_volumeText->setText(to_string(vol));
	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
		_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);
}

void OptionsPanel::moreSFXVolume(Game * g)
{
	float _sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume + 0.1 > 1)
		_sfxVolume = 1;
	else
		_sfxVolume += 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);


	_sfxVolume *= 10;
	_sfxVolume = ceil(_sfxVolume);
	_sfxVolume *= 10;
	_sfxVolume = ceil(_sfxVolume);

	int vol = _sfxVolume;

	_volumeSFXText->setText(to_string(vol));
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
		_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);
}

void OptionsPanel::lessSFXVolume(Game * g)
{
	float _sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume - 0.1 < 0)
		_sfxVolume = 0;
	else
		_sfxVolume -= 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);

	_sfxVolume *= 10;
	_sfxVolume = ceil(_sfxVolume);
	_sfxVolume *= 10;
	_sfxVolume = ceil(_sfxVolume);

	int vol = _sfxVolume;

	_volumeSFXText->setText(to_string(vol));
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
		_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);
}

void OptionsPanel::moreBright(Game * g)
{
	float bright = SDL_GetWindowBrightness(g->getWindow());

	if (bright >= 1)
		bright = 1;
	else
		bright += 0.1;

	SDL_SetWindowBrightness(g->getWindow(), bright);
}

void OptionsPanel::lessBright(Game * g)
{
	float bright = SDL_GetWindowBrightness(g->getWindow());

	if (bright <= 0)
		bright = 0;
	else
		bright -= 0.1;

	SDL_SetWindowBrightness(g->getWindow(), bright);
}

void OptionsPanel::back(Game * g)
{
	_visible = !_visible;
	if (_menu)
	{
		g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgMenu"), g->getCurrentState()->getMainCamera()));
		g->getCurrentState()->getMenuHUD()->getMainMenuPanel()->setVisible(true);
	}
	else
	{
		g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgPauseMenu"), g->getCurrentState()->getMainCamera()));
		g->getCurrentState()->getPauseHUD()->getPausePanel()->setVisible(true);
	}
}

void OptionsPanel::fullScreen(Game* g)
{
	bool IsFullscreen = SDL_GetWindowFlags(g->getWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (IsFullscreen)
	{
		_screenButton->setFrames({ 0, 1, 2, 3, 2 });
		SDL_SetWindowFullscreen(g->getWindow(), 0);
	}
	else
	{
		_screenButton->setFrames({ 3, 4, 5, 0, 5 });
		SDL_SetWindowFullscreen(g->getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}