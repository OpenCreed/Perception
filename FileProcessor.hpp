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

	void copyTo(std::vector<Byte> &dataBuffer)
	{
		file.read((char*)dataBuffer.data(), dataBuffer.size());
	}

	void decompressAndCopyTo(std::vector<Byte> &dataBuffer)
	{
		file.read((char*)dataBuffer.data(), dataBuffer.size());
		zlb.inf(dataBuffer);
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