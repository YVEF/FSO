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
{/*

    std::string s = "rhellomhello";
    auto ss = s.find('p', 2);
    auto sss = s.find("hell", 2);
    bool mmm = ss == -1;
    auto m = s.rfind("hel", s.size());*/

    /*auto v = new std::vector<M>();
    M m{ 1 };
    v->push_back(m);
    M m2{ 2 };
    v->push_back(m2);
    M m3{ 3 };
    v->push_back(m3);*/

    //auto s1 = std::find_if(v->begin(), v->end(), [](const M& mm) {return mm.IntField == 1; });
    //auto s2 = std::find_if(v->begin(), v->end(), [](const M& mm) {return mm.IntField == 10; });

    argument_parser argumentParser;
    request_data* requestData = argumentParser.GetRequestData(argsNumber, args);
    logger logger;
    file_data_storage fileDataStorage;
    file_system_observer_engine fsoEngine(logger, fileDataStorage);
    scaning_scheduler scaningScheduler(fsoEngine, logger);
    scaningScheduler.applyRequest(requestData);
}