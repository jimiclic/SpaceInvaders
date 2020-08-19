#include "Game.h"

/*
	This is where I will place all of my definitions from Game.h.
*/

// GAME CLASS

// Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->enemySpawnTimer = 0.f;
}

void Game::initWindow()
{
	this->videomode.height = 500; // sets the height of the window
	this->videomode.width = 1000; // sets the width of the window
	this->window = new sf::RenderWindow(this->videomode, "Title", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
}

// Constructor
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
}

// Destructor
Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const float Game::getEnemySpawnTimer() const
{
	return enemySpawnTimer;
}

// Public functions

void Game::updateEnemySpawnTimer()
{
	enemySpawnTimer += 1.f;
}

void Game::drawEnemy(sf::RectangleShape shape)
{
	window->draw(shape);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed: // Closes window if red x clicked
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) // Closes window if escape key pressed
				this->window->close();
		}
	}
}

void Game::update()
{
	pollEvents();
}

/* // I got rid of this function and made it into two parts: clearWindow and displayWindow
void Game::render()
{
	// Clears old frame
	window->clear();

	// Draws new frame
	basicenemy->renderEnemy(this);

	// Displays new frame
	window->display();
}
*/

void Game::clearWindow()
{
	window->clear();
}

void Game::displayWindow()
{
	window->display();
}


// ENEMY CLASSES

Enemy::Enemy(int lifepoints, int damagepoints)
{
	life = lifepoints;
	damage = damagepoints;
}

BasicEnemy::BasicEnemy() : Enemy{ 2, 1}
{
	this->shape.setPosition(10.f, 10.f);
	this->shape.setSize(sf::Vector2f(15.f, 15.f));
	this->shape.setFillColor(sf::Color::Red);

	// this is only if you want an outline around the basic enemy
	/*
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setOutlineThickness(5.f);
	*/
}

void BasicEnemy::spawnEnemy()
{
	shape.setPosition(
		static_cast<float>(1000.f - this->shape.getSize().x),
		static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
	);

	shape.setFillColor(sf::Color::Red);

	enemies.push_back(shape);
}

void BasicEnemy::updateEnemy(Game* game)
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

void BasicEnemy::renderEnemy(Game* game)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		game->drawEnemy(enemies[i]);
	}
}
