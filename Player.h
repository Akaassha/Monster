#pragma once
#include <Windows.h>

class Player
{
	COORD position;
	short lives;
	int score;
	int leaps;

public:
	Player();
	~Player();

	void Move(COORD direction);
	void Leap(COORD arenaSize);

	void Draw();

	COORD GetPosition() { return position; };
	void SetPosition(COORD newPosition) { position = newPosition; };

	void SetLives(short newLives) { lives = newLives; };
	short GetLives() { return lives; };

	void SetScore(int newScore) { score = newScore; };
	int GetScore() { return score; };

	void SetLeaps(int newLeaps) { leaps = newLeaps; };
	int GetLeaps() { return leaps; };
};

