#include "configuration_manager.h"

//configuration_manager::configuration_manager()
//{
//}

std::string configuration_manager::get_value(std::string key)
{
	if (key == "application_folder")
		return "C:\\Users\\Iaroslav\\source\\repos\\FSO\\tempfiles\\";

	if (key == "system_folder")
		return "C:\\Windows\\";

	return std::string();
}
