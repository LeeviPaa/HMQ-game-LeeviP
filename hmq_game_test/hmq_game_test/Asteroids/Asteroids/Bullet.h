#pragma once
#include "Actor.h"
class Bullet :
	public Actor
{
private:
	Vector2f Direction;
	float speed = 250;
	CircleShape Shape;
	bool dead = false;
	void Die();

public:
	Bullet(Vector2f direction);
	~Bullet();
	void Update(Time deltaTime);

	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(Shape, states);
	}

	void Collide();
};

