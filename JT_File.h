#pragma once

#include <fstream>

class JT_File
{
	std::ifstream file;

public:

	inline void open(std::string filepath)
	{
		file.open(filepath, std::ios::binary);
	}

	template <typename T>
	inline void read(T& object, int offset = NULL)
	{
		if (offset == NULL)
		{
			file.read((char*)&object, sizeof(object));
		}
		else
		{
			file.seekg(offset);
			file.read((char*)&object, sizeof(object));
		}
	}

	inline ~JT_File()
	{
		file.close();
	}
};