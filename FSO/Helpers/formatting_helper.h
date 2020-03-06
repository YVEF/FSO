#pragma once
#include <string>
#include <Windows.h>
#include <sstream>
#include "../FilesData/file_data.h"
//
//class file_data;

class formatting_helper
{
public:
	static std::string ToString(const WCHAR* chars);
	static DWORD ToDWORD(const std::string value);
};

