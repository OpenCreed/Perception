#pragma once

#include "PCH.h"
#include "ZLibCustom.h"

class FileProcessor
{
	std::ifstream file;
	ZLibCustom zlb = ZLibCustom();

public:
	FileProcessor(std::string filepath)
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
	void readTo(T& object, int offset = NULL)
	{
		try
		{
			if (offset) file.seekg(offset);
			file.read((char*)&object, sizeof(object));
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void decompressData(int sze)
	{
		zlb.inf(file, sze);
	}

	~FileProcessor()
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