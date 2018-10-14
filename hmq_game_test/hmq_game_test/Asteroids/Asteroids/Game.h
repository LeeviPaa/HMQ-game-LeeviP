#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "UFO.h"

class Game
{
private:
	Player PlayerOne;
	int PlayerScore = 0;
	bool gameGoing = true;
	bool prevSpacePressed;
	bool spacePressed;
	int currentLevel = 1;
	float timePerLevel = 30;
	float levelTimer = 0;

	float changeTimer = 0;
	bool levelChanging = false;
	float levelChangeTextSpeed = 20;
	sf::Text levelChangeText;

	float AsteroidSpawnTime = 1.f;
	float AsteroidTimeElapsed = 0;

	float UFOSpawnTime = 10;
	float UFOTimeElapsed = 0;

	//static lists of objects should not leak on the closing of the program
	static std::list<Asteroid> AsteroidsInGame;
	static std::list<Asteroid*> ToBeDeletedAsteroids;

	static std::list<Player> PlayersInGame;

	static std::list<Bullet> PBulletsInGame;
	static std::list<Bullet*> ToBeDeletedPBullets;

	static std::list<UFO> UFOsInGame;
	static std::list<UFO*> ToBeDeletedUFO;

	static std::list<Bullet> UFOBulletsInGame;
	static std::list<Bullet*> ToBeDeletedUFOBullets;

	void AsteroidSpawner(float deltaTime);
	void UFOSpawner(float deltaTime);
	void LevelChanger(float deltaTime);
	void PlayerDeath();
	void RestartGame();
	void ClearAllObjects();
	void ChangeLevel();
	void UpdateLevelChange(float deltaTime);
	void EndLevelChange();

	float Lerp(float start, float end, float alpha);
	Vector2f Lerp(Vector2f start, Vector2f end, float alpha);

public:

	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void DeleteObjects();
	void CheckCollisions();

	static Asteroid* SpawnAsteroid(Vector2f direction, Asteroid::AsteroidType type);
	static bool DeleteAsteroid(Asteroid* deletable);
	bool AsteroidIsInList(Asteroid* astero);

	static Bullet* SpawnPBullet(Vector2f direction);
	static bool DeletePBullet(Bullet* deletable);
	bool PBulletIsInList(Bullet* bullet);

	static UFO* SpawnUFO(Vector2f direction, Player* playerRef);
	static bool DeleteUFO(UFO* deletable);
	bool UFOsInList(UFO* ufo);

	static Bullet* SpawnUFOBullet(Vector2f direction);
	static bool DeleteUFOBullet(Bullet* deletable);
	bool UFOBulletIsInList(Bullet* bullet);

	sf::Font font;
	static sf::Vector2<int> LocalMousePosition;
};

