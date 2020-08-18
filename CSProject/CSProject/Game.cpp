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



void Game::newEnemy(Enemy *enemy)
{
	this->enemies.push_back(enemy);
}

void Game::updateEnemy()
{
	// mechanism for spawning the enemy
	// this is more of a counter for enemy spawning instead of spawning them randomly, I'll work on getting it to be random
	
	if (static_cast<int>(enemySpawnTimer) % 100 == 0)
	{
		BasicEnemy spawn;
		spawn.spawnEnemy(this);
	}
	enemySpawnTimer += 1.f;

	// moving all the enemies from right to left by scaling through the enemies vector
	// also removes enemies if they reach the end of the screen
	for (size_t i = 0; i < enemies.size(); i++)
	{
		this->enemies[i]->shape.move(-5.f, 0.f);

		if (enemies[i]->shape.getPosition().x <= 0)
		{
			this->enemies.erase(this->enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector

		}
	}
}
/*
void Game::renderEnemy() // find a way to fix this so it can draw the enemies
{
	// rendering all the enemies by scaling through the enemies vector
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window->draw(enemies[i]->shape);
	}
}
*/
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
	this->pollEvents();
	this->updateEnemy();
}

void Game::render()
{
	// Clears old frame
	this->window->clear(); // can clear it with a color too

	// Draws new frame
	//this->renderEnemy(); // need to fix this function

	// Displays new frame
	this->window->display();
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

void BasicEnemy::spawnEnemy(Game* game)
{
	this->shape.setPosition(
		static_cast<float>(1000.f - this->shape.getSize().x),
		static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
	);

	this->shape.setFillColor(sf::Color::Red);

	game->newEnemy(this);
}