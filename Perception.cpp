// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PCH.h"
#include "Perception.h"
#include "FileProcessor.hpp"

std::unique_ptr<FileProcessor> fp;
FileHeader fileHeader;

int main()
{
	fp = std::make_unique<FileProcessor>("C:/Users/JBC/3D Objects/floorjack.jt");
	fp->readTo(fileHeader);
	TOCSegment TOC_Segment = TOCSegment();
	std::vector<DataSegment> Data_Segment;
	for (auto entry = TOC_Segment.tocEntry.cbegin(); entry != TOC_Segment.tocEntry.cend(); entry++)
	{
		Data_Segment.push_back(DataSegment(*entry));
	}
}

TOCSegment::TOCSegment()
{
	fp->readTo(entryCount, fileHeader.tocOffset);

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
	std::vector<Byte>dataBuffer;

	fp->readTo(segmentHeader, E.segmentOffset);
	switch ((SegmentType)segmentHeader.segmentType)
	{
	case SegmentType::Logical_SG:
	case SegmentType::JT_B_Rep:
	case SegmentType::PMI_Data:
	case SegmentType::Meta_Data:
	case SegmentType::XT_B_Rep:
	case SegmentType::Wireframe_Rep:
	case SegmentType::ULP:
	case SegmentType::LWPA:
	{
		int32_t compressionFlag;
		int32_t compressionDataLength;
		uint8_t compressionAlgorithm;
		fp->readTo(compressionFlag);
		fp->readTo(compressionDataLength);
		fp->readTo(compressionAlgorithm);
		dataBuffer.resize(compressionDataLength - 1);
		fp->decompressAndCopyTo(dataBuffer);
		break;
	}
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
	{
		dataBuffer.resize(segmentHeader.segmentLength);
		fp->copyTo(dataBuffer);
		break;
	}
	default:
		std::cout << "Invaild Segment Type" << std::endl;
		break;
	}

	data = *(Data*)dataBuffer.data();
	std::cout << data.logicalElementHeader.elementHeader.objectTypeID << std::endl;
}