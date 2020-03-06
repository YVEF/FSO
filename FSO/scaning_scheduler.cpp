#include "scaning_scheduler.h"

scaning_scheduler::scaning_scheduler(file_system_observer_engine& fileSystemObserverEngine, logger& logger)
	: _fileSystemObserverEngine(fileSystemObserverEngine), _logger(logger)
{
}


void scaning_scheduler::start(RequestData* requestData)
{
	while (true)
	{
		_logger.info("Start scaning");
		_fileSystemObserverEngine.run(requestData);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	}
	


}
