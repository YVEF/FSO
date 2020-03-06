#pragma once
#include <string>
#include "RequestData.h"
#include <limits>
#include <stdexcept>
#include "SharedFunctions.h"



class argument_parser
{
private:
	WorksType GetWorksType(char arg);
public:
	
	RequestData* GetRequestData(int argsNumber, char** args);
};

