#pragma once

#include <iostream>
#include <fstream>

struct JT_File
{
	std::ifstream file;

	JT_File(std::string filepath)
	{
		try
		{
			file.open(filepath, std::ios::binary);
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	template <typename T>
	void read_to(T& object, int offset = NULL)
	{
		try
		{
			if (offset) file.seekg(offset);
			file.read((char*)&object, sizeof(object));
		}
		catch (std::exception& e)
		{
			std::cerr << e.what()<< std::endl;
		}
	}

	~JT_File()
	{
		try
		{
			file.close();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
};