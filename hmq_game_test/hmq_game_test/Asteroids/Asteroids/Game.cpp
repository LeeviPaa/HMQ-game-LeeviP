#include "Game.h"
#include <iostream>
#include "Actor.h"
#include <string>
#include <random>
#include <math.h>

#define LOG(x) std::cout << x << std::endl

sf::Vector2i Game::LocalMousePosition = Vector2i(0, 0);
std::list<Player> Game::PlayersInGame = std::list<Player>();

std::list<Asteroid> Game::AsteroidsInGame = std::list<Asteroid>();
std::list<Asteroid*> Game::ToBeDeletedAsteroids = std::list<Asteroid*>();

std::list<Bullet> Game::PBulletsInGame = std::list <Bullet>();
std::list<Bullet*> Game::ToBeDeletedPBullets = std::list <Bullet*>();

std::list<UFO> Game::UFOsInGame = std::list <UFO>();
std::list<UFO*> Game::ToBeDeletedUFO = std::list<UFO*>();

std::list<Bullet> Game::UFOBulletsInGame = std::list <Bullet>();
std::list<Bullet*> Game::ToBeDeletedUFOBullets = std::list <Bullet*>();

void Game::Update(sf::Time deltaTime)
{
	prevSpacePressed = spacePressed;
	spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (!gameGoing)
	{
		if (!prevSpacePressed && spacePressed)
		{
			RestartGame();
		}
	}
	else
	{
		PlayerOne.Update(deltaTime);
		UFOSpawner(deltaTime.asSeconds());
		LevelChanger(deltaTime.asSeconds());
	}

	float fps = 1 / deltaTime.asSeconds();
	//LOG(fps);
	
	if (levelChanging)
	{
		UpdateLevelChange(deltaTime.asSeconds());
	}

	//loop for updating all the objects
	std::list<Asteroid>::iterator updateIterator;
	for (updateIterator = AsteroidsInGame.begin(); updateIterator != AsteroidsInGame.end(); updateIterator++)
	{
		Asteroid* asteroid = &*updateIterator;
		asteroid->Update(deltaTime);
	}

	std::list<Bullet>::iterator updateIteratorB;
	for (updateIteratorB = PBulletsInGame.begin(); updateIteratorB != PBulletsInGame.end(); updateIteratorB++)
	{
		Bullet* pbullet = &*updateIteratorB;
		pbullet->Update(deltaTime);
	}

	std::list<UFO>::iterator updateIteratorC;
	for (updateIteratorC = UFOsInGame.begin(); updateIteratorC != UFOsInGame.end(); updateIteratorC++)
	{
		UFO* ufo = &*updateIteratorC;
		ufo->Update(deltaTime);
	}

	std::list<Bullet>::iterator updateIteratorD;
	for (updateIteratorD = UFOBulletsInGame.begin(); updateIteratorD != UFOBulletsInGame.end(); updateIteratorD++)
	{
		Bullet* bullet = &*updateIteratorD;
		bullet->Update(deltaTime);
	}

	AsteroidSpawner(deltaTime.asSeconds());
}

void Game::Draw(sf::RenderWindow* window)
{
	LocalMousePosition = Mouse::getPosition(*window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Text text("Score: " + std::to_string(PlayerScore) , font, 50);
	sf::Text levelText("Level: " + std::to_string(currentLevel) , font, 50);
	levelText.setPosition(0, 50);

	window->clear();

	//loop for drawing all the objects
	std::list<Asteroid>::iterator drawIterator;
	for (drawIterator = AsteroidsInGame.begin(); drawIterator != AsteroidsInGame.end(); drawIterator++)
	{
		window->draw(*drawIterator);
	}

	std::list<Bullet>::iterator drawIteratorB;
	for (drawIteratorB = PBulletsInGame.begin(); drawIteratorB != PBulletsInGame.end(); drawIteratorB++)
	{
		window->draw(*drawIteratorB);
	}

	std::list<Bullet>::iterator drawIteratorD;
	for (drawIteratorD = UFOBulletsInGame.begin(); drawIteratorD != UFOBulletsInGame.end(); drawIteratorD++)
	{
		window->draw(*drawIteratorD);
	}

	std::list<UFO>::iterator drawIteratorC;
	for (drawIteratorC = UFOsInGame.begin(); drawIteratorC != UFOsInGame.end(); drawIteratorC++)
	{
		window->draw(*drawIteratorC);
	}

	if (!gameGoing)
	{
		sf::Text deathText("You are dead! \nPress space to restart.", font, 50);
		deathText.setPosition(150, 350);
		window->draw(deathText);
	}

	window->draw(text);
	window->draw(levelText);
	window->draw(PlayerOne);

	if(levelChanging)
		window->draw(levelChangeText);

	window->display();
}

void Game::CheckCollisions()
{
	if (!gameGoing)
		return;

	//asteroid collisions
	std::list<Asteroid>::iterator asteroidIterator;
	for (asteroidIterator = AsteroidsInGame.begin(); asteroidIterator != AsteroidsInGame.end(); asteroidIterator++)
	{
		Asteroid* asteroid = &*asteroidIterator;
		sf::FloatRect bounds = asteroid->collision.getGlobalBounds();

		//check player collision
		sf::FloatRect playerBounds = PlayerOne.collision.getGlobalBounds();
		if (bounds.intersects(playerBounds))
		{
			PlayerDeath();
		}

		//check collisions against bullets
		std::list<Bullet>::iterator iter;
		for (iter = PBulletsInGame.begin(); iter != PBulletsInGame.end(); iter++)
		{
			//If the bullet collides with an asteroid: do something
			Bullet* bullet = &*iter;
			if (bounds.contains(bullet->getPosition()))
			{
				asteroid->Collide();
				bullet->Collide();

				//add points depending on the size
				switch (asteroid->asteroType)
				{
				case Asteroid::big:
					PlayerScore += 100;
					break;
				case Asteroid::medium:
					PlayerScore += 50;
					break;
				case Asteroid::small:
					PlayerScore += 25;
					break;
				default:
					break;
				}
			}
		}

		//asteroid to asteroid collisions
		//this wasn't required but it's there

		/*std::list<Asteroid>::iterator iterA;
		for(iterA = AsteroidsInGame.begin(); iterA != AsteroidsInGame.end(); iterA++)
		{
			Asteroid* asteroidA = &*iterA;
			sf::FloatRect boundsA = asteroidA->collision.getGlobalBounds();
			if (asteroidIterator != iterA && bounds.intersects(boundsA))
			{
				asteroid->Collide();
				asteroidA->Collide();
			}
		}*/
	}

	std::list<Bullet>::iterator bulletIter;
	for (bulletIter = UFOBulletsInGame.begin(); bulletIter != UFOBulletsInGame.end(); bulletIter++)
	{
		Bullet* bullet = &*bulletIter;
		if (PlayerOne.collision.getGlobalBounds().contains(bullet->getPosition()))
		{
			PlayerDeath();
		}
	}

	//bullets that kill ufos
	std::list<Bullet>::iterator bulletIterA;
	for (bulletIterA = PBulletsInGame.begin(); bulletIterA != PBulletsInGame.end(); bulletIterA++)
	{
		Bullet* bullet = &*bulletIterA;
		
		std::list<UFO>::iterator iter;
		for (iter = UFOsInGame.begin(); iter != UFOsInGame.end(); iter++)
		{
			UFO* ufo = &*iter;
			if (ufo->collision.getGlobalBounds().contains(bullet->getPosition()))
			{
				ufo->Collide();
			}
		}
	}

	//ufos that kill player
	std::list<UFO>::iterator ufoIter;
	for (ufoIter = UFOsInGame.begin(); ufoIter != UFOsInGame.end(); ufoIter++)
	{
		UFO* ufo = &*ufoIter;
		
		if (PlayerOne.collision.getGlobalBounds().intersects(ufo->collision.getGlobalBounds()))
		{
			PlayerDeath();
		}
	}
}

void Game::LevelChanger(float deltaTime)
{
	levelTimer += deltaTime;
	if (levelTimer > timePerLevel)
	{
		levelTimer = 0;
		currentLevel++;
		ClearAllObjects();
		ChangeLevel();
	}
}

void Game::ChangeLevel()
{
	levelChanging = true;
	levelChangeText = sf::Text("Level: " + std::to_string(currentLevel), font, 50);
	levelChangeText.setPosition(-1000, 350);
}

void Game::UpdateLevelChange(float deltaTime)
{
	changeTimer += deltaTime;

	Vector2f currPosition = levelChangeText.getPosition();

	if (changeTimer < 1.4f)
	{
		levelChangeText.setPosition( Lerp(currPosition, Vector2f(300, 350), levelChangeTextSpeed*deltaTime));
	}
	if (changeTimer > 1.6f && changeTimer < 3.f)
	{
		levelChangeText.setPosition(Lerp(currPosition, Vector2f(1000, 350), levelChangeTextSpeed*deltaTime));
	}
	if (changeTimer > 3.f)
	{
		EndLevelChange();
		changeTimer = 0;
	}


}

void Game::EndLevelChange()
{
	levelChanging = false;
}

void Game::AsteroidSpawner(float deltaTime)
{
	AsteroidTimeElapsed += deltaTime;

	if (AsteroidTimeElapsed >= AsteroidSpawnTime)
	{
		AsteroidTimeElapsed = 0;
		
		//select a direction to move
		float direction = (rand() % 2);
		
		Vector2f directionV(0, 0);
		Vector2f position(0,0);

		if (direction == 0)
		{
			directionV = Vector2f(-1, -1);
			//select a spawn point on the direction side

			int randX = (rand() % 6);
			switch (randX)
			{
			case 0:
				position = Vector2f(100, 900);
				break;
			case 1:
				position = Vector2f(400, 900);
				break;
			case 2:
				position = Vector2f(700, 900);
				break;
			case 3:
				position = Vector2f(900, 200);
				break;
			case 4:
				position = Vector2f(900, 500);
				break;
			case 5:
				position = Vector2f(900, 800);
				break;
			default:
				break;
			}
		}
		else
		{
			directionV = Vector2f(1, 1);

			//select a spawn point on the direction side

			int randX = (rand() % 6);
			switch (randX)
			{
			case 0:
				position = Vector2f(-100, 100);
				break;
			case 1:
				position = Vector2f(-100, 400);
				break;
			case 2:
				position = Vector2f(-100, 700);
				break;
			case 3:
				position = Vector2f(200, -100);
				break;
			case 4:
				position = Vector2f(500, -100);
				break;
			case 5:
				position = Vector2f(800, -100);
				break;
			default:
				break;
			}
		}

		Asteroid* astero = SpawnAsteroid(directionV, Asteroid::AsteroidType::big);
		astero->setPosition(position);
	}
}

void Game::UFOSpawner(float deltaTime)
{
	UFOTimeElapsed += deltaTime;

	if (UFOTimeElapsed >= UFOSpawnTime)
	{
		UFOTimeElapsed = 0;
		UFO* ufo = SpawnUFO(Vector2f(1,1), &PlayerOne);
		ufo->setPosition(0, 0);
	}
}

void Game::PlayerDeath()
{
	PlayerOne.Die();
	gameGoing = false;
	LOG("Player died!");
}

void Game::RestartGame()
{
	gameGoing = true;

	currentLevel = 1;
	ClearAllObjects();
	changeTimer = 0;
	EndLevelChange();

	PlayerScore = 0;
	PlayerOne.Reset();
}

void Game::ClearAllObjects()
{
	std::list<Asteroid>::iterator iter;
	for (iter = AsteroidsInGame.begin(); iter != AsteroidsInGame.end(); iter++)
	{
		DeleteAsteroid(&*iter);
	}

	std::list<Bullet>::iterator iterA;
	for (iterA = PBulletsInGame.begin(); iterA != PBulletsInGame.end(); iterA++)
	{
		DeletePBullet(&*iterA);
	}

	std::list<UFO>::iterator iterB;
	for (iterB = UFOsInGame.begin(); iterB != UFOsInGame.end(); iterB++)
	{
		DeleteUFO(&*iterB);
	}

	std::list<Bullet>::iterator iterC;
	for (iterC = UFOBulletsInGame.begin(); iterC != UFOBulletsInGame.end(); iterC++)
	{
		DeleteUFOBullet(&*iterC);
	}
}

void Game::DeleteObjects()
{
	if (!ToBeDeletedAsteroids.empty())
	{

		//clean the asteroid list from objects marked to be deleted
		std::list<Asteroid>::iterator iter;
		for (iter = AsteroidsInGame.begin(); iter != AsteroidsInGame.end();)
		{
			if (AsteroidIsInList(&*iter))
			{
				iter = AsteroidsInGame.erase(iter);
			}
			else
				iter++;
		}

		//loop for finding and deleting the object
		//Here I tried to finally delete the objects
		//
		//only to find that the objects were already deleted at the .erase()
		//and when we clear the list (or at the application closing)

		ToBeDeletedAsteroids.clear();
	}

	if (!ToBeDeletedPBullets.empty())
	{
		std::list<Bullet>::iterator iter;
		for (iter = PBulletsInGame.begin(); iter != PBulletsInGame.end();)
		{
			if (PBulletIsInList(&*iter))
			{
				iter = PBulletsInGame.erase(iter);
			}
			else
				iter++;
		}

		ToBeDeletedPBullets.clear();
	}

	if (!ToBeDeletedUFOBullets.empty())
	{
		std::list<Bullet>::iterator iter;
		for (iter = UFOBulletsInGame.begin(); iter != UFOBulletsInGame.end();)
		{
			if (UFOBulletIsInList(&*iter))
			{
				iter = UFOBulletsInGame.erase(iter);
			}
			else
				iter++;
		}
	}

	if (!ToBeDeletedUFO.empty())
	{
		std::list<UFO>::iterator iter;
		for (iter = UFOsInGame.begin(); iter != UFOsInGame.end();)
		{
			if (UFOsInList(&*iter))
			{
				iter = UFOsInGame.erase(iter);
			}
			else
				iter++;
		}
	}
}

//These are the main spawn functions (static)
//these ensure that the spawned objects are drawn and updated
//these enable checking for collisions
Asteroid* Game::SpawnAsteroid(Vector2f direction, Asteroid::AsteroidType type)
{
	//asteroid is spawned on the scope of this function
	//this gets destroyed at the end of this function
	Asteroid Object(direction, type);
	//a copy is placed in the list
	Game::AsteroidsInGame.push_front(Object);
	std::list<Asteroid>::iterator it = AsteroidsInGame.begin();

	//Note: AFAIK this is not a pointer but a dereference to the iterator position
	//from which we return the memory address
	return &*it;
}
bool Game::DeleteAsteroid(Asteroid* deletable)
{
	//loop for finding and marking the object for deletion
	std::list<Asteroid>::iterator iter;
	for (iter = AsteroidsInGame.begin(); iter != AsteroidsInGame.end(); iter++)
	{
		if (deletable == &*iter)
		{
			//Mark this for deletion
			Game::ToBeDeletedAsteroids.push_front(&*iter);
			return true;
		}
	}
	return false;
}
bool Game::AsteroidIsInList(Asteroid* astero)
{
	std::list<Asteroid*>::iterator iterr;
	for (iterr = ToBeDeletedAsteroids.begin(); iterr != ToBeDeletedAsteroids.end(); )
	{
		//if this object is marked for delete in the list
		if (astero == *iterr)
		{
			return true;
		}
		else
			++iterr;
	}
	return false;
}

Bullet* Game::SpawnPBullet(Vector2f direction)
{
	Bullet Object(direction);
	Game::PBulletsInGame.push_front(Object);
	std::list<Bullet>::iterator it = PBulletsInGame.begin();

	return &*it;
}
bool Game::DeletePBullet(Bullet* deletable)
{
	std::list<Bullet>::iterator iter;
	for (iter = PBulletsInGame.begin(); iter != PBulletsInGame.end(); iter++)
	{
		if (deletable == &* iter)
		{
			Game::ToBeDeletedPBullets.push_front(&*iter);
			return true;
		}
	}
	return false;
}
bool Game::PBulletIsInList(Bullet* bullet)
{
	std::list<Bullet*>::iterator iter;
	for (iter = ToBeDeletedPBullets.begin(); iter != ToBeDeletedPBullets.end();)
	{
		if (bullet == *iter)
		{
			return true;
		}
		else
			++iter;
	}
	return false;
}

UFO * Game::SpawnUFO(Vector2f direction, Player * playerRef)
{
	UFO object(playerRef, direction);
	Game::UFOsInGame.push_front(object);
	std::list<UFO>::iterator it = UFOsInGame.begin();

	return &*it;
}
bool Game::DeleteUFO(UFO * deletable)
{
	std::list<UFO>::iterator iter;
	for (iter = UFOsInGame.begin(); iter != UFOsInGame.end(); iter++)
	{
		if (deletable == &*iter)
		{
			Game::ToBeDeletedUFO.push_front(&*iter);
			return true;
		}
	}
	return false;
}
bool Game::UFOsInList(UFO * ufo)
{
	std::list<UFO*>::iterator iter;
	for (iter = ToBeDeletedUFO.begin(); iter != ToBeDeletedUFO.end();)
	{
		if (ufo == *iter)
		{
			return true;
		}
		else
			++iter;
	}
	return false;
}

Bullet* Game::SpawnUFOBullet(Vector2f direction)
{
	Bullet Object(direction);
	Game::UFOBulletsInGame.push_front(Object);
	std::list<Bullet>::iterator it = UFOBulletsInGame.begin();

	return &*it;
}
bool Game::DeleteUFOBullet(Bullet* deletable)
{
	std::list<Bullet>::iterator iter;
	for (iter = UFOBulletsInGame.begin(); iter != UFOBulletsInGame.end(); iter++)
	{
		if (deletable == &* iter)
		{
			Game::ToBeDeletedUFOBullets.push_front(&*iter);
			return true;
		}
	}
	return false;
}
bool Game::UFOBulletIsInList(Bullet* bullet)
{
	std::list<Bullet*>::iterator iter;
	for (iter = ToBeDeletedUFOBullets.begin(); iter != ToBeDeletedUFOBullets.end();)
	{
		if (bullet == *iter)
		{
			return true;
		}
		else
			++iter;
	}
	return false;
}

float Game::Lerp(float start, float end, float alpha)
{
	return (start + alpha * (end - start));
}

Vector2f Game::Lerp(Vector2f start, Vector2f end, float alpha)
{
	return (start + alpha * (end - start));
}
