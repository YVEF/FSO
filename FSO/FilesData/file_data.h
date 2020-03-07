#pragma once
#include <string>
#include <Windows.h>
#include "../Helpers/formatting_helper.h"


struct file_data
{
public:
	enum EntryType
	{
		M,
		A,
		R
	};


	file_data();
	file_data(WIN32_FIND_DATA* fileFindData, file_data* parentFileData);

	std::string Id;
	LONGLONG Size;
	DWORD CreatedDateTime;
	DWORD LastModifiedDateTime;
	file_data* ParentFileData;
	EntryType Type;
};

struct file_data_difference
{
public:
	std::string Id;
	std::string Size;
	std::string LastModifiedDateTime;
};


