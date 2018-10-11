#include "Player.h"
#include <iostream>
#include <math.h>

void Player::Decelerate()
{
	CurrentVelocity *= Deceleration;
}

void Player::Update(sf::Time deltaTime)
{
	Decelerate();

	//Player movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		CurrentVelocity.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		CurrentVelocity.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		CurrentVelocity.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		CurrentVelocity.y = 1;
	}

	//player rotation

	sf::Vector2<float> normalVector;
	normalVector.y = 1;
	normalVector.x = 0;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();

	rotate(10 * deltaTime.asSeconds());

	move(CurrentVelocity*deltaTime.asSeconds() * MoveSpeed);
}
