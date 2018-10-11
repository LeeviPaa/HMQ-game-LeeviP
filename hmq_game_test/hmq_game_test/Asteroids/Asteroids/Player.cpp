#include "Player.h"
#include <iostream>
#include <math.h>
#include "Game.h"

#define LOG(x) std::cout << x << std::endl

void Player::Decelerate()
{
	CurrentVelocity *= Deceleration;
}

Player::Player()
{
	setOrigin(25.f/2, 25.f/2);
	setPosition(400, 400);
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

	//get the vector from the player to the mouse position and change it to float vector
	sf::Vector2i relativeMousePosition = Game::LocalMousePosition;
	sf::Vector2f relativeMousePositionF(relativeMousePosition.x, relativeMousePosition.y);
	relativeMousePositionF = relativeMousePositionF - getPosition();
	relativeMousePositionF /= VectorLenght(relativeMousePositionF);

	//calculate the angle between two vectors
	float dotProduct = (normalVector.x * relativeMousePositionF.x) + (normalVector.y * relativeMousePositionF.y);
	float magnitudes =  VectorLenght(normalVector) * VectorLenght(relativeMousePositionF);

	//beware of that NAN error
	if (magnitudes != 0)
	{
		float angle = 0;

		if(relativeMousePositionF.x < 0)
			angle = acos(dotProduct / magnitudes)* (180/3.14159265358979323846f);
		else
			angle = acos(dotProduct / magnitudes)* -(180 / 3.14159265358979323846f);

		setRotation(angle);
	}

	move(CurrentVelocity*deltaTime.asSeconds() * MoveSpeed);

	//move the player from one edge to another smoothly
	Vector2f NewPos = getPosition();
	if (NewPos.x < -25)
	{
		NewPos.x = 825;
	}
	if (NewPos.x > 825)
	{
		NewPos.x = -25;
	}

	if (NewPos.y < -25)
	{
		NewPos.y = 825;
	}
	if (NewPos.y > 825)
	{
		NewPos.y = -25;
	}

	setPosition(NewPos);
}
