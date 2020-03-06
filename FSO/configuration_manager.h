#pragma once
#include <string>


class configuration_manager
{
public:
	//configuration_manager();
	static std::string get_value(std::string key);
};

