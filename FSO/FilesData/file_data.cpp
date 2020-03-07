#include "file_data.h"



file_data::file_data()
{
    ParentFileData = nullptr;
}

file_data::file_data(WIN32_FIND_DATA* fileFindData, file_data* parentFileData)
{
    LARGE_INTEGER fileSize;

    fileSize.HighPart = fileFindData->nFileSizeHigh;
    fileSize.LowPart = fileFindData->nFileSizeLow;

    CreatedDateTime = fileFindData->ftCreationTime.dwLowDateTime;
    LastModifiedDateTime = fileFindData->ftLastWriteTime.dwLowDateTime;
    Size = fileSize.QuadPart;
    Id = formatting_helper::ToString(fileFindData->cFileName);
    ParentFileData = parentFileData;
}

