// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.hpp"
#include "JT_File.hpp"
#include <iostream>
#include "Z_Lib.h"

std::unique_ptr<JT_File> jtfile;
std::unique_ptr<CFile_Header> File_Header;
Z_Lib zlb = Z_Lib();

void main()
{
	//jtfile.open("C:/Users/JBC/3D Objects/floorjack.jt");
	jtfile = std::make_unique<JT_File>("C:/Users/JBC/3D Objects/floorjack.jt");
	File_Header = std::make_unique<CFile_Header>();
	CTOC_Segment TOC_Segment = CTOC_Segment();
	std::vector<CData_Segment> Data_Segment;
	for (auto entry = TOC_Segment.toc_entry.cbegin(); entry != TOC_Segment.toc_entry.cend(); entry++)
	{
		Data_Segment.push_back(CData_Segment(*entry));
	}
}

CFile_Header::CFile_Header()
{
	jtfile->read_to(*this);
}

CTOC_Segment::CTOC_Segment()
{
	jtfile->read_to(entry_count, File_Header->toc_offset);

	for (int i = 0; i < entry_count; i++)
	{
		CTOC_Entry entry;
		jtfile->read_to(entry);
		entry.segment_attribute >>= 24;
		toc_entry.push_back(entry);
	}
}

CData_Segment::CData_Segment(CTOC_Segment::CTOC_Entry E)
{
	jtfile->read_to(Segment_Header, E.segment_offset);
	Data = CData((Segment_Type)Segment_Header.segment_type);
}

CData_Segment::CData::CData(Segment_Type type)
{
	int ret;
	switch (type)
	{
	case Segment_Type::Logical_SG:
	case Segment_Type::JT_B_Rep:
	case Segment_Type::PMI_Data:
	case Segment_Type::Meta_Data:
	case Segment_Type::XT_B_Rep:
	case Segment_Type::Wireframe_Rep:
	case Segment_Type::ULP:
	case Segment_Type::LWPA:
		int32_t compression_flag;
		int32_t compression_data_length;
		uint8_t compression_algorithm;
		jtfile->read_to(compression_flag);
		jtfile->read_to(compression_data_length);
		jtfile->read_to(compression_algorithm);
		ret = zlb.inf(jtfile->file, compression_data_length-1);
		std::cout << compression_data_length << " " << ret << std::endl;
		break;
	case Segment_Type::Shape:
	case Segment_Type::Shape_LOD0:
	case Segment_Type::Shape_LOD1:
	case Segment_Type::Shape_LOD2:
	case Segment_Type::Shape_LOD3:
	case Segment_Type::Shape_LOD4:
	case Segment_Type::Shape_LOD5:
	case Segment_Type::Shape_LOD6:
	case Segment_Type::Shape_LOD7:
	case Segment_Type::Shape_LOD8:
	case Segment_Type::Shape_LOD9:
		jtfile->read_to(Logical_Element_Header);
		break;
	default:
		std::cout << "Invaild Segment Type" << std::endl;
		break;
	}
}
