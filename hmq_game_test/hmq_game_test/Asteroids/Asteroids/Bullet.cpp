#include "Bullet.h"
#include "Game.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

void Bullet::Die()
{
	dead = true;
	Game::DeletePBullet(this);
}

Bullet::Bullet(Vector2f direction)
{
	Direction = direction;
	Shape = CircleShape(2.0f);
	Shape.setFillColor(sf::Color::White);
}

Bullet::~Bullet()
{
	//LOG("Destroyed player bullet!");
}

void Bullet::Update(Time deltaTime)
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

void Bullet::Collide()
{
	Die();
}
