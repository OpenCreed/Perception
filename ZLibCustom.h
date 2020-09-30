#pragma once

#include "PCH.h"

constexpr int CHUNK = 131072;

class ZLibCustom
{
	z_stream strm;
	std::vector<Bytef> in;
	std::vector<Bytef> out;

	int initForInflate()
	{
		/* allocate inflate state */
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		strm.avail_out = 0;
		strm.next_out = Z_NULL;
		strm.data_type = Z_BINARY;
		return inflateInit(&strm);
	}

	void clearVectorStreams()
	{
		in.clear();
		out.clear();
	}

public:
	void inf(std::ifstream& file, int inp_bytes)
	{
		int ret;
		clearVectorStreams();
		try
		{
			ret = initForInflate();
			if (ret != Z_OK)	throw ret;
			in.resize(inp_bytes);
			file.read((char*)in.data(), inp_bytes);
			strm.avail_in = inp_bytes;
			strm.next_in = in.data();
			while (strm.avail_out == 0)
			{
				out.resize(out.size() + CHUNK);
				strm.avail_out = CHUNK;
				strm.next_out = out.data() + out.size() - CHUNK;
				ret = inflate(&strm, Z_NO_FLUSH);
				if (ret != Z_OK && ret != Z_STREAM_END) break;
			}
			out.resize(strm.total_out);
			(void)inflateEnd(&strm);
			std::cout << ret << std::endl;
			if (ret != Z_STREAM_END)	throw ret == Z_OK ? Z_DATA_ERROR : ret;
		}
		catch (int ret)
		{
			zLibCustomErr(ret);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}
	}

	void zLibCustomErr(int ret)
	{
		std::cerr << "ZLibCustom : ";
		switch (ret) {
		case Z_ERRNO:
			std::cerr << "IO Error\n";
			break;
		case Z_STREAM_ERROR:
			std::cerr << "invalid compression level\n";
			break;
		case Z_DATA_ERROR:
			std::cerr << "invalid or incomplete deflate data\n";
			break;
		case Z_MEM_ERROR:
			std::cerr << "out of memory\n";
			break;
		case Z_VERSION_ERROR:
			std::cerr << "zlib version mismatch!\n";
		}
	}
};