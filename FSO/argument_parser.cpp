#include "argument_parser.h"


WorksType argument_parser::GetWorksType(char arg)
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

request_data* argument_parser::GetRequestData(int argsNumber, char** args)
{
	if (argsNumber <= 1)
		throw std::invalid_argument("Not enough arguments");

	request_data* rdata = new request_data();
	//rdata->ScaningFrequency = 5000;
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


