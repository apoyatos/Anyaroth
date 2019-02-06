#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class MovingComponent : public PhysicsComponent
{
	private:
		TransformComponent* transform;
		Vector2D dir;

	public:
		MovingComponent(TransformComponent* trans, double x, double y) :
			transform(trans), MovingComponent::PhysicsComponent() { dir = Vector2D(x, y); };

		double getDirX() { return dir.getX(); }
		double getDirY() { return dir.getY(); }
		void changeDir(double x, double y) { dir = Vector2D(x, y); }

		virtual void update() 
		{
			Vector2D pos = transform->getPosition();
			double x = pos.getX();
			double y = pos.getY();
			transform->setPosition(dir.getX() + x, dir.getY() + y);
		}
};