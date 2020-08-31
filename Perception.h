#pragma once

#include <fstream>

using namespace std;

struct CPerception {
	ifstream file;
	struct CFile_Header {
		char version[80];
		char byte_order;
		int empty_field;
		unsigned long long toc_offset;
		CFile_Header(CPerception* P);
	};
	CPerception();
};