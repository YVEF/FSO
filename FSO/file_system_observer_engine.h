#pragma once
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "RequestData.h"
#include "Logger.h"
#include "FilesData/file_data.h"
#include "FilesData/file_data_storage.h"
#include "Helpers/formatting_helper.h"


class file_system_observer_engine
{
private:
	logger& _logger;
	file_data_storage& _fileDataStorage;
	RequestData* _requestData;

public:
	file_system_observer_engine(logger& logger, file_data_storage& fileDataStorage);

	void run(RequestData* requestData);
	void file_processing(WIN32_FIND_DATA* fileFindData, file_data* parentFileData);
	void directory_processing(std::string rootPath, file_data* parentFileData);
};

