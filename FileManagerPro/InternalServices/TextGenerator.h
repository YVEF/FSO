#pragma once
#include <random>
#include <fstream>
#include <string>
#include <sstream>


class TextGenerator
{
public:
	void Generate(std::string fileName, size_t lineSize, size_t rowNumber);
};

