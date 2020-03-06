#include "Logger.h"

void logger::Write(CONSOLE_COLOR color, const char* message)
{
	SetConsoleTextAttribute(_consoleHandle, color);
	std::cout << message << std::endl;
}

void logger::Write(CONSOLE_COLOR color, const WCHAR* message, const wchar_t* format)
{
	SetConsoleTextAttribute(_consoleHandle, color);	
	_tprintf(format, message);
}

logger::logger()
{
	_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void logger::info(const char* message)
{
	Write(WHITE, message);
}

void logger::info(const std::string message)
{
	Write(WHITE, message.c_str());
}

void logger::info(const WCHAR* message, const char* format)
{
	SetConsoleTextAttribute(_consoleHandle, WHITE);
	std::string formatString(format);
	_tprintf(std::wstring(formatString.begin(), formatString.end()).c_str(), message);
}

void logger::info(const LONGLONG message, const char* format)
{
	SetConsoleTextAttribute(_consoleHandle, WHITE);
	std::string formatString(format);
	_tprintf(std::wstring(formatString.begin(), formatString.end()).c_str(), message);
}

void logger::error(const char* message)
{
	Write(RED, message);
}

void logger::error(const std::string message)
{
	Write(RED, message.c_str());
}
