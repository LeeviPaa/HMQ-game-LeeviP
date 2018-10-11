#pragma once
#include <SFML/Graphics.hpp>

void Update(sf::Time deltaTime);
void Draw(sf::RenderWindow* window);

sf::Font font;
int PlayerScore = 0;
