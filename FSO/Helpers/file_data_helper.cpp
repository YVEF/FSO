#include "file_data_helper.h"

const std::string file_data_helper::tokens::CreateDateTime = "&c&";
const std::string file_data_helper::tokens::Id = "&i&";
const std::string file_data_helper::tokens::Type = "&t&";
const std::string file_data_helper::tokens::LastModifiedDateTime = "&l&";
const std::string file_data_helper::tokens::Size = "&s&";
const std::string file_data_helper::tokens::Delimiter = "&>&";



std::string file_data_helper::toLinearizedString(const file_data* fileData)
{
	std::string result;
	for (; fileData != nullptr; fileData = fileData->ParentFileData)
	{
		result += tokens::CreateDateTime + std::to_string(fileData->CreatedDateTime);
		result += tokens::LastModifiedDateTime + std::to_string(fileData->LastModifiedDateTime);
		result += tokens::Id + fileData->Id;
		result += tokens::Type + std::to_string(fileData->Type);		
		result += tokens::Size + std::to_string(fileData->Size);
		result += tokens::Delimiter;
	}
	result.pop_back();
	result.pop_back();
	result.pop_back();

	return result;
}

void file_data_helper::to(size_t* index, const std::string* lineData, std::string key, std::function<void(std::string)> func)
{
	int startIndex = *index + key.size();
	int nextAmp = lineData->find("&", startIndex);
	if (nextAmp == -1)
		nextAmp = lineData->size();
	int length = nextAmp - startIndex;
	func(lineData->substr(startIndex, length));
	*index = length + startIndex;
}

file_data* file_data_helper::toFileData(const std::string lineData)
{

	auto currentFData = new file_data();
	file_data* result = currentFData;
	size_t i = 0;
	int parentDataStartIndex = 0;
	

	while (i < lineData.size())
	{
		parentDataStartIndex = lineData.find(tokens::Delimiter, parentDataStartIndex + 1);
		if (parentDataStartIndex == -1)
			parentDataStartIndex = lineData.size();

		for (; i < parentDataStartIndex;)
		{
			if (lineData.rfind(tokens::CreateDateTime, i) == i)
			{
				to(&i, &lineData, tokens::CreateDateTime, [currentFData](const std::string& ld) {currentFData->CreatedDateTime = formatting_helper::ToDWORD(ld); });
			}
			else if (lineData.rfind(tokens::LastModifiedDateTime, i) == i)
			{
				to(&i, &lineData, tokens::LastModifiedDateTime, [currentFData](const std::string& ld) {currentFData->LastModifiedDateTime = formatting_helper::ToDWORD(ld); });
			}
			else if (lineData.rfind(tokens::Id, i) == i)
			{
				to(&i, &lineData, tokens::Id, [currentFData](const std::string& ld) {currentFData->Id = ld; });
			}
			else if (lineData.rfind(tokens::Type, i) == i)
			{
				to(&i, &lineData, tokens::Type, [currentFData](const std::string& ld) {currentFData->Type = static_cast<file_data::EntryType>(std::stoi(ld)); });
			}
			else if (lineData.rfind(tokens::Size, i) == i)
			{
				to(&i, &lineData, tokens::Size, [currentFData](const std::string& ld)
					{
						std::stringstream stream(ld);
						stream >> currentFData->Size;
					});
			}
		}

		if (parentDataStartIndex != lineData.size())
		{
			currentFData->ParentFileData = new file_data();
			currentFData = currentFData->ParentFileData;
			i += tokens::Delimiter.size();
		}
	}

	return result;

}
