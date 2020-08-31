// Perception.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Perception.h"
#include <iostream>
#include <fstream>
#include <ctype.h>

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
	CFile_Header File_Header = CFile_Header(this);
}

CPerception::CFile_Header::CFile_Header(CPerception* P)
{
	P->file.read(version, sizeof(version));
	P->file.read((char*)&byte_order, sizeof(byte_order));
	P->file.read((char*)&empty_field, sizeof(empty_field));
	P->file.read((char*)&toc_offset, sizeof(toc_offset));
	cout << toc_offset;
}