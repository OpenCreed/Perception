// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.h"
#include <iostream>
#include <fstream>

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
	file.open("D:/JBC/3D Objects/Radial_Engine.jt", ios::binary);
	File_Header = CFile_Header(this);
	TOC_Segment = CTOC_Segment(this);
	//file.read((char*)&File_Header, sizeof(File_Header));
	//cout << File_Header.version << endl;
	//file.seekg(File_Header.toc_offset);
	//file.read((char*)&TOC_Segment.entry_count, sizeof(TOC_Segment.entry_count));
	//TOC_Segment.toc_entry = (CTOC_Segment::CTOC_Entry*)malloc((int64_t)TOC_Segment.entry_count * sizeof(CTOC_Segment::CTOC_Entry));
	//if (TOC_Segment.toc_entry != nullptr)
	//{
	//	file.read((char*)TOC_Segment.toc_entry, (int64_t)TOC_Segment.entry_count * sizeof(CTOC_Segment::CTOC_Entry));
	//}
	//cout << file.tellg() << endl << endl;
	//for (int i = 0; i < TOC_Segment.entry_count; i++)
	//{
	//	cout << TOC_Segment.toc_entry[i].segment_offset<<endl;
	//}

	//free(TOC_Segment.toc_entry);
	//cout << TOC_Segment.entry_count;
}

CPerception::CFile_Header::CFile_Header(CPerception *P)
{
	P->file.read((char*)this, sizeof(*this));
}

CPerception::CTOC_Segment::CTOC_Segment(CPerception* P)
{
	P->file.seekg(P->File_Header.toc_offset);
	P->file.read((char*)&entry_count, sizeof(entry_count));
}
