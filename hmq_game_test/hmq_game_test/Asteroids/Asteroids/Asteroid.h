#pragma once
#include "Actor.h"

class Asteroid: public Actor
{
private:
	float MoveSpeed = 100.f;
	Vector2f Direction;
	float TimeElapsed = 0;
	bool dead = false;
	sf::VertexArray AsteroidShape;
	float rotSpeed = 0;
	void Die();

public:
	Asteroid(Vector2f direction);
	~Asteroid();
	FloatRect boundingBox;

	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(AsteroidShape, states);
	}
	
};

