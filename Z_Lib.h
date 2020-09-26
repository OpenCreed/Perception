#pragma once

#include <fstream>
#include <assert.h>
#include "zlib.h"
#include <vector>

constexpr int CHUNK = 262144;

class Z_Lib
{
	z_stream strm;
	int have, ret;

	int initForInflate()
	{
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

public:
	int inf(std::ifstream& file, int inp_bytes)
	{
		/* allocate inflate state */
		ret = initForInflate();
		if (ret != Z_OK)
			return ret;

		std::vector<Bytef> in;
		std::vector<Bytef> out;

		in.reserve(inp_bytes);
		out.reserve(CHUNK);

		file.read((char*)in.data(), inp_bytes);

		strm.avail_in = inp_bytes;
		strm.next_in = in.data();

		int out_size = 0;
		int test = 0;

		while (strm.avail_out == 0)
		{
			test++;
			Bytef* chunk_out = out.data();
			out_size += CHUNK;
			out.reserve(out_size);
			strm.avail_out = CHUNK;
			strm.next_out = &chunk_out[out_size - CHUNK];
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