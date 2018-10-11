#pragma once
#include "Actor.h"
class Player :
	public Actor
{
private:
	float MoveSpeed = 130.f;
	float Deceleration = 0.999f;
	Vector2<float> CurrentVelocity;

	void Decelerate();

public:
	void Update(sf::Time deltaTime) override;
};

