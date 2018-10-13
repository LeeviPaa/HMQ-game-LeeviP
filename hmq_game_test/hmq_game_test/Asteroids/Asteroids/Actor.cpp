#include "Actor.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

float Actor::VectorLenght(sf::Vector2f Vector)
{
	float lenght = sqrt(pow(Vector.x, 2) + pow(Vector.y, 2));
	return lenght;
}

int Actor::VectorLenght(sf::Vector2i Vector)
{
	int lenght = sqrt(pow(Vector.x, 2) + pow(Vector.y, 2));
	return lenght;
}

void Actor::Update(Time deltaTime)
{

}

