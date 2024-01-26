#include "GameManager.h"
#include "Monster.h"
#include "Player.h"
#include <string>
#include <time.h>

bool operator==(COORD loc1, COORD loc2)
{
	if (loc1.X == loc2.X && loc1.Y == loc2.Y)
		return true;
	else
		return false;
}

COORD operator+(COORD pos1, COORD pos2)
{
	COORD pos;
	pos.X = pos1.X + pos2.X;
	pos.Y = pos1.Y + pos2.Y;
	return pos;
}

GameManager::GameManager()
{
	GameStatus = EGameStatus::SplashScreen;
	player = new Player;
	LastAction = 0;
	MonstersAmount = 0;
	Arena.X = 0;
	Arena.Y = 0;
}

GameManager::~GameManager()
{
	delete player;
}

void GameManager::ShowSplash()
{
	ConsoleManager::Clear();
	ConsoleManager::PrintString("Welcome to Monster 1.0\n");

	ConsoleManager::PrintString("The objective of the game is to destroy \n");
	ConsoleManager::PrintString("all the monsters. Two or more monsters \n");
	ConsoleManager::PrintString("are destroyed when they move to the \n");
	ConsoleManager::PrintString("same cell in the field. You also lose a \n");
	ConsoleManager::PrintString("life if you move to a cell where a \n");
	ConsoleManager::PrintString("monster is. You move the player with the \n");
	ConsoleManager::PrintString("numerical keypad in the eight possible \n");
	ConsoleManager::PrintString("directions. You can also press Space \n");
	ConsoleManager::PrintString("which will make you leap to a random \n");
	ConsoleManager::PrintString("place in the field.\n\n");

	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::PrintString("NOTE: Make sure NumLock is turned off.\n\n");
	ConsoleManager::SetTextColor(ConColor::White);

	ConsoleManager::PrintString("There are three difficulties available:\n\n");
	ConsoleManager::PrintString(" Easy : Monsters = 10 Arena = 25*15\n");
	ConsoleManager::PrintString(" Lives = 4 Leaps = 3\n");
	ConsoleManager::PrintString(" Medium : Monsters = 20 Arena = 35*18\n");
	ConsoleManager::PrintString(" Hard : Monsters = 30 Arena = 50*23\n");
	ConsoleManager::PrintString(" Lives = 2 Leaps = 1\n");

}

void GameManager::ShowMenu()
{
	COORD cursorPos;

	ConsoleManager::SetBackGroundColor(ConColor::Black);
	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::Clear();

	ConsoleManager::SetBackGroundColor(ConColor::White);

	ConsoleManager::PrintString("                       \n");
	ConsoleManager::PrintString(" Monster - version 1.0 \n");
	ConsoleManager::PrintString("                       \n");

	ConsoleManager::SetBackGroundColor(ConColor::Black);
	ConsoleManager::SetTextColor(ConColor::White);

	cursorPos.X = 1;
	cursorPos.Y = 4;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("What do you want to do?");

	cursorPos.X = 3;
	cursorPos.Y = 6;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("1 - Start new game - Easy");
	cursorPos.Y = 7;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("2 - Start new game - Medium");
	cursorPos.Y = 8;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("3 - Start new game - Hard");

	cursorPos.Y = 10;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("Q - Exit game");

}

void GameManager::ShowGame()
{
	COORD cursorPos;
	
	DrawMap();
	player->Draw();
	DrawMonsters();

	char Buffer[100];
	sprintf_s(Buffer, "Lives: %d \t\t Score: %d \t Leaps: %d", player->GetLives() - 1, player->GetScore(), player->GetLeaps());

	cursorPos.X = 5;
	cursorPos.Y = 24;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::SetTextColor(ConColor::Green);
	ConsoleManager::PrintString(Buffer);
}

void GameManager::DrawMap()
{
	COORD cursorPos;
	int MapX, MapY;

	ConsoleManager::SetBackGroundColor(ConColor::White);
	ConsoleManager::SetTextColor(ConColor::White);

	for (MapY = 0; MapY < Arena.Y+1; MapY++)
	{
		if ((MapY == 0) || (MapY == Arena.Y))
		{
			for (MapX = 0; MapX <= Arena.X; MapX++)
			{
				cursorPos.X = MapX;
				cursorPos.Y = MapY;
				ConsoleManager::SetCursorPosition(cursorPos);
				ConsoleManager::PrintString("#");
			}
		}
		else
		{
			cursorPos.X = 0;
			cursorPos.Y = MapY;
			ConsoleManager::SetCursorPosition(cursorPos);
			ConsoleManager::PrintString("#");

			cursorPos.X = Arena.X;
			cursorPos.Y = MapY;
			ConsoleManager::SetCursorPosition(cursorPos);
			ConsoleManager::PrintString("#");
		}
	}
}

void GameManager::DrawMonsters()
{
	for (auto monster : Monsters)
	{
		if (!monster.isDead)
		{
			monster.Draw();
		}
	}
}

void GameManager::ShowWon()
{
	ShowGame();

	COORD cursorPos;
	cursorPos.X = 20;
	cursorPos.Y = 11;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::SetBackGroundColor(ConColor::Green);
	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::PrintString("#################################");
	cursorPos.Y = 12;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#       Congratulations!        #");
	cursorPos.Y = 13;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("# You have killed all monsters. $");
	cursorPos.Y = 14;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#################################");

}

void GameManager::ShowLostLife()
{
	ShowGame();

	COORD cursorPos;
	cursorPos.X = 20;
	cursorPos.Y = 11;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::SetBackGroundColor(ConColor::Green);
	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::PrintString("#################################");
	cursorPos.Y = 12;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#              Oops!            #");
	cursorPos.Y = 13;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#    You have lost Your live.   #");
	cursorPos.Y = 14;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#################################");
}

void GameManager::ShowLost()
{
	ShowGame();

	COORD cursorPos;
	cursorPos.X = 20;
	cursorPos.Y = 11;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::SetBackGroundColor(ConColor::Green);
	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::PrintString("#################################");
	cursorPos.Y = 12;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#         Thoug Luck!           #");
	cursorPos.Y = 13;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("# You have lost all Your lives. #");
	cursorPos.Y = 14;
	ConsoleManager::SetCursorPosition(cursorPos);
	ConsoleManager::PrintString("#################################");
}

void GameManager::ShowExit()
{

}

void GameManager::Show()
{
	ConsoleManager::SetBackGroundColor(ConColor::Black);
	ConsoleManager::SetTextColor(ConColor::White);
	ConsoleManager::Clear();

	switch (GameStatus)
	{
	case EGameStatus::MainMenu:
		ShowMenu();
		break;

	case EGameStatus::Running:
		ShowGame();
		break;

	case EGameStatus::Won:
		ShowWon();
		break;

	case EGameStatus::LostLife:
		ShowLostLife();
		break;

	case EGameStatus::Exit:
		ShowExit();
		break;

	case EGameStatus::SplashScreen:
		ShowSplash();
		break;
	
	default:
		break;
	}
}

void GameManager::StartNewGame(EGameDifficulty difficulty)
{
	GameStatus = EGameStatus::Running;

	switch (difficulty)
	{
	case EGameDifficulty::Easy:
		MonstersAmount = 10;
		player->SetLives(4);
		player->SetLeaps(3);
		Arena.X = 25;
		Arena.Y = 15;
		break;

	case EGameDifficulty::Normal:
		MonstersAmount = 25;
		player->SetLives(3);
		player->SetLeaps(2);
		Arena.X = 35;
		Arena.Y = 18;
		break;

	case EGameDifficulty::Hard:
		MonstersAmount = 35;
		player->SetLives(1);
		player->SetLeaps(1);
		Arena.X = 50;
		Arena.Y = 23;
		break;
	}

	player->Leap(Arena);

	srand(time(NULL));
	COORD randPos;
	for (int i =0; i < MonstersAmount; ++i)
	{
		do
		{
			randPos.X = (rand() % (Arena.X - 1) + 1);
			randPos.Y = (rand() % (Arena.Y - 1) + 1);
			Monster monster;
			monster.SetPosition(randPos);
			Monsters.push_back(monster);
		} while (Monsters[i].GetPosition() == player->GetPosition());
		
	}

}

int GameManager::GetAction()
{
	LastAction = ConsoleManager::GetKey();
	return LastAction;
}

void GameManager::MoveMonsters()
{
	COORD distanceToPlayer;
	distanceToPlayer.X = 0;
	distanceToPlayer.Y = 0;

	for (auto& monster : Monsters)
	{
		if (!monster.isDead)
		{
			distanceToPlayer.X = player->GetPosition().X - monster.GetPosition().X;
			distanceToPlayer.Y = player->GetPosition().Y - monster.GetPosition().Y;

			if (distanceToPlayer.X > 0) distanceToPlayer.X = 1;
			if (distanceToPlayer.X < 0) distanceToPlayer.X = -1;
			if (distanceToPlayer.Y > 0) distanceToPlayer.Y = 1;
			if (distanceToPlayer.Y < 0) distanceToPlayer.Y = -1;

			monster.SetPosition(monster.GetPosition() + distanceToPlayer);
		}
	}

}

void GameManager::ProcessSplash()
{
	if (LastAction) {
		GameStatus = EGameStatus::MainMenu;
	}
}

void GameManager::ProcessMenu()
{
	switch (LastAction)
	{
	case VK_ESCAPE:
	case 'Q':
	case 'q':
		GameStatus = EGameStatus::Exit;
		break;

	case '1':
		GameStatus = EGameStatus::Running;
		StartNewGame(EGameDifficulty::Easy);
		break;

	case '2':
		GameStatus = EGameStatus::Running;
		StartNewGame(EGameDifficulty::Normal);
		break;

	case '3':
		GameStatus = EGameStatus::Running;
		StartNewGame(EGameDifficulty::Hard);
		break;

	default:
		break;
	}
}

void GameManager::ProcessGame()
{
	ConsoleManager::Clear();
	COORD movement; 
	int MonstersAlived;

	movement.X = 0;
	movement.Y = 0;

	switch (LastAction)
	{
	case VK_UP:
		movement.Y = -1;
		break;

	case VK_DOWN:
		movement.Y = 1;
		break;

	case VK_LEFT:
		movement.X = -1;
		break;

	case VK_RIGHT:
		movement.X = 1;
		break;

	case VK_SPACE:
		if (player->GetLeaps() > 0)
		{
			player->Leap(Arena);
			player->SetLeaps(player->GetLeaps() - 1);
		}
		break;

	}

	if ((movement.X != 0) || (movement.Y != 0))
	{
		if ((movement.X + player->GetPosition().X > 0) &&
			(movement.Y + player->GetPosition().Y > 0) &&
			(movement.X + player->GetPosition().X < Arena.X) &&
			(movement.Y + player->GetPosition().Y < Arena.Y))
		{
			player->Move(movement);
		}
	}

	MoveMonsters();
	CheckCollisions();

	if (!CheckIfAnyMonsterLeft())
	{
		GameStatus = EGameStatus::Won;
	}
}

bool GameManager::CheckIfAnyMonsterLeft()
{
	for (auto monster: Monsters)
	{
		if (!monster.isDead)
		{
			return true;
		}
	}

	return false;
}

void GameManager::CheckCollisions()
{
	COORD originPos;
	originPos.X = 0;
	originPos.Y = 0;

	for (auto monster : Monsters)
	{
		if (!monster.isDead)
		{
			if (monster.GetPosition() == player->GetPosition())
			{
				monster.isDead = true;
				monster.SetPosition(originPos);

				if (player->GetLives() - 1 <= 0)
				{
					GameStatus = EGameStatus::Lost;
				}
				else
				{
					GameStatus = EGameStatus::LostLife;
				}
				return;
			}
		}

		for (auto OtherMonster : Monsters)
		{
			if (!OtherMonster.isDead)
			{
				if (&OtherMonster == &monster) continue;

				if (monster.GetPosition() == OtherMonster.GetPosition())
				{
					monster.SetPosition(originPos);
					monster.isDead = true;
					OtherMonster.SetPosition(originPos);
					OtherMonster.isDead = true;
					
					player->SetScore(player->GetScore() + 15);
				}
			}
		}

	}
}

void GameManager::ProcessWon()
{
	if (LastAction)
	{
		GameStatus = EGameStatus::MainMenu;
	}

	EndGame();
}

void GameManager::EndGame()
{
	if (Monsters.size() != 0)
	{
		Monsters.empty();
	}
}

void GameManager::ProcessLostLife()
{
	player->SetLives(player->GetLives() - 1);
	if (player->GetLives() < 0)
	{
		GameStatus = EGameStatus::Lost;
	}
	else
	{
		bool isValid = false;
		GameStatus = EGameStatus::Running;
		do
		{
			player->Leap(Arena);
			for (auto monster : Monsters)
			{
				if (monster.GetPosition() == player->GetPosition())
				{
					isValid = true;
					break;
				}
			}

			isValid = false;
		} while (isValid);
	}
}

void GameManager::ProcessLost()
{
	if (LastAction)
	{
		GameStatus = EGameStatus::MainMenu;
	}

	EndGame();
	Show();
}

void GameManager::Process()
{
	if (GameStatus == EGameStatus::SplashScreen)
	{
		Show();
	}

	if (GetAction())
	{
		switch (GameStatus)
		{
		case EGameStatus::MainMenu:
			ProcessMenu();
			break;

		case EGameStatus::Running:
			ProcessGame();
			break;

		case EGameStatus::Won:
			ProcessWon();
			break;

		case EGameStatus::Lost:
			ProcessLost();
			break;

		case EGameStatus::LostLife:
			ProcessLostLife();
			break;

		case EGameStatus::SplashScreen:
			ProcessSplash();
			break;

		default:
			break;
		}

		Show();
	}
}