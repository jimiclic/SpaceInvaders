#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace std;

class Game;

class Powerup
{
private:
	int life;
	int damage;

public:
	sf::RectangleShape shape;
	Powerup(int lifepoints, int damagepoints)
	{
		life = lifepoints;
		damage = damagepoints;
	}
	virtual void updatePowerup(float& PowerupTimer) = 0;
};

class BasicPowerup : public Powerup
{
private:
	std::vector<sf::RectangleShape> powerup;
	sf::Texture basicPowerupTexture;
public:
	BasicPowerup() : Powerup{ 2, 1 }
	{
		shape.setSize(sf::Vector2f(40.f, 40.f));
		// shape.setFillColor(sf::Color(124, 252, 0));
		basicPowerupTexture.loadFromFile("plusten.png");
		shape.setTexture(&basicPowerupTexture);
		basicPowerupTexture.setSmooth(true);
	}
	void spawnPowerup()
	{
		shape.setPosition(
			static_cast<float>(1000.f - this->shape.getSize().x),
			static_cast<float>(rand() % static_cast<int>((500.f - this->shape.getSize().y)))
		);

		powerup.push_back(shape);
	}
	virtual void updatePowerup(float& PowerupTimer)
	{
		if (static_cast<int>(PowerupTimer) % 1000 == 0 && static_cast<int>(PowerupTimer) != 0)
		{
			spawnPowerup();
		}
		PowerupTimer += 1.f;

		for (size_t i = 0; i < powerup.size(); i++)
		{
			powerup[i].move(-7.f, 0.f);

			if (powerup[i].getPosition().x <= 0)
			{
				powerup.erase(powerup.begin() + i); 
			}
		}
	}

	sf::RectangleShape getBasicPowerup(int i) 
	{
		return powerup.at(i);
	}

	const size_t getBasicPowerupSize() const
	{
		return powerup.size();
	}

	std::vector<sf::RectangleShape>* get_powerup() { return &powerup; }
};