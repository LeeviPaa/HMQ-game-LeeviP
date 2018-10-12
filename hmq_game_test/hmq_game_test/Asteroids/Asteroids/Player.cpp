#include "Player.h"
#include <iostream>
#include <math.h>
#include "Game.h"

#define LOG(x) std::cout << x << std::endl

void Player::Movement(float deltaTime)
{
	sf::Vector2f InputVector;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		InputVector.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		InputVector.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		InputVector.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		InputVector.y = 1;
	}

	if (!gate && sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		gate = true;
		Asteroid* testActor = Game::SpawnAsteroid();
		testActor->setPosition(50, 200);
	}

	CurrentVelocity += InputVector * Acceleration*deltaTime;

	if (CurrentVelocity.x > MoveSpeed)
		CurrentVelocity.x = MoveSpeed;

	if (CurrentVelocity.x < -MoveSpeed)
		CurrentVelocity.x = -MoveSpeed;

	if (CurrentVelocity.y > MoveSpeed)
		CurrentVelocity.y = MoveSpeed;

	if (CurrentVelocity.y < -MoveSpeed)
		CurrentVelocity.y = -MoveSpeed;

	move(CurrentVelocity*deltaTime * MoveSpeed);

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

void Player::Rotation(float deltaTime)
{
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
	float magnitudes = VectorLenght(normalVector) * VectorLenght(relativeMousePositionF);

	//beware of that NAN error
	if (magnitudes != 0)
	{
		float angle = 0;

		if (relativeMousePositionF.x < 0)
			angle = acos(dotProduct / magnitudes)* (180 / 3.14159265358979323846f);
		else
			angle = acos(dotProduct / magnitudes)* -(180 / 3.14159265358979323846f);

		setRotation(angle + 180);
	}
}

void Player::Shooting(float deltaTime)
{
	//save prev mouse position so that we only shoot on the frame the click is made
	prevMousePressed = mousePressed;
	mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (mousePressed && !prevMousePressed)
	{
		sf::Vector2i relativeMousePosition = Game::LocalMousePosition;
		sf::Vector2f relativeMousePositionF(relativeMousePosition.x, relativeMousePosition.y);
		relativeMousePositionF = relativeMousePositionF - getPosition();
		relativeMousePositionF /= VectorLenght(relativeMousePositionF);

		Vector2f direction = relativeMousePositionF;
		PlayerBullet* pbullet = Game::SpawnPBullet(direction);
		pbullet->setPosition(getPosition());
	}
}

void Player::Decelerate(Time deltaTime)
{
	CurrentVelocity -= CurrentVelocity* Deceleration * deltaTime.asSeconds();
}

Player::Player()
{
	//setup the player values

	setOrigin(15, 15);
	setPosition(400, 400);

	sf::Vector2<float> boxSize;
	boxSize.x = 25;
	boxSize.y = 25;

	playerShape = VertexArray(sf::TriangleFan, 4);
	playerShape[0].position = Vector2f(15, 20);
	playerShape[1].position = Vector2f(0, 30);
	playerShape[2].position = Vector2f(15, 0);
	playerShape[3].position = Vector2f(30, 30);

	playerShape[0].color = sf::Color::White;
	playerShape[1].color = sf::Color::White;
	playerShape[2].color = sf::Color::White;
	playerShape[3].color = sf::Color::White;


	shape.setSize(boxSize);
	shape.setFillColor(sf::Color::Yellow);
}

void Player::Update(sf::Time deltaTime)
{
	Decelerate(deltaTime);

	Movement(deltaTime.asSeconds());

	Rotation(deltaTime.asSeconds());

	Shooting(deltaTime.asSeconds());
}
