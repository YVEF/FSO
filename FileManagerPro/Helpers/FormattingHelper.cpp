#include "FormattingHelper.h"

std::string FormattingHelper::ToString(WCHAR* chars)
{
	std::string result;
	for (int i = 0; chars[i] != '\0'; i++)
		result.push_back(chars[i]);
	return result;
}
