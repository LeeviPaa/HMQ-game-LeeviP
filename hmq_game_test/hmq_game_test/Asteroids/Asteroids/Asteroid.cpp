#include "Asteroid.h"
#include "Game.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

Asteroid::Asteroid()
{
	shape.setRadius(10);
	shape.setFillColor(sf::Color::Red);
}

Asteroid::~Asteroid()
{
	//LOG("DESTROYED");
}


void Asteroid::Update(sf::Time deltaTime)
{
	if (dead)
		return;

	TimeElapsed += deltaTime.asSeconds();

	move(0.1f, 0.1f);

	if (TimeElapsed > 1)
	{
		Game::DeleteAsteroid(this);
		dead = true;
	}

}
