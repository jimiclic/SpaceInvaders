#include "Game.h"
#include <cstdlib>
/*
	This is where I will place all of my definitions from Game.h.
*/

void Game::initializeVariables()
{
	this->window = nullptr;
	this->enemySpawnTimer = 0.f;
}

void Game::initWindow()
{
	this->videomode.height = 500; // sets the height of the window
	this->videomode.width = 1000; // sets the width of the window
	this->window = new sf::RenderWindow(this->videomode, "RyBriSteph's Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

// Constructor
Game::Game()
{
	this->initializeVariables();
	this->initWindow();

	user = new Player();
	basicenemy = new BasicEnemy();
	diagenemy = new DiagEnemy();
}

Game::~Game()
{
	delete user;
	delete basicenemy;
	delete diagenemy;
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::renderEnemy()
{
	// rendering all the enemies by scaling through the enemies vector
	for (size_t i = 0; i < basicenemy->getBasicEnemiesSize(); i++)
	{
		this->window->draw(basicenemy->getBasicEnemies(i));
	}
	for (size_t i = 0; i < diagenemy->getDiagEnemiesSize(); i++)
	{
		this->window->draw(diagenemy->getDiagEnemies(i));
	}
}

void Game::renderBullets()
{
	for (auto& e : user->get_bullets()->get_bullets())
	{
		this->window->draw(e);
	}
}

void Game::renderPlayer()
{
	this->window->draw(*(user->get_player()));
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
			if (this->event.key.code == sf::Keyboard::Space)
				user->shoot();
			if (this->event.key.code == sf::Keyboard::Up)
				user->moveUp();
			if (this->event.key.code == sf::Keyboard::Down)
				user->moveDown();
		}
	}
}

void Game::checkCollisions() { //if bullet is 2 units within the enemy, then the user gets a point
	std::vector<sf::RectangleShape>* b = &(user->get_bullets()->get_bullets());
	std::vector<sf::RectangleShape>* e = &(basicenemy->get_enemies());

	//for (int i = 0; i < b->size(); i++) {
	//	for (int j = 0; j < e->size(); j++) {
	//		if (abs((*e)[j].getPosition().x - (*b)[i].getPosition().x) < 10 && abs((*e)[j].getPosition().y - (*b)[i].getPosition().y) < 10) {
	//			b->erase(b->begin() + i);
	//			e->erase(e->begin() + j);
	//			cout << "collision detected" << endl;
	//		}
	//	}
	//}
}

void Game::update()
{
	this->pollEvents();
	basicenemy->updateEnemy(enemySpawnTimer);
	diagenemy->updateEnemy(enemySpawnTimer);
	user->updateBullets();
	//checkCollisions();
}

void Game::render()
{
	// Clears old frame
	this->window->clear(sf::Color(230, 255, 255)); // can clear it with a color too

	// Draws new frame
	this->renderEnemy();
	this->renderBullets();
	this->renderPlayer();

	// Displays new frame
	this->window->display();
}
