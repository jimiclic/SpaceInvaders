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

	// THIS WILL BE MOVED ONCE I MAKE AN ENEMY CLASS
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape basicenemy;

	// Private Functions
	void initializeVariables();
	void initWindow();
	void initBasicEnemy(); // THIS WILL BE MOVED ONCE I MAKE AN ENEMY CLASS

public:
	// Constructor
	Game();
	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Public Functions
	void spawnEnemy(); // THIS WILL BE MOVED ONCE I MAKE AN ENEMY CLASS
	void updateEnemy();
	void renderEnemy();

	void pollEvents(); // this is for event polling
	void update(); // this is for the display
	void render();
};

// I'm working on separating the enemy from the game class
/*
class Enemy
{
public:
	// Constructor
	Enemy();
	// Destructor
	~Enemy();

	// Variables
	int life;
	int damage;

	// Public Functions
	void hitPlayer(); // will hit player for hit points based on damage
};

class BasicEnemy : public Enemy
{
public:
	BasicEnemy();
	~BasicEnemy();

	// Variables for the basicenemy
	sf::RectangleShape basicenemy;
};
*/
#endif
