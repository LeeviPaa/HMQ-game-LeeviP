#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Asteroid.h"
#include "PlayerBullet.h"
#include "UFO.h"

class Game
{
private:
	Player PlayerOne;
	int PlayerScore = 0;
	bool gameGoing = true;
	bool prevSpacePressed;
	bool spacePressed;
	int currentDifficulty = 0;

	float AsteroidSpawnTime = 1.f;
	float AsteroidTimeElapsed = 0;

	float UFOSpawnTime = 10;
	float UFOTimeElapsed = 0;

	//static lists of objects should not leak on the closing of the program
	static std::list<Asteroid> AsteroidsInGame;
	static std::list<Asteroid*> ToBeDeletedAsteroids;

	static std::list<Player> PlayersInGame;

	static std::list<PlayerBullet> PBulletsInGame;
	static std::list<PlayerBullet*> ToBeDeletedPBullets;

	static std::list<UFO> UFOsInGame;
	static std::list<UFO*> ToBeDeletedUFO;

	void AsteroidSpawner(float deltaTime);
	void UFOSpawner(float deltaTime);
	void PlayerDeath();
	void RestartGame();


public:

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void DeleteObjects();
	void CheckCollisions();

	static Asteroid* SpawnAsteroid(Vector2f direction, Asteroid::AsteroidType type);
	static bool DeleteAsteroid(Asteroid* deletable);
	bool AsteroidIsInList(Asteroid* astero);

	static PlayerBullet* SpawnPBullet(Vector2f direction);
	static bool DeletePBullet(PlayerBullet* deletable);
	bool PBulletIsInList(PlayerBullet* bullet);

	static UFO* SpawnUFO(Vector2f direction, Player* playerRef);
	static bool DeleteUFO(UFO* deletable);
	bool UFOsInList(UFO* ufo);

	sf::Font font;
	static sf::Vector2<int> LocalMousePosition;
};

