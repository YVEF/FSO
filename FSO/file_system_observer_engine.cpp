#include "file_system_observer_engine.h"


file_system_observer_engine::file_system_observer_engine(logger& logger, file_data_storage& fileDataStorage, change_handler& changeHandler)
    : _logger(logger), 
    _fileDataStorage(fileDataStorage),
    _changeHandler(changeHandler)
{
    
}

void file_system_observer_engine::scaning(request_data* requestData)
{
    if (requestData == nullptr)
        throw std::invalid_argument("RequestData was null");

    _requestData = requestData;

    bool wasLoaded = _fileDataStorage.load();    
    directory_processing(_requestData->RootDirectory, nullptr);
    if (wasLoaded)
    {
        auto mainContainer = _fileDataStorage.getMainFileContainer();
        auto newContainer = _fileDataStorage.getNewFileContainer();
        auto diffContainer = _changeHandler.calculateDifference(mainContainer, newContainer);
        _fileDataStorage.applyNewContainer(diffContainer);
    }
    _fileDataStorage.flush();
}




void file_system_observer_engine::directory_processing(std::string rootPath, file_data* parentFileData)
{
    WIN32_FIND_DATA fileFindData;
    HANDLE hFile;
    TCHAR directory[MAX_PATH];
    std::wstring dirPath = std::wstring(rootPath.begin(), rootPath.end());

    StringCchCopy(directory, MAX_PATH, dirPath.c_str());
    StringCchCat(directory, MAX_PATH, TEXT("\\*"));

    hFile = FindFirstFile(directory, &fileFindData);

    if (hFile == INVALID_HANDLE_VALUE)
        throw std::exception("INVALID_HANDLE_VALUE");

    do
    {
        if (fileFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            if (fileFindData.cFileName[0] == '.')
                continue;
            auto newParentFileData = new file_data(&fileFindData, parentFileData);
            newParentFileData->Type = file_data::EntryType::A;
            directory_processing(rootPath + "\\" + formatting_helper::ToString(fileFindData.cFileName), newParentFileData);
        }
        else
            file_processing(&fileFindData, parentFileData);

    } while (FindNextFile(hFile, &fileFindData) != 0);
}



void file_system_observer_engine::file_processing(WIN32_FIND_DATA* fileFindData, file_data* parentFileData)
{
    auto fileData = new file_data(fileFindData, parentFileData);
    fileData->Type = file_data::EntryType::A;
    _fileDataStorage.add_file(fileData);
}
