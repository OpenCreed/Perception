#pragma once

#include <fstream>
#include <assert.h>
#include "zlib.h"
#include <vector>

constexpr int CHUNK = 131072;

class Z_Lib
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
	int inf(std::ifstream& file, int inp_bytes)
	{
		int ret;

		clearVectorStreams();
		ret = initForInflate();
		if (ret != Z_OK)
			return ret;

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
			assert(ret != Z_STREAM_ERROR);
			switch (ret)
			{
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return ret;
			}
		}

		out.resize(strm.total_out);
		std::cout << strm.total_out << " " << out.size()<<" ";
		(void)inflateEnd(&strm);
		return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
	}

	void zerr(int ret)
	{
		fputs("zpipe: ", stderr);
		switch (ret) {
		case Z_ERRNO:
			if (ferror(stdin))
				fputs("error reading stdin\n", stderr);
			if (ferror(stdout))
				fputs("error writing stdout\n", stderr);
			break;
		case Z_STREAM_ERROR:
			fputs("invalid compression level\n", stderr);
			break;
		case Z_DATA_ERROR:
			fputs("invalid or incomplete deflate data\n", stderr);
			break;
		case Z_MEM_ERROR:
			fputs("out of memory\n", stderr);
			break;
		case Z_VERSION_ERROR:
			fputs("zlib version mismatch!\n", stderr);
		}
	}
};