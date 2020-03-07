#include "file_system_observer_engine.h"

file_system_observer_engine::file_system_observer_engine(logger& logger, file_data_storage& fileDataStorage)
    : _logger(logger), _fileDataStorage(fileDataStorage)
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
        auto diffContainer = calculateDifference(mainContainer, newContainer);
        _fileDataStorage.applyNewContainer(diffContainer);
    }
    _fileDataStorage.flush();
}

std::vector<file_data*>* file_system_observer_engine::calculateDifference(const std::vector<file_data*>* first, const std::vector<file_data*>* second)
{
    bool fileWasChanged = false;

    auto result = new std::vector<file_data*>();
    for (auto firstIter = first->begin(); firstIter != first->end(); firstIter++)
    {
        auto secondIter = std::find_if(second->begin(), second->end(), [firstIter](const file_data* fd) { return fd->Id == (*firstIter)->Id; });

        // if second collection has no item, existed in first collection
        if (secondIter == second->end())
        {
            auto removedData = new file_data();
            removedData->Id = (*firstIter)->Id;
            removedData->Type = file_data::R;
            result->push_back(removedData);
            continue;
        }

        auto modifiedData = new file_data();
        if ((*secondIter)->CreatedDateTime != (*firstIter)->CreatedDateTime)
        {
            modifiedData->CreatedDateTime = (*firstIter)->CreatedDateTime;
            fileWasChanged = true;
        }            
        if ((*secondIter)->LastModifiedDateTime != (*firstIter)->LastModifiedDateTime)
        {
            modifiedData->LastModifiedDateTime = (*firstIter)->LastModifiedDateTime;
            fileWasChanged = true;
        }
        if ((*secondIter)->Size != (*firstIter)->Size)
        {
            modifiedData->Size = (*firstIter)->Size;
            fileWasChanged = true;
        }
        if (fileWasChanged)
        {
            modifiedData->Type = file_data::M;
            result->push_back(modifiedData);
        }
    }

    for (auto secondIter = first->begin(); secondIter != first->end(); secondIter++)
    {
        if (std::find_if(second->begin(), second->end(), [secondIter](const file_data* fd) { return fd->Id == (*secondIter)->Id; }) == second->end())
        {
            auto removedData = new file_data();
            removedData->Type = file_data::R;
            removedData->Id = (*secondIter)->Id;
            result->push_back(removedData);
        }
    }
    


    return result;
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
            directory_processing(rootPath + "\\" + formatting_helper::ToString(fileFindData.cFileName), newParentFileData);
        }
        else
            file_processing(&fileFindData, parentFileData);

    } while (FindNextFile(hFile, &fileFindData) != 0);
}



void file_system_observer_engine::file_processing(WIN32_FIND_DATA* fileFindData, file_data* parentFileData)
{
    auto fileData = new file_data(fileFindData, parentFileData);
    _fileDataStorage.add_file(fileData);
}
