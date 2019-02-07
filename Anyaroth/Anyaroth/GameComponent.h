#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include <vector>

using namespace std;
/*
 *
 */
class GameComponent: public GameObject {
public:
	GameComponent();
	virtual ~GameComponent();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;

protected:
	TransformComponent* transform;
	vector<RenderComponent*> renderComp_;
};

#endif /* GAMECOMPONENT_H_ */