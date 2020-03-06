#pragma once
#include <string>

typedef enum WorksType
{
	MONITORING,
	REPORTING
} WORKTYPES;

struct RequestData
{


	std::string RootDirectory;
	bool EnableNotification;
	int ScaningFrequency;
	WORKTYPES WorkType;
	bool ToStart;
	bool ToStop;
};




