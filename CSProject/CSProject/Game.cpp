#include "Game.h"

/*
	This is where I will place all of my definitions from Game.h.
*/

// Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 100.f;
	this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->videomode.height = 500; // sets the height of the window
	this->videomode.width = 1000; // sets the width of the window
	this->window = new sf::RenderWindow(this->videomode, "Title", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
}

void Game::initBasicEnemy()
{
	this->basicenemy.setPosition(10.f, 10.f);
	this->basicenemy.setSize(sf::Vector2f(15.f, 15.f));
	this->basicenemy.setFillColor(sf::Color::Red);

	// this is only if you want an outline around the basic enemy
	/*
	this->basicenemy.setOutlineColor(sf::Color::White);
	this->basicenemy.setOutlineThickness(5.f);
	*/


}


// Constructor
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initBasicEnemy();
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

// Public functions

void Game::spawnEnemy()
{
	this->basicenemy.setPosition(
		static_cast<float>(1000.f - this->basicenemy.getSize().x),
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().y - this->basicenemy.getSize().y)))
	);

	this->basicenemy.setFillColor(sf::Color::Red);

	this->enemies.push_back(this->basicenemy);
}

void Game::updateEnemy()
{
	// mechanism for spawning the enemy
	// this is more of a counter for enemy spawning instead of spawning them randomly, I'll work on getting it to be random
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemySpawnTimer = 0.f;
			this->spawnEnemy();
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	// moving all the enemies from right to left by scaling through the enemies vector
	// also removes enemies if they reach the end of the screen
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(-5.f, 0.f);

		if (this->basicenemy.getPosition().x <= 0)
		{
			this->enemies.erase(this->enemies.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
		}
	}
}

void Game::renderEnemy()
{
	// rendering all the enemies by scaling through the enemies vector
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
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
	this->pollEvents();
	this->updateEnemy();
}

void Game::render()
{
	// Clears old frame
	this->window->clear(); // can clear it with a color too

	// Draws new frame
	this->renderEnemy();

	// Displays new frame
	this->window->display();
}
