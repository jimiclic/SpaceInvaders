#pragma once
#ifndef GAME_H
#define GAME_H

#include<vector>

#include "Player.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Powerup.h"

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
	float PowerupTimer;

	// Game characters
	Player* user;
	BasicEnemy* basicenemy;
	DiagEnemy* diagenemy;
	BasicPowerup* powerup;

	// Private Functions
	void initializeVariables();
	void initWindow();

	void pollEvents(); // this is for event polling

	void showScore();
	void showLives();

	void renderEnemy();
	void renderBullets();
	void renderPlayer();
	void renderPowerup();

	bool check_collide(sf::RectangleShape a, sf::RectangleShape b);
	void checkCollisions(std::vector<sf::RectangleShape>* b, std::vector<sf::RectangleShape>* e);
	void checkPowerupCollisions(std::vector<sf::RectangleShape>* b, std::vector<sf::RectangleShape>* p);

public:
	// Constructor
	Game();
	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Public Functions
	// Public Functions
	void update(); // this is for the display
	void render();
	void end_game();
};

#endif