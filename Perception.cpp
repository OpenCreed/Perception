// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.h"

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
	file.open("D:/JBC/3D Objects/floorjack.jt", ios::binary);
	File_Header = CFile_Header(this);
	TOC_Segment = CTOC_Segment(this);
	for (auto entry = TOC_Segment.toc_entry.cbegin(); entry != TOC_Segment.toc_entry.cend(); entry++)
	{
		Data_Segment.push_back(CData_Segment(this, *entry));
	}
}

CPerception::CFile_Header::CFile_Header(CPerception* P)
{
	P->file.read((char*)this, sizeof(*this));
}

CPerception::CTOC_Segment::CTOC_Segment(CPerception* P)
{
	P->file.seekg(P->File_Header.toc_offset);
	P->file.read((char*)&entry_count, sizeof(entry_count));

	for (int i = 0; i < entry_count; i++)
	{
		CTOC_Entry entry;
		P->file.read((char*)&entry, sizeof(entry));
		entry.segment_attribute >>= 24;
		toc_entry.push_back(entry);
	}
}

CPerception::CData_Segment::CData_Segment(CPerception* P, CTOC_Segment::CTOC_Entry E)
{
	P->file.seekg(E.segment_offset);
	P->file.read((char*)&Segment_Header, sizeof(Segment_Header));
}
