#pragma once
#include <string>

typedef enum WorksType
{
	MONITORING,
	REPORTING
} WORKTYPES;

struct request_data
{
	std::string RootDirectory;
	bool EnableNotification;
	int ScaningFrequency = -1;
	WORKTYPES WorkType;
	bool ToStart;
	bool ToStop;
};




