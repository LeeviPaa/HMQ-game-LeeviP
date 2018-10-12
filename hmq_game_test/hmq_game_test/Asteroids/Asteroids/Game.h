#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Asteroid.h"

class Game
{
private:
	Player PlayerOne;
	int PlayerScore = 0;

	//static lists of objects should not leak on the closing of the program
	static std::list<Asteroid> AsteroidsInGame;
	static std::list<Asteroid*> ToBeDeletedAsteroids;
	static std::list<Player> PlayersInGame;


public:

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void DeleteObjects();
	static Asteroid* SpawnAsteroid();
	static bool DeleteAsteroid(Asteroid* deletable);
	bool AsteridIsInList(Asteroid* astero);
	static Player* SpawnPlayer();

	sf::Font font;
	static sf::Vector2<int> LocalMousePosition;
};

