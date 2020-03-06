#pragma once
#include <string>
#include "RequestData.h"
#include <limits>
#include <stdexcept>
#include "SharedFunctions.h"



class ArgumentParser
{
private:
	WorksType GetWorksType(char arg);
public:
	
	RequestData* GetRequestData(int argsNumber, char** args);
};

