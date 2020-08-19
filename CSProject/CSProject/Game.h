#pragma once
#ifndef GAME_H
#define GAME_H

#include<vector>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

/*
	This header file will contain all the declarations of the game class.
	We should also put all the declarations of ememies, the player, bullets, etc. here too.
*/
class Enemy;

class Game
{
private:
	// Variables for the window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event event;

	// Variables for the game objects

	// Game logic
	float enemySpawnTimer;

	// Private Functions
	void initializeVariables();
	void initWindow();

public:
	// Constructor
	Game();
	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;
	const float getEnemySpawnTimer() const;

	// Public Functions
	void updateEnemySpawnTimer(); // increases the enemy spawn timer
	void drawEnemy(sf::RectangleShape shape);

	void pollEvents(); // this is for event polling
	void update(); // this is for the display
	// void render(); // I got rid of this function and made it into two parts: clearWindow and displayWindow
	void clearWindow();
	void displayWindow();
};

// I'm working on separating the enemy from the game class

class Enemy
{
private:
	int life;
	int damage;

public:
	sf::RectangleShape shape;
	Enemy(int lifepoints, int damagepoints);
	virtual void updateEnemy(Game* game) = 0;
	virtual void renderEnemy(Game* game) = 0;
};

class BasicEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
public:
	BasicEnemy();
	void spawnEnemy();
	virtual void updateEnemy(Game* game);
	virtual void renderEnemy(Game* game);
};

class DiagEnemy : public Enemy
{
private:
	std::vector<sf::RectangleShape> enemies;
public:
	DiagEnemy();
	void spawnEnemy();
	virtual void updateEnemy(Game* game);
	virtual void renderEnemy(Game* game);
};
#endif
