#pragma once
#include <string>
#include <sstream>
#include <functional>
#include "../FilesData/file_data.h"
#include "formatting_helper.h"

class file_data_helper
{
private:
	
	class tokens
	{
	public:
		static const std::string Id;
		static const std::string Type;
		static const std::string CreateDateTime;
		static const std::string LastModifiedDateTime;
		static const std::string Size;
		static const std::string Delimiter;
	};

	static void to(size_t* index, const std::string* lineData, std::string key, std::function<void(std::string)> func);

public:
	static std::string toLinearizedString(const file_data* fileData);
	static file_data* toFileData(const std::string lineData);
};

