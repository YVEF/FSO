#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "FileData.h"
#include "../configuration_manager.h"
#include "../bitsery/bitsery.h"
#include "../bitsery/adapter/buffer.h"
#include "../bitsery/brief_syntax.h"
#include "../bitsery/brief_syntax/vector.h"

using OutputAdapter = bitsery::OutputBufferAdapter<std::vector<uint8_t>>;
using InputAdapter = bitsery::InputBufferAdapter<std::vector<uint8_t>>;

class T
{
public:
	int IntField;

	template <typename TT123>
	void serialize(TT123& tt);
	
};


class file_data_storage
{
private:
	std::vector<FileData*>* _fileContainer;

public:
	file_data_storage();
	void add_file(FileData* fileData);
	void flush();
};



