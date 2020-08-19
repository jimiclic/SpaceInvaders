#include<iostream>
#include "Game.h"


int main()
{
	std::srand(static_cast<unsigned>(time(NULL))); // initializes srand

	Game game; // creates game object, which also initializes variables and window
	BasicEnemy basicenemy; // creates basicenemies
	DiagEnemy diagenemy; // creates diagenemies


	while (game.running())
	{
		// Update
		game.update();
		basicenemy.updateEnemy(&game);
		diagenemy.updateEnemy(&game);

		// Render
		game.clearWindow();
		basicenemy.renderEnemy(&game);
		diagenemy.renderEnemy(&game);
		game.displayWindow();
	}

	return 0;
}