#pragma once
#include <chrono>
#include <thread>
#include "file_system_observer_engine.h"
#include "RequestData.h"
#include "Logger.h"

class scaning_scheduler
{
private:
	file_system_observer_engine& _fileSystemObserverEngine;
	logger& _logger;

public:
	scaning_scheduler(file_system_observer_engine& fileSystemObserverEngine, logger& logger);

	void start(RequestData* requestData);
};

