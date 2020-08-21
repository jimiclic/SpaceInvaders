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
	for (auto& e : *(user->get_bullets()->ret_bullets()))
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
			if (this->event.key.code == sf::Keyboard::Up || this->event.key.code == sf::Keyboard::W)
				user->moveUp();
			if (this->event.key.code == sf::Keyboard::Down || this->event.key.code == sf::Keyboard::S)
				user->moveDown();
		}
	}
}

bool Game::check_collide(sf::RectangleShape a, sf::RectangleShape b) {
	if (abs(a.getPosition().x - b.getPosition().x) < 40 && abs(a.getPosition().y - b.getPosition().y) < 40) {
		return true;
	}
	return false;
}

void Game::checkCollisions(std::vector<sf::RectangleShape>* b, std::vector<sf::RectangleShape>* e) {
	for (int i = 0; i < b->size(); i++) {
		for (int j = 0; j < e->size(); j++) {
			if (check_collide((*b)[i], (*e)[j])) {
				user->addpoint();
				cout << "SCORE: " << user->get_score() << endl;
				b->erase(b->begin() + i);
				e->erase(e->begin() + j);
			}
		}
	}
}

void Game::update()
{
	this->pollEvents();
	basicenemy->updateEnemy(enemySpawnTimer);
	diagenemy->updateEnemy(enemySpawnTimer);
	user->updateBullets();

	vector<sf::RectangleShape>* b_ptr = user->get_bullets()->ret_bullets();
	vector<sf::RectangleShape>* e_ptr = basicenemy->get_enemies();
	vector<sf::RectangleShape>* d_ptr = diagenemy->get_enemies();

	checkCollisions(b_ptr, e_ptr);
	checkCollisions(b_ptr, d_ptr);
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
