#pragma once
#pragma pack(1)

#include <string>
#include <fstream>
#include <stdint.h>
#include <vector> 
#include <iostream>
#include <zlib.h>

using namespace std;

struct CPerception
{
	struct CFile_Header
	{
		char version[80];
		char byte_order;
		int32_t empty_field;
		int32_t toc_offset;
		char lsg_segment_id[16]; // GUID

		CFile_Header() {};
		CFile_Header(CPerception*);
	};

	struct CTOC_Segment
	{
		struct CTOC_Entry
		{
			char segment_id[16];
			int32_t segment_offset;
			int32_t segment_length;
			uint32_t segment_attribute;
		};

		int32_t entry_count;
		vector<CTOC_Entry> toc_entry;

		CTOC_Segment() {};
		CTOC_Segment(CPerception*);
	};

	struct CData_Segment
	{
		struct CSegment_Header
		{
			char segment_id[16];
			int32_t segment_type;
			int32_t segment_length;
		};

		CSegment_Header Segment_Header;

		CData_Segment(CPerception*, CTOC_Segment::CTOC_Entry);
	};

	ifstream file;
	CFile_Header File_Header;
	CTOC_Segment TOC_Segment;
	vector<CData_Segment> Data_Segment;

	CPerception();
};