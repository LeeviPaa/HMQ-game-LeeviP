#include "Asteroid.h"
#include "Game.h"
#include <iostream>
#include <random>

#define LOG(x) std::cout << x << std::endl

void Asteroid::Die()
{
	dead = true;
	Game::DeleteAsteroid(this);
}

Asteroid::Asteroid(Vector2f direction)
{
	Direction = direction;
	setOrigin(50, 50);

	setRotation(rand() % 360);
	rotSpeed = (rand() % 300) -150;
		
	AsteroidShape = VertexArray(sf::LineStrip, 8);

	int shape = rand() % 2;
	if (shape == 0)
	{

		AsteroidShape[0].position = Vector2f(0, 0);
		AsteroidShape[1].position = Vector2f(30, 0);
		AsteroidShape[2].position = Vector2f(70, 20);
		AsteroidShape[3].position = Vector2f(100, 0);
		AsteroidShape[4].position = Vector2f(100, 100);
		AsteroidShape[5].position = Vector2f(60, 110);
		AsteroidShape[6].position = Vector2f(0, 50);
		AsteroidShape[7].position = Vector2f(0, 0);
	}
	else
	{
		AsteroidShape[0].position = Vector2f(0, 0);
		AsteroidShape[1].position = Vector2f(50, -30);
		AsteroidShape[2].position = Vector2f(100, 60);
		AsteroidShape[3].position = Vector2f(85, 90);
		AsteroidShape[4].position = Vector2f(75, 100);
		AsteroidShape[5].position = Vector2f(30, 50);
		AsteroidShape[6].position = Vector2f(0, 40);
		AsteroidShape[7].position = Vector2f(0, 0);
	}

	AsteroidShape[0].color = sf::Color::White;
	AsteroidShape[1].color = sf::Color::White;
	AsteroidShape[2].color = sf::Color::White;
	AsteroidShape[3].color = sf::Color::White;
	AsteroidShape[4].color = sf::Color::White;
	AsteroidShape[5].color = sf::Color::White;
	AsteroidShape[6].color = sf::Color::White;
	AsteroidShape[7].color = sf::Color::White;

	boundingBox = AsteroidShape.getBounds();
}

Asteroid::~Asteroid()
{
	//LOG("DESTROYED");
}


void Asteroid::Update(sf::Time deltaTime)
{
	if (dead)
		return;
	move(Direction*deltaTime.asSeconds()*MoveSpeed);
	rotate(rotSpeed * deltaTime.asSeconds());

	Vector2f position = getPosition();

	if (position.x < -200)
	{
		Die();
	}
	if (position.x > 1000)
	{
		Die();
	}
	if (position.y < -200)
	{
		Die();
	}
	if (position.y > 1000)
	{
		Die();
	}
}
	
