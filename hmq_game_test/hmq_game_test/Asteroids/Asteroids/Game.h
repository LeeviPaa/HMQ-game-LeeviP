#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:
	Player PlayerOne;
	int PlayerScore = 0;

public:

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);

	sf::Font font;
	static sf::Vector2<int> LocalMousePosition;
};

