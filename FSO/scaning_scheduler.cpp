#include "scaning_scheduler.h"

scaning_scheduler::scaning_scheduler(file_system_observer_engine& fileSystemObserverEngine, logger& logger)
	: _fileSystemObserverEngine(fileSystemObserverEngine), _logger(logger)
{
}

void scaning_scheduler::applyRequest(request_data* requestData)
{
	if (requestData->ToStart)
		start(requestData);
	else if (requestData->ToStop)
		stop(requestData);
	else
		throw std::logic_error("Not supported state");
}


void scaning_scheduler::start(request_data* requestData)
{
	if (requestData->ScaningFrequency == -1)
	{
		_fileSystemObserverEngine.scaning(requestData);
		return;
	}
		

	while (true)
	{
		_logger.info("Start scaning");
		_fileSystemObserverEngine.scaning(requestData);

		std::this_thread::sleep_for(std::chrono::milliseconds(requestData->ScaningFrequency));
	}
}

// it will be accessed through another thread
void scaning_scheduler::stop(request_data* requestData)
{
}
