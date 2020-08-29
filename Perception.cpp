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
    fopen_s(&file, "D:/JBC/3D Objects/Radial_Engine.jt", "r");
    CFile_Header File_Header = CFile_Header(this);
}

CPerception::CFile_Header::CFile_Header(CPerception* P)
{
    fscanf_s(P->file, "%75c", version, sizeof(version));
    fseek(P->file, 80, 0);
    fscanf_s(P->file, "%c", &byte_order);
    fscanf_s(P->file, "%i", &empty_field);
    fscanf_s(P->file, "%li", &toc_offset);
    cout << version;
}