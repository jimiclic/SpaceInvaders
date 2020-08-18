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

	// THIS WILL BE MOVED ONCE I MAKE AN ENEMY CLASS
	std::vector<Enemy*> enemies;

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
	void newEnemy(Enemy* enemy);
	void updateEnemy();
	void renderEnemy();

	void pollEvents(); // this is for event polling
	void update(); // this is for the display
	void render();
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
};

class BasicEnemy : public Enemy
{
private:

public:
	BasicEnemy();
	void spawnEnemy(Game* game);
};
#endif
