#pragma once
#include <string>
#include <Windows.h>
#include "../Helpers/FormattingHelper.h"
//#include "../bitsery/bitsery.h"
//#include "../bitsery/adapter/buffer.h"
//#include "../bitsery/brief_syntax.h"


struct FileData
{
public:
	FileData();
	FileData(WIN32_FIND_DATA* fileFindData, FileData* parentFileData);

	std::string Name;
	LONGLONG Size;
	DWORD CreatedDateTime;
	DWORD LastModifiedDateTime;
	bool IsDirectory;
	FileData* ParentFileData;

	//template<typename FD>
	//void serialize(FD& fd);
	
};


