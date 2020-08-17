#include<iostream>
#include "Game.h"


int main()
{
	std::srand(static_cast<unsigned>(time(NULL))); // initializes srand

	Game game; // creates game object, which also initializes variables and window


	while (game.running())
	{
		// Update
		game.update();

		// Render
		game.render();
	}

	return 0;
}