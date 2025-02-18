#include "file_data_storage.h"

file_data_storage::file_data_storage(change_handler& changeHandler) :
	_changeHandler(changeHandler)
{
	_containerIndex = 0;
	_mappedFilePath = configuration_manager::get_value("application_folder") + "tempfile.fsofd";
}

void file_data_storage::add_file(file_data* fileData)
{
	_fileContainers[_containerIndex]->push_back(fileData);
}



void file_data_storage::flush()
{
	std::ofstream file;
	file.open(_mappedFilePath, std::ofstream::binary | std::ios_base::app);
	if (!file.is_open())
		throw std::exception("Could not to open or create the file");

	if(_fileContainers[_containerIndex]->size() > 0)
		file << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << std::endl;
	for (auto iterator = _fileContainers[_containerIndex]->begin(); iterator != _fileContainers[_containerIndex]->end(); iterator++)
	{
		auto linearizedString = file_data_helper::toLinearizedString(*iterator);
		file << linearizedString << std::endl;
	}

	file.flush();
	file.close();
	_fileContainers[0]->clear();
	_fileContainers[1]->clear();
	delete _fileContainers[0];
	delete _fileContainers[1];
}

bool file_data_storage::load()
{
	_fileContainers[0] = new std::vector<file_data*>();
	_fileContainers[1] = new std::vector<file_data*>();

	std::ifstream file(_mappedFilePath);
	if (!file.good())
	{
		_containerIndex = 0;
		return false;
	}
	_containerIndex = 1;

		
	if (!file.is_open())
		throw std::exception();
	
	std::stringstream stream;
	std::string line;
	while (std::getline(file, line))
	{
		// if this is timestamp. TODO handle it
		if (line[0] != '&')
			continue;
		_changeHandler.applyChange(_fileContainers[0], file_data_helper::toFileData(line));
	}
		

	return true;
}
std::vector<file_data*>* file_data_storage::getMainFileContainer()
{
	return _fileContainers[0];
}

std::vector<file_data*>* file_data_storage::getNewFileContainer()
{
	return _fileContainers[1];
}

void file_data_storage::applyNewContainer(std::vector<file_data*>* newContainer)
{
	if (newContainer == nullptr)
		throw std::invalid_argument("New Container cannot be null");
	_fileContainers[1]->clear();
	delete _fileContainers[1];
	_fileContainers[1] = newContainer;
}

