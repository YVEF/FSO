#include "SharedFunctions.h"

bool shf::IsEquals(char* first, std::string secondString)
{
	std::string firstString(first);
	return firstString == secondString;
}
