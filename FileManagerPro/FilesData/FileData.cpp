#include "FileData.h"



FileData::FileData()
{
}

FileData::FileData(WIN32_FIND_DATA* fileFindData, FileData* parentFileData)
{
    LARGE_INTEGER fileSize;

    fileSize.HighPart = fileFindData->nFileSizeHigh;
    fileSize.LowPart = fileFindData->nFileSizeLow;

    CreatedDateTime = fileFindData->ftCreationTime.dwLowDateTime;
    LastModifiedDateTime = fileFindData->ftLastWriteTime.dwLowDateTime;
    Size = fileSize.QuadPart;
    Name = FormattingHelper::ToString(fileFindData->cFileName);
    ParentFileData = parentFileData;
}

//template<typename FD>
//inline void FileData::serialize(FD& fd)
//{
//    fd(Name, Size, CreatedDateTime, LastModifiedDateTime, IsDirectory, ParentFileData);
//}
