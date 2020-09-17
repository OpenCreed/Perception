// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.hpp"
#include "JT_File.hpp"
#include <iostream>

static JT_File jtfile;
CPerception::CFile_Header CPerception::File_Header;

int main()
{
	CPerception Perception = CPerception();
}

CPerception::CPerception()
{
	jtfile.open("D:/JBC/3D Objects/floorjack.jt");
	File_Header = CFile_Header();
	TOC_Segment = CTOC_Segment();
	for (auto entry = TOC_Segment.toc_entry.cbegin(); entry != TOC_Segment.toc_entry.cend(); entry++)
	{
		Data_Segment.push_back(CData_Segment(*entry));
	}
}

CPerception::CFile_Header::CFile_Header()
{
	jtfile.read_to(*this);
}

CPerception::CTOC_Segment::CTOC_Segment()
{
	jtfile.read_to(entry_count, File_Header.toc_offset);

	for (int i = 0; i < entry_count; i++)
	{
		CTOC_Entry entry;
		jtfile.read_to(entry);
		entry.segment_attribute >>= 24;
		toc_entry.push_back(entry);
	}
}

CPerception::CData_Segment::CData_Segment(CTOC_Segment::CTOC_Entry E)
{
	jtfile.read_to(Segment_Header, E.segment_offset);
	Data = CData((Segment_Type)Segment_Header.segment_type);
}

CPerception::CData_Segment::CData::CData(Segment_Type type)
{
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
		jtfile.read_to(compression_flag);
		jtfile.read_to(compression_data_length);
		jtfile.read_to(compression_algorithm);
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
		jtfile.read_to(Logical_Element_Header);
		break;
	default:
		std::cout << "Invaild Segment Type" << std::endl;
		break;
	}
}
