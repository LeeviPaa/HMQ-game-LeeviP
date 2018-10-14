#pragma once
#include "Actor.h"
#include "Player.h"

class UFO : public Actor
{
private: 
	float speed = 0.35f;
	int health = 2;
	float timeElapsed = 0;
	float timePerShot = 1.f;
	VertexArray UfoShape;
	Vector2f Direction;
	Player* playerRef;
	void Shoot(Vector2f direction);

public:
	UFO(Player* player, Vector2f direction);
	~UFO();
	void Collide();

	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(UfoShape, states);
	}
};

