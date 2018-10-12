#include "PlayerBullet.h"
#include "Game.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

void PlayerBullet::Die()
{
	dead = true;
	Game::DeletePBullet(this);
}

PlayerBullet::PlayerBullet(Vector2f direction)
{
	Direction = direction;
	Shape = CircleShape(2.0f);
	Shape.setFillColor(sf::Color::White);
}

PlayerBullet::~PlayerBullet()
{
	//LOG("Destroyed player bullet!");
}

void PlayerBullet::Update(Time deltaTime)
{
	if (!dead)
	{
		move(Direction*deltaTime.asSeconds()*speed);

		Vector2f position = getPosition();

		if (position.x < -100)
		{
			Die();
		}
		if (position.x > 900)
		{
			Die();
		}
		if (position.y < -100)
		{
			Die();
		}
		if (position.y > 900)
		{
			Die();
		}
	}
}

void PlayerBullet::Collide()
{
	Die();
}
