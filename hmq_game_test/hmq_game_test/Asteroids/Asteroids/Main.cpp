// Tutorial from https://www.sfml-dev.org/tutorials/2.4/start-vc.php

#include <SFML/Graphics.hpp>
#include <iostream>

void Update(sf::Time deltaTime);
void Draw(sf::RenderWindow* window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::Clock clock;




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
}

void Draw(sf::RenderWindow* window)
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window->clear();
	window->draw(shape);
	window->display();
}

