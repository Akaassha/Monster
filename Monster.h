#pragma once
#include <Windows.h>

class Monster
{
	COORD position;
	
public:
	Monster() {};
	~Monster() {};

	void Move(COORD direction);
	COORD GetPosition() { return position; };
	void SetPosition(COORD newPiosition) { position = newPiosition; }
	void Draw();

	bool isDead = false;
};

