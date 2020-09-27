#pragma once
#pragma pack(push, 1)

#include "PCH.h"
#include "enum.hpp"

struct FileHeader
{
	char version[80];
	char byteOrder;
	int32_t emptyField;
	int32_t tocOffset;
	char lsgSegmentID[16]; // GUID

	FileHeader();
};

struct TOCSegment
{
	struct TOCEntry
	{
		char segmentID[16];
		int32_t segmentOffset;
		int32_t segmentLength;
		uint32_t segmentAttribute;
	};

	int32_t entryCount;
	std::vector<TOCEntry> tocEntry;

	TOCSegment();
};

struct DataSegment
{
	struct SegmentHeader
	{
		char segmentID[16];
		int32_t segmentType;
		int32_t segmentLength;
	};

	struct Data
	{
		struct LogicalElementHeader
		{
			struct ElementHeader
			{
				char objectTypeID[16];
				uint8_t objectBaseType;
				int32_t objectID;
			};

			int32_t elementLength;
			ElementHeader elementHeader;
		};
		struct CObject_Data
		{

		};

		LogicalElementHeader logicalElementHeader;

		Data() {};
		Data(SegmentType);
	};

	SegmentHeader segmentHeader;
	Data data;

	DataSegment(TOCSegment::TOCEntry);
};

#pragma pack(pop)