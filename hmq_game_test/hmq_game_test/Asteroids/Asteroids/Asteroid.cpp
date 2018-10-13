#include "Asteroid.h"
#include "Game.h"
#include <iostream>
#include <random>

#define LOG(x) std::cout << x << std::endl

void Asteroid::Die()
{
	dead = true;
	Game::DeleteAsteroid(this);

	Vector2f direction(0, 0);
	float dirX = ((rand() % 200) - 100.f)/100.f;
	float dirY = ((rand() % 200) - 100.f)/100.f;
	LOG(direction.x);
	direction.x = dirX;
	direction.y = dirY;

	Asteroid* subA;
	Asteroid* subB;

	//here we spawn two smaller asteroids depending on this type
	switch (asteroType)
	{
	case Asteroid::big:
		subA = Game::SpawnAsteroid(direction, AsteroidType::medium);
		subA->setPosition(getPosition() + direction*55.f);
		subB = Game::SpawnAsteroid(-direction, AsteroidType::medium);
		subB->setPosition(getPosition() - direction * 55.f);
		break;
	case Asteroid::medium:
		subA = Game::SpawnAsteroid(direction, AsteroidType::small);
		subA->setPosition(getPosition() + direction * 30.f);
		subB = Game::SpawnAsteroid(-direction, AsteroidType::small);
		subB->setPosition(getPosition() - direction * 30.f);
		break;
	case Asteroid::small:
		break;
	default:
		break;
	}
}

Asteroid::Asteroid(Vector2f direction, AsteroidType type)
{
	Direction = direction;
		
	AsteroidShape = VertexArray(sf::LineStrip, 8);

	asteroType = type;

	switch (type)
	{
	case Asteroid::big:
		break;
	case Asteroid::medium:
		setScale(0.5f, 0.5f);
		break;
	case Asteroid::small:
		setScale(0.25f, 0.25f);
		break;
	default:
		break;
	}

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

		//create a convex shape from which we can get the globalbounds
		collision = ConvexShape(5);

		collision.setPoint(0, Vector2f(0, 0));
		collision.setPoint(1, Vector2f(100, 0));
		collision.setPoint(2, Vector2f(100, 100));
		collision.setPoint(3, Vector2f(60, 110));
		collision.setPoint(4, Vector2f(0, 50));
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

		collision = ConvexShape(6);

		collision.setPoint(0, Vector2f(0, 0));
		collision.setPoint(1, Vector2f(50, -30));
		collision.setPoint(2, Vector2f(100, 60));
		collision.setPoint(3, Vector2f(85, 90));
		collision.setPoint(4, Vector2f(75, 100));
		collision.setPoint(5, Vector2f(0, 40));
	}

	AsteroidShape[0].color = sf::Color::White;
	AsteroidShape[1].color = sf::Color::White;
	AsteroidShape[2].color = sf::Color::White;
	AsteroidShape[3].color = sf::Color::White;
	AsteroidShape[4].color = sf::Color::White;
	AsteroidShape[5].color = sf::Color::White;
	AsteroidShape[6].color = sf::Color::White;
	AsteroidShape[7].color = sf::Color::White;

	collision.setScale(getScale());
	boundingBox = collision.getGlobalBounds();
}

Asteroid::~Asteroid()
{
	//LOG("DESTROYED");
}

void Asteroid::Collide()
{
	LOG("Collision");
	Die();
}

void Asteroid::Update(sf::Time deltaTime)
{
	if (dead)
		return;
	move(Direction*deltaTime.asSeconds()*MoveSpeed);

	boundingBox = collision.getGlobalBounds();

	collision.setPosition(getPosition());

	Vector2f point = collision.getPoint(0);

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
	
