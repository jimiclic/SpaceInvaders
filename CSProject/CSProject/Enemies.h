#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

// Game Class forward declaration
class Game;

// MY ENEMY CLASSES

class Enemy
{
private:
	int life;
	int damage;

public:
	sf::RectangleShape shape;
	Enemy(int lifepoints, int damagepoints)
	{
		life = lifepoints;
		damage = damagepoints;
	}
	virtual bool updateEnemy(float& enemySpawnTimer) = 0;
	// virtual void renderEnemy(Game* game) = 0; might not need since we're rendering from game class
};

class BasicEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
	sf::Texture enemyTexture;
public:
	BasicEnemy() : Enemy{ 2, 1}
	{
		shape.setSize(sf::Vector2f(50.f, 50.f));

		enemyTexture.loadFromFile("asteroid.png");
		shape.setTexture(&enemyTexture);
		enemyTexture.setSmooth(true);

		// this is only if you want an outline around the basic enemy
		/*
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(5.f);
		*/
	}
	void spawnEnemy()
	{
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
		);

		enemies.push_back(shape);
	}
	virtual bool updateEnemy(float& enemySpawnTimer)
	{
		int a = 0;
		// mechanism for spawning the enemy
		// this is more of a counter for enemy spawning instead of spawning them randomly, I'll work on getting it to be random

		if (static_cast<int>(enemySpawnTimer) % 100 == 0)
		{
			spawnEnemy();
		}
		enemySpawnTimer += 1.f;

		// moving all the enemies from right to left by scaling through the enemies vector
		// also removes enemies if they reach the end of the screen
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-5.f, 0.f);

			if (enemies[i].getPosition().x <= 0)
			{
				enemies.erase(enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
				a = 1;
			}
		}

		if (a == 1) { return true; }
		return false;
	}

	sf::RectangleShape getBasicEnemies(int i) // to access the enemies vector
	{
		return enemies.at(i);
	}

	const size_t getBasicEnemiesSize() const // to access enemies vector size
	{
		return enemies.size();
	}

	std::vector<sf::RectangleShape>* get_enemies() { return &enemies; }
};

/*
class SnakeEnemy : public BasicEnemy
{

};
*/


class DiagEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
	std::vector<int> randoms;
	sf::Texture diagEnemyTexture;
public:
	DiagEnemy() : Enemy{ 1, 1 }
	{
		shape.setPosition(10.f, 10.f);
		shape.setSize(sf::Vector2f(25.f, 25.f));
		diagEnemyTexture.loadFromFile("diagAsteroid.png");
		shape.setTexture(&diagEnemyTexture);
		diagEnemyTexture.setSmooth(true);
	}
	void spawnEnemy()
	{
		int random = (rand() % 2) + 1;
		randoms.push_back(random);
		if (random == 1)
		{
			shape.setPosition(
				static_cast<float>(1000.f - this->shape.getSize().x),
				static_cast<float>(0.f)
			);
		}
		else
		{
			shape.setPosition(
				static_cast<float>(1000.f - this->shape.getSize().x),
				static_cast<float>(500.f - this->shape.getSize().y)
			);
		}

		enemies.push_back(shape);
	}
	virtual bool updateEnemy(float& enemySpawnTimer)
	{
		int a = 0;
		if (static_cast<int>(enemySpawnTimer) % 200 == 0)
		{
			spawnEnemy();
		}
		// game->updateEnemySpawnTimer(); BasicEnemy::updateEnemy is already updating the timer

		for (size_t i = 0; i < enemies.size(); i++)
		{
			/* enemies bounce code
			bool top = false;
			bool bot = false;
			if (enemies[i].getPosition().y > 0 || enemies[i].getPosition().y < 500 && top == false && bot == false) // if shape is in the middle, it will move either up or down
			{
				
				enemies[i].move(-5.f, -5.f);
			}
			else if (enemies[i].getPosition().y <= 0 && top == true && bot == false) // if the shape is at the top it will move down
			{
				top = true;
				bot = false;
				enemies[i].move(-5.f, 5.f);
			}
			else if (enemies[i].getPosition().y >= 500 && top == false && bot == true) // if the shape is at the bottom, it will move up
			{
				top = false;
				bot = true;
				enemies[i].move(-5.f, -5.f);
			}
			*/

			if (randoms[i] == 1)
			{
				enemies[i].move(-5.f, 2.5f);
			}
			else
			{
				enemies[i].move(-5.f, -2.5f);
			}
			

			if (enemies[i].getPosition().x <= 0)
			{
				a = 1;
				enemies.erase(enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
				randoms.erase(randoms.begin() + i);
			}
		}
		if (a == 1) { return true; }
		return false;
	}
	
	sf::RectangleShape getDiagEnemies(int i) // to access the enemies vector
	{
		return enemies.at(i);
	}

	const size_t getDiagEnemiesSize() const // to access enemies vector size
	{
		return enemies.size();
	}

	std::vector<sf::RectangleShape>* get_enemies() { return &enemies; }
};



class SnakeEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
	sf::Texture enemyTexture;
public:
	SnakeEnemy() : Enemy{ 1, 1 }
	{
		shape.setSize(sf::Vector2f(20.f, 20.f));

		enemyTexture.loadFromFile("asteroid.png");
		shape.setTexture(&enemyTexture);
		enemyTexture.setSmooth(true);
	}

	//fix from here

	void spawnEnemy()
	{
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
		);

		enemies.push_back(shape);
	}
	void spawnEnemyAfter()
	{
		float ypos = shape.getPosition().y;
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			ypos
		);

		enemies.push_back(shape);
	}

	virtual bool updateEnemy(float& enemySpawnTimer)
	{
		int a = 0;
		// mechanism for spawning the enemy
		// this is more of a counter for enemy spawning instead of spawning them randomly, I'll work on getting it to be random

		if (static_cast<int>(enemySpawnTimer) % 300 == 0)
		{
			spawnEnemy();
		}
		if (static_cast<int>(enemySpawnTimer) % 302 == 0)
		{
			spawnEnemyAfter();
		}
		if (static_cast<int>(enemySpawnTimer) % 304 == 0)
		{
			spawnEnemyAfter();
		}
		if (static_cast<int>(enemySpawnTimer) % 306 == 0)
		{
			spawnEnemyAfter();
		}
		if (static_cast<int>(enemySpawnTimer) % 308 == 0)
		{
			spawnEnemyAfter();
		}
		// enemySpawnTimer += 1.f; BasicEnemy::updateEnemy is already updating the timer

		// moving all the enemies from right to left by scaling through the enemies vector
		// also removes enemies if they reach the end of the screen
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-3.f, 0.f);

			if (enemies[i].getPosition().x <= 0)
			{
				enemies.erase(enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
				a = 1;
			}
		}

		if (a == 1) { return true; }
		return false;
	}

	sf::RectangleShape getSnakeEnemies(int i) // to access the enemies vector
	{
		return enemies.at(i);
	}

	const size_t getSnakeEnemiesSize() const // to access enemies vector size
	{
		return enemies.size();
	}

	std::vector<sf::RectangleShape>* get_enemies() { return &enemies; }
};