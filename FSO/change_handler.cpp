#include "change_handler.h"


void change_handler::applyChange(std::vector<file_data*>* container, file_data* currentData)
{
    switch (currentData->Type)
    {
    case file_data::EntryType::M: {
        auto previousData = std::find_if(container->begin(), container->end(), [currentData](const file_data* fd) {return fd->Id == currentData->Id; });
        if (previousData == container->end())
            throw std::exception();
        *previousData = currentData;
    }; break;
    case file_data::EntryType::A: container->push_back(currentData); break;
    case file_data::EntryType::R: {
        auto previousData = std::find_if(container->begin(), container->end(), [currentData](const file_data* fd) {return fd->Id == currentData->Id; });
        if (previousData == container->end())
            throw std::exception();
        container->erase(previousData);
    }; break;
    }
}

std::vector<file_data*>* change_handler::calculateDifference(const std::vector<file_data*>* first, const std::vector<file_data*>* second)
{
    bool fileWasChanged;

    auto result = new std::vector<file_data*>();
    for (auto firstIter = first->begin(); firstIter != first->end(); firstIter++)
    {
        fileWasChanged = false;
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

    for (auto secondIter = second->begin(); secondIter != second->end(); secondIter++)
    {
        if (std::find_if(first->begin(), first->end(), [secondIter](const file_data* fd) { return fd->Id == (*secondIter)->Id; }) == first->end())
        {
            auto addedData = new file_data(*secondIter);
            addedData->Type = file_data::A;
            result->push_back(addedData);
        }
    }
    return result;
}