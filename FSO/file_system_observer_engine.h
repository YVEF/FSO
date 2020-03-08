#pragma once
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "request_data.h"
#include "Logger.h"
#include "FilesData/file_data.h"
#include "FilesData/file_data_storage.h"
#include "Helpers/formatting_helper.h"
#include "change_handler.h"

class file_system_observer_engine
{
private:
	logger& _logger;
	file_data_storage& _fileDataStorage;
	request_data* _requestData;
	change_handler& _changeHandler;


	void file_processing(WIN32_FIND_DATA* fileFindData, file_data* parentFileData);
	void directory_processing(std::string rootPath, file_data* parentFileData);
public:
	file_system_observer_engine(logger& logger, file_data_storage& fileDataStorage, change_handler& changeHandler);
	void scaning(request_data* requestData);	
};

