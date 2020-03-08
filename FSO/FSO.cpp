#include "InternalServices/TextGenerator.h"
#include "argument_parser.h"
#include "request_data.h"
#include "file_system_observer_engine.h"
#include "Logger.h"
#include "scaning_scheduler.h"
#include "FilesData/file_data_storage.h"
#include "change_handler.h"


int main(int argsNumber, char** args)
{
    argument_parser argumentParser;
    request_data* requestData = argumentParser.GetRequestData(argsNumber, args);
    logger logger;
    change_handler changeHandler;
    file_data_storage fileDataStorage(changeHandler);
    file_system_observer_engine fsoEngine(logger, fileDataStorage, changeHandler);
    scaning_scheduler scaningScheduler(fsoEngine, logger);
    scaningScheduler.applyRequest(requestData);
}