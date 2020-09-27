// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PCH.h"
#include "Perception.h"
#include "FileProcessor.hpp"

std::unique_ptr<FileProcessor> fp;
std::unique_ptr<FileHeader> fileHeader;

int main()
{
	fp = std::make_unique<FileProcessor>("C:/Users/JBC/3D Objects/floorjack.jt");
	fileHeader = std::make_unique<FileHeader>();
	TOCSegment TOC_Segment = TOCSegment();
	std::vector<DataSegment> Data_Segment;
	for (auto entry = TOC_Segment.tocEntry.cbegin(); entry != TOC_Segment.tocEntry.cend(); entry++)
	{
		Data_Segment.push_back(DataSegment(*entry));
	}
}

FileHeader::FileHeader()
{
	fp->readTo(*this);
}

TOCSegment::TOCSegment()
{
	fp->readTo(entryCount, fileHeader->tocOffset);

	for (int i = 0; i < entryCount; i++)
	{
		TOCEntry entry;
		fp->readTo(entry);
		entry.segmentAttribute >>= 24;
		tocEntry.push_back(entry);
	}
}

DataSegment::DataSegment(TOCSegment::TOCEntry E)
{
	fp->readTo(segmentHeader, E.segmentOffset);
	data = Data((SegmentType)segmentHeader.segmentType);
}

DataSegment::Data::Data(SegmentType type)
{
	switch (type)
	{
	case SegmentType::Logical_SG:
	case SegmentType::JT_B_Rep:
	case SegmentType::PMI_Data:
	case SegmentType::Meta_Data:
	case SegmentType::XT_B_Rep:
	case SegmentType::Wireframe_Rep:
	case SegmentType::ULP:
	case SegmentType::LWPA:
		int32_t compression_flag;
		int32_t compression_data_length;
		uint8_t compression_algorithm;
		fp->readTo(compression_flag);
		fp->readTo(compression_data_length);
		fp->readTo(compression_algorithm);
		fp->decompressData(compression_data_length - 1);
		break;
	case SegmentType::Shape:
	case SegmentType::Shape_LOD0:
	case SegmentType::Shape_LOD1:
	case SegmentType::Shape_LOD2:
	case SegmentType::Shape_LOD3:
	case SegmentType::Shape_LOD4:
	case SegmentType::Shape_LOD5:
	case SegmentType::Shape_LOD6:
	case SegmentType::Shape_LOD7:
	case SegmentType::Shape_LOD8:
	case SegmentType::Shape_LOD9:
		fp->readTo(logicalElementHeader);
		std::cout << +logicalElementHeader.elementHeader.objectBaseType << std::endl;
		break;
	default:
		std::cout << "Invaild Segment Type" << std::endl;
		break;
	}
}