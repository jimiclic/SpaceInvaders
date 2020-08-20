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

class Enemies {
private:
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape basicenemy;

public:
	Enemies() {
		basicenemy.setSize(sf::Vector2f(50.f, 50.f));
		basicenemy.setFillColor(sf::Color(255, 92, 51));
	}

	std::vector<sf::RectangleShape> get_enemies() { return enemies; }

	void spawn(int yPos) {
		basicenemy.setPosition(
			static_cast<float>(1000.f - basicenemy.getSize().x),
			static_cast<float>(rand() % static_cast<int>((yPos - basicenemy.getSize().y)))
		);
		enemies.push_back(this->basicenemy);
	}

	void update(int maxEnemies, float& enemySpawnTimer, float enemySpawnTimerMax, int yPos) {
		if (enemies.size() < maxEnemies)
		{
			if (enemySpawnTimer >= enemySpawnTimerMax)
			{
				enemySpawnTimer = 0.f;
				spawn(yPos);
			}
			else
			{
				enemySpawnTimer += 1.f;
			}
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-3.f, 0.f);

			if (enemies[i].getPosition().x <= 0)
			{
				enemies.erase(enemies.begin() + i);
			}
		}
	}
};

/* MY ENEMY CLASSES
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
	virtual void updateEnemy(Game* game) = 0;
	virtual void renderEnemy(Game* game) = 0;
};

class BasicEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
public:
	BasicEnemy() : Enemy{ 2, 1}
	{
		shape.setPosition(10.f, 10.f);
		shape.setSize(sf::Vector2f(15.f, 15.f));
		shape.setFillColor(sf::Color::Red);

		// this is only if you want an outline around the basic enemy
		/*
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(5.f);
		star/
	}
	void spawnEnemy()
	{
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
		);

		shape.setFillColor(sf::Color::Red);

		enemies.push_back(shape);
	}
	virtual void updateEnemy(Game* game)
	{
		// mechanism for spawning the enemy
		// this is more of a counter for enemy spawning instead of spawning them randomly, I'll work on getting it to be random

		if (static_cast<int>(game->getEnemySpawnTimer()) % 100 == 0)
		{
			spawnEnemy();
		}
		game->updateEnemySpawnTimer();

		// moving all the enemies from right to left by scaling through the enemies vector
		// also removes enemies if they reach the end of the screen
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-5.f, 0.f);

			if (enemies[i].getPosition().x <= 0)
			{
				enemies.erase(enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
			}
		}
	}
	virtual void renderEnemy(Game* game)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			game->drawEnemy(enemies[i]);
		}
	}
};

class DiagEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
public:
	DiagEnemy() : Enemy{ 1, 1 }
	{
		shape.setPosition(10.f, 10.f);
		shape.setSize(sf::Vector2f(25.f, 25.f));
		shape.setFillColor(sf::Color::Magenta);
	}
	void spawnEnemy()
	{
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
		);

		shape.setFillColor(sf::Color::Magenta);

		enemies.push_back(shape);
	}
	virtual void updateEnemy(Game* game)
	{
		if (static_cast<int>(game->getEnemySpawnTimer()) % 200 == 0)
		{
			spawnEnemy();
		}
		// game->updateEnemySpawnTimer(); BasicEnemy::updateEnemy is already updating the timer

		bool atTheTop = false;
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (shape.getPosition().y <= 0) // checking if the shape is at the top to switch movement
			{
				atTheTop = true;
			}
			else if(shape.getPosition().y >= 500)
			{
				atTheTop = false;
			}

			if (atTheTop) // if the shape is at the top it will move down, if the shape is at the bottom it will move up
			{
				enemies[i].move(-5.f, 5.f);
			}
			else
			{
				enemies[i].move(-5.f, -5.f);
			}

			if (enemies[i].getPosition().x <= 0)
			{
				enemies.erase(enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
			}
		}
	}
	virtual void renderEnemy(Game* game)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			game->drawEnemy(enemies[i]);
		}
	}
};
*/