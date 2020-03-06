#include "ArgumentParser.h"


WorksType ArgumentParser::GetWorksType(char arg)
{
	switch (arg)
	{
	case 'm':
		return MONITORING;
	case 'r':
		return REPORTING; break;
	default:
		throw std::exception("Not supported argument");
		break;
	}
}

//void AnalyzeCommand(RequestData* data, argument start char** args)
//{
//
//}

RequestData* ArgumentParser::GetRequestData(int argsNumber, char** args)
{
	if (argsNumber <= 1)
		throw std::invalid_argument("Not enough arguments");

	RequestData* rdata = new RequestData();
	rdata->ScaningFrequency = INFINITY;
	rdata->EnableNotification = false;
	for (int i = 1; i < argsNumber; i++)
	{
		if (args[i][0] == '-')
			rdata->WorkType = GetWorksType(args[i][1]);
		else if (args[i][0] == '/')
		{
			std::string command = args[i];
			if (command == "/sf")
			{
				rdata->ScaningFrequency = std::stoi(args[++i]);
			}
			else if (command == "/n")
				rdata->EnableNotification = true;
			else if (command == "/root")
				rdata->RootDirectory = args[++i];
		}
		else if (shf::IsEquals(args[i],"start"))
			rdata->ToStart = true;
		else if (shf::IsEquals(args[i], "stop"))
			rdata->ToStop = true;
		else
			throw std::invalid_argument("Not supported arguments on " + std::to_string(i) + " position");
	}

	return rdata;
}


