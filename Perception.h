#pragma once

#include <fstream>

using namespace std;

struct CPerception {
	//fstream file;
	FILE* file;
	struct CFile_Header {
		char version[75];
		char byte_order;
		int empty_field;
		unsigned int toc_offset;
		CFile_Header(CPerception* P);
	};
	CPerception();
};