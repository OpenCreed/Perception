#pragma once

#include <fstream>
#include <assert.h>
#include "zlib.h"
#include <vector>

constexpr int CHUNK = 131072;

class Z_Lib
{
    z_stream strm;
    int have, ret;

public:
    int inf(std::ifstream &file, int inp_bytes)
    {
        Bytef* in = new Bytef[inp_bytes];
        unsigned char out[CHUNK];
        std::vector<unsigned char> sink;

        file.read((char*)in, inp_bytes);

        /* allocate inflate state */
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        strm.data_type = Z_BINARY;
        ret = inflateInit(&strm);
       
        strm.avail_in = inp_bytes;
        strm.next_in = in;
       
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;

            /*if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }*/
            for (int i = 0; i < have; i++)
            {
                sink.push_back(out[i]);
            }
            
        } while (strm.avail_out == 0);
        delete[] in;

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