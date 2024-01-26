#include "Monster.h"
#include "ConsoleManager.h"

void Monster::Draw()
{
	ConsoleManager::SetBackGroundColor(ConColor::Black);
	ConsoleManager::SetTextColor(ConColor::Red);
	ConsoleManager::SetCursorPosition(position);
	ConsoleManager::PrintString("M");
}