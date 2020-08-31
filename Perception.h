#pragma once
#pragma pack(1)

#include <fstream>
#include <stdint.h>

using namespace std;

struct CPerception {
	struct CFile_Header {
		char version[80];
		char byte_order;
		int32_t empty_field;
		uint64_t toc_offset;
	};

	struct CTOC_Segment {
		int32_t entry_count;
	};

	ifstream file;
	CFile_Header File_Header;
	CTOC_Segment TOC_Segment;

	CPerception();
};