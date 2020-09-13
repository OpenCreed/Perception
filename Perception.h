#pragma once
#pragma pack(1)

#include <fstream>
#include <stdint.h>
#include <vector>
#include "enum.h"

struct CPerception
{
	struct CFile_Header
	{
		char version[80];
		char byte_order;
		int32_t empty_field;
		int32_t toc_offset;
		char lsg_segment_id[16]; // GUID

		CFile_Header();
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
		std::vector<CTOC_Entry> toc_entry;

		CTOC_Segment();
	};

	struct CData_Segment
	{
		struct CSegment_Header
		{
			char segment_id[16];
			int32_t segment_type;
			int32_t segment_length;
		};

		struct CData
		{
			struct CLogical_Element_Header
			{

			};
			struct CObject_Data
			{

			};

			CData() {};
			CData(Segment_Type);
		};

		CSegment_Header Segment_Header;
		CData Data;

		CData_Segment(CTOC_Segment::CTOC_Entry);
	};

	//static std::ifstream file;
	static CFile_Header File_Header;
	CTOC_Segment TOC_Segment;
	std::vector<CData_Segment> Data_Segment;

	CPerception();
};