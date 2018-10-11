#include "Game.h"
#include <iostream>
#include "Actor.h"
#include <string>

#define LOG(x) std::cout << x << std::endl

sf::Vector2i Game::LocalMousePosition = Vector2i(0, 0);

void Game::Update(sf::Time deltaTime)
{
	//std::cout << deltaTime.asMicroseconds() << std::endl;
	
	PlayerOne.Update(deltaTime);
}

void Game::Draw(sf::RenderWindow* window)
{
	LocalMousePosition = Mouse::getPosition(*window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Text text("Score: " + std::to_string(PlayerScore) , font, 50);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		PlayerScore++;
	}

	window->clear();

	window->draw(text);
	window->draw(PlayerOne);

	window->display();
}
