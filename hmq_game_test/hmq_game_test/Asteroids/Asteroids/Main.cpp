// Tutorial from https://www.sfml-dev.org/tutorials/2.4/start-vc.php

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

#define DEBUG 1

#if DEBUG 
#define LOG(x) std::cout << x << std::endl
#else
#define Log(x)
#endif

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Asteroids by Leevi P.");
	sf::Clock clock;

	float maxFps = 200;
	Game GameLoop;

	// Font
	if (!GameLoop.font.loadFromFile("sansation.ttf"))
		return EXIT_FAILURE;

	int frame = 0;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		GameLoop.Update(deltaTime);
		GameLoop.Draw(&window);
		GameLoop.DeleteObjects();
		sf::sleep(sf::seconds((1 / maxFps)));
	}

	return 0;
}

