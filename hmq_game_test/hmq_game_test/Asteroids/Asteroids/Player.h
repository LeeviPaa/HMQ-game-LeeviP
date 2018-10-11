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
	Player();
	void Update(sf::Time deltaTime) override;
	void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		sf::Vector2<float> boxSize;
		boxSize.x = 25;
		boxSize.y = 25;

		//no need to do this every frame!!!
		//create a start() function
		sf::RectangleShape shape(boxSize);
		shape.setFillColor(sf::Color::Yellow);

		target.draw(shape, states);
	}
};

