#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "InternalServices/TextGenerator.h"
#include "ArgumentParser.h"
#include "RequestData.h"
#include "file_system_observer_engine.h"
#include "Logger.h"
#include "scaning_scheduler.h"
#include "FilesData/file_data_storage.h"



int main(int argsNumber, char** args)
{
    ArgumentParser argumentParser;
    RequestData* requestData = argumentParser.GetRequestData(argsNumber, args);
    logger logger;
    file_data_storage fileDataStorage;
    file_system_observer_engine fsoEngine(logger, fileDataStorage);
    scaning_scheduler scaningScheduler(fsoEngine, logger);
    scaningScheduler.start(requestData);
    fileDataStorage.flush();
    

}
