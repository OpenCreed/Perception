#pragma once
#pragma pack(1)

#include <fstream>
#include <stdint.h>

using namespace std;

struct CPerception 
{
	struct CFile_Header 
	{
		char version[80];
		char byte_order;
		int32_t empty_field;
		uint32_t toc_offset;
		char lsg_segment_id[16]; // GUID

		CFile_Header() {};
		CFile_Header(CPerception*);
	};

	struct CTOC_Segment 
	{
		struct CTOC_Entry
		{
			char segment_id[16];
			uint32_t segment_offset;
			uint32_t segment_length;
			uint32_t segment_attribute;
		};

		int32_t entry_count;
		CTOC_Entry* toc_entry;

		CTOC_Segment() {};
		CTOC_Segment(CPerception*);
	};

	ifstream file;
	CFile_Header File_Header;
	CTOC_Segment TOC_Segment;

	CPerception();
};