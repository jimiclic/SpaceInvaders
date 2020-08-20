#pragma once
#ifndef GAME_H
#define GAME_H

#include<vector>

#include "Player.h"
#include "Bullets.h"
#include "Enemies.h"

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
	float enemySpawnTimerMax;
	int maxEnemies;

	// Game characters
	Player* user;
	Enemies* enemies;

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

	// Public Functions
	void renderEnemy();
	void renderBullets();
	void renderPlayer();

	void pollEvents(); // this is for event polling
	void update(); // this is for the display
	void render();

	void checkCollisions();
};

#endif