#pragma once
#include <string>
#include "request_data.h"
#include <limits>
#include <stdexcept>
#include "SharedFunctions.h"



class argument_parser
{
private:
	WorksType GetWorksType(char arg);
public:
	
	request_data* GetRequestData(int argsNumber, char** args);
};

