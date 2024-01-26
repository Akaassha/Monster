#pragma once

#include <Windows.h>
#include <string>

enum class ConColor
{
	White,
	Black,
	Red,
	Green,
	Blue
};

class ConsoleManager
{
	static HANDLE Screen;
	static HANDLE Keyboard;

	static WORD TextColor;
	static WORD BackgroundColor;

	const static int consoleWidth = 200;
	const static int consoleHeight = 180;

public:

	static void SetTextColor(ConColor color);
	static void SetBackGroundColor(ConColor color);

	static void SetCursorPosition(COORD newPosition);

	static void PrintString(std::string text);
	static void Clear();

	static void ReadFromKeyboard(char* buffer, DWORD bufferSize);
	static int GetKey();
};