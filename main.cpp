#include <iostream>
#include "ConsoleManager.h"
#include "GameManager.h"
#include "Monster.h"

int main()
{
	GameManager game;

	while (game.GetStatus() != EGameStatus::Exit)
	{
		game.Process();
	}
}

