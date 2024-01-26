#include "Player.h"
#include "ConsoleManager.h"
#include <time.h>

Player::Player()
{
	srand(time(NULL));
	score = 0;
}

Player::~Player()
{

}

void Player::Move(COORD direction)
{
	position.X += direction.X;
	position.Y += direction.Y;
}

void Player::Leap(COORD arenaSize)
{
	position.X = (rand() % (arenaSize.X - 1) + 1);
	position.Y = (rand() % (arenaSize.Y - 1) + 1);
}

void Player::Draw()
{
	ConsoleManager::SetBackGroundColor(ConColor::White);
	ConsoleManager::SetTextColor(ConColor::Green);
	ConsoleManager::SetCursorPosition(position);
	ConsoleManager::PrintString("P");
}