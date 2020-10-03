#pragma once
#pragma pack(push, 1)

#include "PCH.h"
#include "enum.hpp"

struct GUID
{
	uint32_t d1;
	uint16_t d2[2];
	uint8_t d3[8];

	friend std::ostream& operator<<(std::ostream& output, const GUID& id) {
		output << std::hex << id.d1;
		for (size_t i = 0; i < 2; i++)
		{
			output << '-' << id.d2[i];
		}
		for (size_t i = 0; i < 8; i++)
		{
			output << '-' << static_cast<uint16_t>(id.d3[i]);
		}
		return output;
	}
};

struct FileHeader
{
	char version[80];
	char byteOrder;
	int32_t emptyField;
	int32_t tocOffset;
	GUID lsgSegmentID;
};

struct TOCSegment
{
	struct TOCEntry
	{
		GUID segmentID;
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
		GUID segmentID;
		int32_t segmentType;
		int32_t segmentLength;
	};

	struct Data
	{
		struct LogicalElementHeader
		{
			struct ElementHeader
			{
				GUID objectTypeID;
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
	};

	SegmentHeader segmentHeader;
	Data data;

	DataSegment(TOCSegment::TOCEntry);
};

#pragma pack(pop)