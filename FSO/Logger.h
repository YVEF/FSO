#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>

class logger
{
private:
	HANDLE _consoleHandle;

	typedef enum ConsoleColor
	{
		WHITE = 7,
		GREEN = 10,
		BLUE = 11,
		RED = 12
	} CONSOLE_COLOR;


	void Write(CONSOLE_COLOR color, const char* message);
	void Write(CONSOLE_COLOR color, const WCHAR* message, const wchar_t* format);
public:
	logger();

	void info(const char* message);
	void info(const std::string message);
	void info(const WCHAR* message, const char* format);
	void info(const LONGLONG message, const char* format);
	void error(const char* message);
	void error(const std::string message);

};

