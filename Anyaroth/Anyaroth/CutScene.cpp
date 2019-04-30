#include "CutScene.h"

CutScene::CutScene(Player* player) : _player(player)
{

}

CutScene::~CutScene()
{
	while (!_events.empty())
	{
		delete _events.front();
		_events.pop();
	}
}

void CutScene::update(const double& deltaTime)
{
	if (_isPlaying && !_events.empty())
	{
		if (!_events.front()->isFinished())
			_events.front()->update(deltaTime);
		else
		{
			delete _events.front();
			_events.pop();

			if (!_events.empty())
				_events.front()->play();
			else
			{
				_isPlaying = false;
				_player->setInputFreezed(false);
			}
		}
	}
}

void CutScene::play()
{
	if (!_events.empty())
	{
		_player->setInputFreezed(true);
		_isPlaying = true;
		_events.front()->play();
	}

}

void CutScene::addMoveEvent(BodyComponent* body, int dir, int speed, int xDestination)
{
	_events.push(new MoveEvent(body, dir, speed, xDestination));
}

void CutScene::addDialogueEvent(DialoguePanel* dialoguePanel, Dialogue dialogue)
{
	_events.push(new DialogueEvent(dialoguePanel, dialogue));
}

void CutScene::addWaitEvent(int time)
{
	_events.push(new WaitingEvent(time));
}

void CutScene::addCameraEvent(Camera* cam, int time, CamEffect type)
{
	if (type == CamEffect::FadeIn || type == CamEffect::FadeOut)
	{
		_events.push(new FadeInOutEvent(cam, time, type));
	}
	else
	{
		_events.push(new ZoomInOutEvent(cam, time, type));
	}
}

void CutScene::addCameraShakeEvent(Camera* cam, int time, int intensity)
{
	_events.push(new ShakeEvent(cam, time, intensity));
}

void CutScene::addFlipEvent()
{
	_events.push(new FlipEvent(_player));
}

void CutScene::addShopEvent(ShopMenu* shop)
{
	_events.push(new ShopEvent(shop));
}