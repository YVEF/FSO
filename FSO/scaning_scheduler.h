#pragma once
#include <chrono>
#include <thread>
#include <exception>
#include "file_system_observer_engine.h"
#include "request_data.h"
#include "Logger.h"

class scaning_scheduler
{
private:
	file_system_observer_engine& _fileSystemObserverEngine;
	logger& _logger;


	void start(request_data* requestData);
	void stop(request_data* requestData);

public:
	scaning_scheduler(file_system_observer_engine& fileSystemObserverEngine, logger& logger);
	void applyRequest(request_data* requestData);
	
};

