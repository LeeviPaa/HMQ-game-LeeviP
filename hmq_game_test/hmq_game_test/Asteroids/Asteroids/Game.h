#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Asteroid.h"
#include "PlayerBullet.h"

class Game
{
private:
	Player PlayerOne;
	int PlayerScore = 0;

	float AsteroidSpawnTime = 1;
	float AsteroidTimeElapsed = 0;

	//static lists of objects should not leak on the closing of the program
	static std::list<Asteroid> AsteroidsInGame;
	static std::list<Asteroid*> ToBeDeletedAsteroids;

	static std::list<Player> PlayersInGame;

	static std::list<PlayerBullet> PBulletsInGame;
	static std::list<PlayerBullet*> ToBeDeletedPBullets;

	void AsteroidSpawner(float deltaTime);


public:

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void DeleteObjects();

	static Asteroid* SpawnAsteroid(Vector2f direction);
	static bool DeleteAsteroid(Asteroid* deletable);
	bool AsteroidIsInList(Asteroid* astero);

	static PlayerBullet* SpawnPBullet(Vector2f direction);
	static bool DeletePBullet(PlayerBullet* deletable);
	bool PBulletIsInList(PlayerBullet* bullet);

	static Player* SpawnPlayer();

	sf::Font font;
	static sf::Vector2<int> LocalMousePosition;
};

