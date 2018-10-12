#pragma once
#include "Actor.h"

class Asteroid: public Actor
{
private:
	float MoveSpeed = 100.f;
	Vector2<float> CurrentVelocity;
	sf::CircleShape shape;
	float TimeElapsed = 0;
	bool dead = false;

public:
	Asteroid();
	~Asteroid();

	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(shape, states);
	}
	
};

