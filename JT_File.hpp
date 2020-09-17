#pragma once

#include <fstream>

class JT_File
{
	std::ifstream file;

public:
	void open(std::string filepath)
	{
		file.open(filepath, std::ios::binary);
	}

	template <typename T>
	void read_to(T& object, int offset = NULL)
	{
		if (offset) file.seekg(offset);
		file.read((char*)&object, sizeof(object));
	}

	~JT_File()
	{
		file.close();
	}
};