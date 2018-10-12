#pragma once
#include "Actor.h"
class Player :
	public Actor
{
private:
	float MoveSpeed = 100.f;
	float Acceleration = 10.f;
	float Deceleration = 0.7f;
	bool gate = false;
	Vector2<float> CurrentVelocity;
	sf::RectangleShape shape;
	
	bool mousePressed = false;
	bool prevMousePressed = false;

	void Movement(float deltaTime);
	void Rotation(float deltaTime);
	void Shooting(float deltaTime);
	void Decelerate(Time deltaTime);

public:
	Player();
	VertexArray playerShape;
	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(playerShape, states);
	}
};

