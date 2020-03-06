#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "file_data.h"
#include "../configuration_manager.h"
#include "../Helpers/formatting_helper.h"
#include "../Helpers/file_data_helper.h"

//class formatting_helper;

class file_data_storage
{
private:
	std::string mappedFilePath;
	std::vector<file_data*>* _fileContainer;

public:
	file_data_storage();
	void add_file(file_data* fileData);
	void flush();
	void load();
};



