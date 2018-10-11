// Tutorial from https://www.sfml-dev.org/tutorials/2.4/start-vc.php

#include <SFML/Graphics.hpp>
#include "Main.h"
#include "Actor.h"
#include "Player.h"
#include <iostream>

Player PlayerOne;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	sf::Clock clock;

	// Font
	if (!font.loadFromFile("sansation.ttf"))
		return EXIT_FAILURE;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		Update(deltaTime);
		Draw(&window);
	}

	return 0;
}

void Update(sf::Time deltaTime)
{
	std::cout << deltaTime.asMicroseconds() << std::endl;
	PlayerOne.Update(deltaTime);
}

void Draw(sf::RenderWindow* window)
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Text text("Score: "+ PlayerScore, font, 50);

	window->clear();

	window->draw(text);
	window->draw(PlayerOne);

	window->display();
}

