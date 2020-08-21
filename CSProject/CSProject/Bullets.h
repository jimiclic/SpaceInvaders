#pragma once
#include <iostream>
#include <vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Bullets {
private:
	std::vector<sf::RectangleShape> bullets;
	sf::RectangleShape singlebullet;
	sf::Texture bulletTexture;

public:
	Bullets() {
		singlebullet.setSize(sf::Vector2f(50.f, 20.f));
		bulletTexture.loadFromFile("missle.png");
		singlebullet.setTexture(&bulletTexture);
		bulletTexture.setSmooth(true);
	}

	std::vector<sf::RectangleShape>* ret_bullets() { return &bullets; }

	void add(int Xpos, int Ypos) {
		singlebullet.setPosition(Xpos + 10, Ypos + 35);
		bullets.push_back(singlebullet);
	}

	void update(bool goingRight) {
		for (int i = 0; i < bullets.size(); i++)
		{
			if (goingRight) {
				bullets[i].move(10.f, 0.f);

				if (this->bullets[i].getPosition().x >= 1000)
				{
					this->bullets.erase(this->bullets.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
				}
			}

			else {
				bullets[i].move(-10.f, 0.f);

				if (this->bullets[i].getPosition().x <= 0)
				{
					this->bullets.erase(this->bullets.begin() + i); // might have to change this to get exact enemy instead of just the last enemy in the vector
				}
			}
		}
	}
};
