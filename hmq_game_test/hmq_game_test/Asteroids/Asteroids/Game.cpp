#include "Game.h"
#include <iostream>
#include "Actor.h"
#include <string>

#define LOG(x) std::cout << x << std::endl

sf::Vector2i Game::LocalMousePosition = Vector2i(0, 0);
std::list<Player> Game::PlayersInGame = std::list<Player>();

std::list<Asteroid> Game::AsteroidsInGame = std::list<Asteroid>();
std::list<Asteroid*> Game::ToBeDeletedAsteroids = std::list<Asteroid*>();

std::list<PlayerBullet> Game::PBulletsInGame = std::list <PlayerBullet>();
std::list<PlayerBullet*> Game::ToBeDeletedPBullets = std::list <PlayerBullet*>();


void Game::Update(sf::Time deltaTime)
{
	float fps = 1 / deltaTime.asSeconds();
	//LOG(fps);
	
	PlayerOne.Update(deltaTime);

	//loop for updating all the objects
	std::list<Asteroid>::iterator updateIterator;
	for (updateIterator = AsteroidsInGame.begin(); updateIterator != AsteroidsInGame.end(); updateIterator++)
	{
		Asteroid* asteroid = &*updateIterator;
		asteroid->Update(deltaTime);
	}

	std::list<PlayerBullet>::iterator updateIteratorB;
	for (updateIteratorB = PBulletsInGame.begin(); updateIteratorB != PBulletsInGame.end(); updateIteratorB++)
	{
		PlayerBullet* pbullet = &*updateIteratorB;
		pbullet->Update(deltaTime);
	}
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

	//loop for drawing all the objects
	std::list<Asteroid>::iterator drawIterator;
	for (drawIterator = AsteroidsInGame.begin(); drawIterator != AsteroidsInGame.end(); drawIterator++)
	{
		window->draw(*drawIterator);
	}

	std::list<PlayerBullet>::iterator drawIteratorB;
	for (drawIteratorB = PBulletsInGame.begin(); drawIteratorB != PBulletsInGame.end(); drawIteratorB++)
	{
		window->draw(*drawIteratorB);
	}

	window->draw(text);
	window->draw(PlayerOne);

	window->display();
}

//This is the main spawn function (static)
//this ensures that the spawned objects are drawn and updated
//this enables checking for collisions

Player * Game::SpawnPlayer()
{
	return nullptr;
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
		std::list<PlayerBullet>::iterator iter;
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
}

Asteroid* Game::SpawnAsteroid()
{
	//asteroid is spawned on the scope of this function
	//this gets destroyed at the end of this function
	Asteroid Object;
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

PlayerBullet* Game::SpawnPBullet(Vector2f direction)
{
	PlayerBullet Object(direction);
	Game::PBulletsInGame.push_front(Object);
	std::list<PlayerBullet>::iterator it = PBulletsInGame.begin();

	return &*it;
}
bool Game::DeletePBullet(PlayerBullet* deletable)
{
	std::list<PlayerBullet>::iterator iter;
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
bool Game::PBulletIsInList(PlayerBullet* bullet)
{
	std::list<PlayerBullet*>::iterator iter;
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