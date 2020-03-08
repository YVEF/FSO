#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "InternalServices/TextGenerator.h"
#include "argument_parser.h"
#include "request_data.h"
#include "file_system_observer_engine.h"
#include "Logger.h"
#include "scaning_scheduler.h"
#include "FilesData/file_data_storage.h"

struct M
{
public:
    int IntField;
};

int main(int argsNumber, char** args)
{
    argument_parser argumentParser;
    request_data* requestData = argumentParser.GetRequestData(argsNumber, args);
    logger logger;
    file_data_storage fileDataStorage;
    file_system_observer_engine fsoEngine(logger, fileDataStorage);
    scaning_scheduler scaningScheduler(fsoEngine, logger);
    scaningScheduler.applyRequest(requestData);
}