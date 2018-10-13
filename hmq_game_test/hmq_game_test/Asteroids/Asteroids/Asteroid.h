#pragma once
#include "Actor.h"

class Asteroid: public Actor
{
private:
	float MoveSpeed = 100.f;
	Vector2f Direction;
	float TimeElapsed = 0;
	bool dead = false;
	void Die();
	VertexArray AsteroidShape;

public:
	enum AsteroidType {
		big,
		medium,
		small
	};

	Asteroid(Vector2f direction, AsteroidType type);
	~Asteroid();
	AsteroidType asteroType;
	FloatRect boundingBox;
	void Collide();

	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(AsteroidShape, states);
	}
	
};

