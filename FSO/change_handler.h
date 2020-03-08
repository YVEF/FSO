#pragma once
#include <vector>
#include "FilesData/file_data.h"

class change_handler
{
public:
	void applyChange(std::vector<file_data*>* container, file_data* current);
	std::vector<file_data*>* calculateDifference(const std::vector<file_data*>* first, const std::vector<file_data*>* second);
};

