#include "file_data_storage.h"

file_data_storage::file_data_storage()
{
	_fileContainer = new std::vector<file_data*>();
	mappedFilePath = configuration_manager::get_value("application_folder") + "tempfile.fsofd";
}

void file_data_storage::add_file(file_data* fileData)
{
	_fileContainer->push_back(fileData);
}




void file_data_storage::flush()
{
	std::ofstream file(mappedFilePath, std::ofstream::binary);
	if (!file.is_open())
		throw std::exception("Could not to open or create the file");

	for (auto iterator = _fileContainer->begin(); iterator != _fileContainer->end(); iterator++)
	{
		auto linearizedString = file_data_helper::toLinearizedString(*iterator);
		file << linearizedString << std::endl;
	}

	file.flush();
	file.close();
	_fileContainer->clear();
	delete _fileContainer;
}

void file_data_storage::load()
{
	_fileContainer = new std::vector<file_data*>();

	std::ifstream file(mappedFilePath);
	if (!file.is_open())
		throw std::exception();

	std::stringstream stream;
	std::string line;
	while (std::getline(file, line))
		_fileContainer->push_back(file_data_helper::toFileData(line));
}


