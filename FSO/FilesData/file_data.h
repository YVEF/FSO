#pragma once
#include <string>
#include <Windows.h>
#include "../Helpers/formatting_helper.h"


struct file_data
{
public:
	file_data();
	file_data(WIN32_FIND_DATA* fileFindData, file_data* parentFileData);

	std::string Name;
	LONGLONG Size;
	DWORD CreatedDateTime;
	DWORD LastModifiedDateTime;
	bool IsDirectory;
	file_data* ParentFileData;
	
};


