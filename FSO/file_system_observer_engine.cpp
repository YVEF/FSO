#include "file_system_observer_engine.h"

file_system_observer_engine::file_system_observer_engine(logger& logger, file_data_storage& fileDataStorage)
    : _logger(logger), _fileDataStorage(fileDataStorage)
{
    
}

void file_system_observer_engine::run(RequestData* requestData)
{
    if (requestData == nullptr)
        throw std::invalid_argument("RequestData was null");

    _requestData = requestData;

    directory_processing(_requestData->RootDirectory, nullptr);
}


void file_system_observer_engine::directory_processing(std::string rootPath, FileData* parentFileData)
{
    WIN32_FIND_DATA fileFindData;
    HANDLE hFile;
    TCHAR directory[MAX_PATH];
    std::wstring dirPath = std::wstring(rootPath.begin(), rootPath.end());


    StringCchCopy(directory, MAX_PATH, dirPath.c_str());
    StringCchCat(directory, MAX_PATH, TEXT("\\*"));

    hFile = FindFirstFile(directory, &fileFindData);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        //_logger.Error("INVALID_HANDLE_VALUE");
        throw std::exception("INVALID_HANDLE_VALUE");
    }


    do
    {
        if (fileFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            if (fileFindData.cFileName[0] == '.')
                continue;
            auto newParentFileData = new FileData(&fileFindData, parentFileData);
            //newParentFileData->IsDirectory = true;
            directory_processing(rootPath + "\\" + FormattingHelper::ToString(fileFindData.cFileName), newParentFileData);
        }
        else
            file_processing(&fileFindData, parentFileData);

    } while (FindNextFile(hFile, &fileFindData) != 0);
}

void file_system_observer_engine::file_processing(WIN32_FIND_DATA* fileFindData, FileData* parentFileData)
{
    auto fileData = new FileData(fileFindData, parentFileData);
    //fileData->IsDirectory = false;

    _fileDataStorage.add_file(fileData);
}
