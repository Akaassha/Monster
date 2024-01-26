#include "ConsoleManager.h"

#define BACKGROUND_WHITE 0x00F0
#define BACKGROUND_BLACK 0x0000
#define FOREGROUND_WHITE 0x000F
#define FOREGROUND_BLACK 0x0000

HANDLE ConsoleManager::Screen = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE ConsoleManager::Keyboard = GetStdHandle(STD_INPUT_HANDLE);
WORD ConsoleManager::TextColor = FOREGROUND_WHITE;
WORD ConsoleManager::BackgroundColor = BACKGROUND_BLACK;

void ConsoleManager::SetBackGroundColor(ConColor color)
{

	switch (color)
	{
	case ConColor::Black:
		BackgroundColor = BACKGROUND_BLACK;
		break;

	case ConColor::White:
		BackgroundColor = BACKGROUND_WHITE;
		break;

	case ConColor::Red:
		BackgroundColor = BACKGROUND_RED;
		break;

	case ConColor::Green:
		BackgroundColor = BACKGROUND_GREEN;
		break;

	case ConColor::Blue:
		BackgroundColor = BACKGROUND_BLUE;
		break;

	default:
		BackgroundColor = BACKGROUND_BLACK;
	}

	SetConsoleTextAttribute(Screen, TextColor | BackgroundColor);
}

void ConsoleManager::SetTextColor(ConColor color)
{

	switch (color)
	{
	case ConColor::Black:
		TextColor = FOREGROUND_BLACK;
		break;

	case ConColor::White:
		TextColor = FOREGROUND_WHITE;
		break;

	case ConColor::Red:
		TextColor = FOREGROUND_RED;
		break;

	case ConColor::Green:
		TextColor = FOREGROUND_GREEN;
		break;

	case ConColor::Blue:
		TextColor = FOREGROUND_BLUE;
		break;

	default:
		TextColor = FOREGROUND_WHITE;
	}

	SetConsoleTextAttribute(Screen, TextColor | BackgroundColor);
}

void ConsoleManager::SetCursorPosition(COORD newPosition)
{
	SetConsoleCursorPosition(Screen, newPosition);
}

void ConsoleManager::PrintString(std::string text)
{
	DWORD written;
	WriteConsoleA(Screen, text.c_str(), text.size(), &written, NULL);
}

void ConsoleManager::Clear()
{
	COORD start;
	DWORD written;

	start.X = 0;
	start.Y = 0;

	FillConsoleOutputAttribute(Screen, TextColor | BackgroundColor, consoleWidth * consoleHeight, start, &written);
	FillConsoleOutputCharacter(Screen, ' ', consoleWidth * consoleHeight, start, &written);
	SetCursorPosition(start);
}

int ConsoleManager::GetKey()
{
	DWORD read;
	INPUT_RECORD event;

	ReadConsoleInputA(Keyboard, &event, 1, &read);

	if (event.EventType == KEY_EVENT)
	{
		if (event.Event.KeyEvent.bKeyDown)
		{
			return event.Event.KeyEvent.wVirtualKeyCode;
		}
	}

	return 0;
}

void ConsoleManager::ReadFromKeyboard(char* buffer, DWORD bufferSize)
{
	DWORD read;
	ReadConsole(Keyboard, buffer, bufferSize, &read, NULL);
}