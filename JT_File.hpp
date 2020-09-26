#pragma once

#include <iostream>
#include <fstream>

struct JT_File
{
	std::ifstream file;

	JT_File(std::string filepath)
	{
		file.open(filepath, std::ios::binary);
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
	}

	template <typename T>
	void read_to(T& object, int offset = NULL)
	{
		try
		{
			if (offset) file.seekg(offset);
			file.read((char*)&object, sizeof(object));
		}
		catch (std::ifstream::failure e)
		{
			std::cerr << e.code().message()<< std::endl;
		}
	}

	~JT_File()
	{
		file.close();
	}
};