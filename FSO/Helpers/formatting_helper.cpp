#include "formatting_helper.h"

std::string formatting_helper::ToString(const WCHAR* chars)
{
	std::string result;
	for (int i = 0; chars[i] != '\0'; i++)
		result.push_back(chars[i]);
	return result;
}

DWORD formatting_helper::ToDWORD(const std::string value)
{
	DWORD result;
	//value >> result;
	std::stringstream stream(value);
	stream >> result;

	return result;
}



