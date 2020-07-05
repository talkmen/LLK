#pragma once
#include "global.h"
#include "CONSTANT.h"
#include<fstream>

class CScoreDao
{
public:
	CScoreDao();
	~CScoreDao();
	bool Save(const CString & filePath, SCORE &score);
	int Read(const CString &filePath, CString mesStr[MAXRANKMES]);
	void PraseCString(CString cstr, SCORE &score);
};

