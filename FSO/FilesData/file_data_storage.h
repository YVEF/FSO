#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "file_data.h"
#include "../configuration_manager.h"
#include "../Helpers/formatting_helper.h"
#include "../Helpers/file_data_helper.h"
#include "../change_handler.h"

class file_data_storage
{
private:
	std::string _mappedFilePath;
	int _containerIndex;
	std::vector<file_data*>* _fileContainers[2];
	change_handler& _changeHandler;
	
public:
	file_data_storage(change_handler& changeHandler);
	void add_file(file_data* fileData);
	void flush();
	bool load();
	std::vector<file_data*>* getMainFileContainer();
	std::vector<file_data*>* getNewFileContainer();
	void applyNewContainer(std::vector<file_data*>* newContainer);
};



