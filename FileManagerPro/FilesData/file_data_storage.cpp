#include "file_data_storage.h"

file_data_storage::file_data_storage()
{
	_fileContainer = new std::vector<FileData*>();
}

void file_data_storage::add_file(FileData* fileData)
{
	_fileContainer->push_back(fileData);
}

template <typename TT123>
void T::serialize(TT123& tt)
{
	tt(IntField);
}



void file_data_storage::flush()
{
	std::string path = configuration_manager::get_value("application_folder");
	std::ofstream file;
	file.open(path, std::ios::out | std::ios::binary);
	if (!file.is_open())
		throw std::exception("Could not to open or create the file");

	std::vector<uint8_t> buffer;
	//T t;
	//auto s = bitsery::quickSerialization<OutputAdapter>(buffer, t);
	/*for (auto iterator = _fileContainer->begin(); iterator != _fileContainer->end(); iterator++)
	{
		
		for (auto iter = buffer.begin(); iter != buffer.end(); iter++)
			file << *iter;

		file.flush();
		file.close();
	}*/
}


