#pragma once

#include <Windows.h>
#include <stdio.h>
#include <vector>
#include "ConsoleManager.h"

enum class EGameStatus
{
	MainMenu = 1,
	Running,
	Paused,
	Won,
	LostLife,
	Lost,
	Exit,
	SplashScreen
};

enum class EGameDifficulty
{
	Easy = 1,
	Normal,
	Hard
};

class GameManager
{
	int LastAction;

	EGameStatus GameStatus;
	COORD Arena;
	class Player* player;
	std::vector<class Monster> Monsters;
	int MonstersAmount;

public:
	GameManager();
	~GameManager();

	void DrawMap();
	void DrawMonsters();
	
	void ShowSplash();
	void ShowMenu();
	void ShowGame();
	void ShowWon();
	void ShowLostLife();
	void ShowLost();
	void ShowExit();
	void Show();

	void ProcessSplash();
	void ProcessMenu();
	void ProcessGame();
	void ProcessWon();
	void ProcessLostLife();
	void ProcessLost();
	void ProcessExit();
	void ProcessTurn();
	void Process();

	void StartNewGame(EGameDifficulty Difficulty);
	void EndGame();
	void CheckCollisions();
	int GetAction();
	EGameStatus GetStatus() { return GameStatus; };
	void MoveMonsters();
	bool CheckIfAnyMonsterLeft();
};

