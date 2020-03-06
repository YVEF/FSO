#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "InternalServices/TextGenerator.h"
#include "argument_parser.h"
#include "RequestData.h"
#include "file_system_observer_engine.h"
#include "Logger.h"
#include "scaning_scheduler.h"
#include "FilesData/file_data_storage.h"



int main(int argsNumber, char** args)
{

    std::string s = "rhellomhello";
    auto ss = s.find('p', 2);
    auto sss = s.find("hell", 2);
    bool mmm = ss == -1;
    auto m = s.rfind("hel", s.size());

    argument_parser argumentParser;
    RequestData* requestData = argumentParser.GetRequestData(argsNumber, args);
    logger logger;
    file_data_storage fileDataStorage;
    file_system_observer_engine fsoEngine(logger, fileDataStorage);
    scaning_scheduler scaningScheduler(fsoEngine, logger);
    scaningScheduler.start(requestData);
    fileDataStorage.flush();
    fileDataStorage.load();

}