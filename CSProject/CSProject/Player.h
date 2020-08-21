#pragma once
#include <iostream>
#include <vector>
#include "Bullets.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Player {
private:
	int points;
	sf::CircleShape* player;
	Bullets* bullets;
	sf::Texture playerTexture;

public:

	Player() {
		player = new sf::CircleShape;

		player->setRadius(50);
		player->setPosition(50, 250);

		playerTexture.loadFromFile("spaceship.png");
		player->setTexture(&playerTexture, true);
		playerTexture.setSmooth(true);

		bullets = new Bullets;

		points = 0;
	}

	~Player() {
		delete player;
		delete bullets;
	}

	void shoot() {
		bullets->add(50, player->getPosition().y);
	}

	void updateBullets() {
		bullets->update(true);
	}

	Bullets* get_bullets() { return bullets; }

	sf::CircleShape* get_player() { return player; }

	void moveUp() {
		if (player->getPosition().y < 0) {
			sf::Vector2f pos = player->getPosition();
			player->setPosition(pos.x, 0);
		}
		else {
			for (int i = 0; i < 10; i++) {
				player->move(0.f, -3.f);
			}
		}
	}

	void moveDown() {
		if (player->getPosition().y > 420) {
			sf::Vector2f pos = player->getPosition();
			player->setPosition(pos.x, 420);
		}
		else {
			for (int i = 0; i < 10; i++) {
				player->move(0.f, 3.f);
			}
		}
	}

	void addpoint(int amount) {
		points += amount;
	}

	int get_score() { return points; }

};
