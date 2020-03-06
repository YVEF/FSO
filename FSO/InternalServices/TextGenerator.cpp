#include "TextGenerator.h"

void TextGenerator::Generate(std::string fileName, size_t lineSize, size_t rowNumber)
{
	std::ofstream file(fileName);
	std::string line;
	std::stringstream stream;

	std::random_device dev;
	std::mt19937_64 mt(dev());
	std::uniform_int_distribution<std::mt19937_64::result_type> generator(0, 255);


	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < lineSize; j++)
		{
			char m = generator(dev);
			line.push_back(m);
		}
		file << line << std::endl;
		line.clear();
	}


	file.flush();
	file.close();
		
	//int s = generator(dev);
}