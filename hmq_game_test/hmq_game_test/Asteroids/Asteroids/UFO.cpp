#include "UFO.h"
#include "Game.h"
#include <iostream>
#include <random>

#define LOG(x) std::cout << x << std::endl

void UFO::Shoot(Vector2f direction)
{
	Bullet* bullet = Game::SpawnUFOBullet(direction);
	bullet->setPosition(getPosition());
}

void UFO::Collide()
{
	health--;

	if (health <= 0)
		Game::DeleteUFO(this);
}

void UFO::Update(sf::Time deltaTime)
{

	timeElapsed += deltaTime.asSeconds();

	Vector2f ufoToPlayer = playerRef->getPosition() - getPosition();
	Vector2f UTPNormalized = ufoToPlayer / VectorLenght(ufoToPlayer);

	if (VectorLenght(ufoToPlayer) < 250)
	{
		if (timeElapsed > timePerShot)
		{
			timeElapsed = 0;
			Shoot(UTPNormalized);
		}
	}
	else
	{
		move(ufoToPlayer*speed*deltaTime.asSeconds());
	}

	collision.setPosition(getPosition());
	collision.setRotation(getRotation());
}

UFO::UFO(Player* player, Vector2f direction)
{
	Direction = direction;
	playerRef = player;

	UfoShape = VertexArray(sf::LineStrip, 7);

	UfoShape[0].position = Vector2f(15, 0);
	UfoShape[1].position = Vector2f(20, 5);
	UfoShape[2].position = Vector2f(30, 20);
	UfoShape[3].position = Vector2f(15, 30);
	UfoShape[4].position = Vector2f(0, 20);
	UfoShape[5].position = Vector2f(10, 5);
	UfoShape[5].position = Vector2f(15, 0);

	UfoShape[0].color = sf::Color::White;
	UfoShape[1].color = sf::Color::White;
	UfoShape[2].color = sf::Color::White;
	UfoShape[3].color = sf::Color::White;
	UfoShape[4].color = sf::Color::White;
	UfoShape[5].color = sf::Color::White;
	UfoShape[5].color = sf::Color::White;

	collision = ConvexShape(4);

	collision.setPoint(0, Vector2f(15,0));
	collision.setPoint(1, Vector2f(30,20));
	collision.setPoint(2, Vector2f(15,30));
	collision.setPoint(3, Vector2f(0,20));

	setOrigin(15, 15);
	collision.setOrigin(15, 15);
}

UFO::~UFO()
{
}
