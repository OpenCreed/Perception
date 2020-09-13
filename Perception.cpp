// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.h"
#include <iostream>

std::ifstream CPerception::file;
CPerception::CFile_Header CPerception::File_Header;

int main()
{
	CPerception P = CPerception();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

CPerception::CPerception()
{
	file.open("D:/JBC/3D Objects/floorjack.jt", std::ios::binary);
	File_Header = CFile_Header();
	TOC_Segment = CTOC_Segment();
	for (auto entry = TOC_Segment.toc_entry.cbegin(); entry != TOC_Segment.toc_entry.cend(); entry++)
	{
		Data_Segment.push_back(CData_Segment(*entry));
	}
}

CPerception::CFile_Header::CFile_Header()
{
	file.read((char*)this, sizeof(*this));
}

CPerception::CTOC_Segment::CTOC_Segment()
{
	file.seekg(File_Header.toc_offset);
	file.read((char*)&entry_count, sizeof(entry_count));

	for (int i = 0; i < entry_count; i++)
	{
		CTOC_Entry entry;
		file.read((char*)&entry, sizeof(entry));
		entry.segment_attribute >>= 24;
		toc_entry.push_back(entry);
	}
}

CPerception::CData_Segment::CData_Segment(CTOC_Segment::CTOC_Entry E)
{
	file.seekg(E.segment_offset);
	file.read((char*)&Segment_Header, sizeof(Segment_Header));
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
		std::cout << "Compressed" << std::endl;
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
		std::cout << "Not Compressed" << std::endl;
		break;
	default:
		std::cout << "Invaild Segment Type" << std::endl;
		break;
	}
}
