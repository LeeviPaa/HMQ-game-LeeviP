#pragma once
#include "Actor.h"
class Player :
	public Actor
{
private:
	float MoveSpeed = 100.f;
	float Acceleration = 10.f;
	float Deceleration = 0.999f;
	bool gate = false;
	Vector2<float> CurrentVelocity;
	sf::RectangleShape shape;

	void Decelerate();

public:
	Player();
	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(shape, states);
	}
};

