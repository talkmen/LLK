#include "stdafx.h"
#include "ScoreDao.h"
#include<stdlib.h>
#include<string>
#include<fstream>

using namespace std;

CScoreDao::CScoreDao()
{
}

CScoreDao::~CScoreDao()
{
}

//bool CScoreDao::Save(const CString & filePath, SCORE &score)
//{
//	ofstream file(filePath, ios::app);
//
//	if (file.is_open())
//	{
//		CString cstr;
//		file << endl;
//		cstr.Format(_T("%02d%s%05d%d\n"), score.nMode, score.strName, score.nGrade, score.nLevel);
//		file << cstr;
//		file.close();
//		return true;
//	}
//	return false;
//}
//
//int CScoreDao::Read(const CString &filePath, CString mesStr[MAXRANKMES])
//{
//	ifstream file(filePath, ios::in);
//	int mesNum = 0;
//	string str;
//	if (file.is_open())
//	{
//		while (getline(file, str))
//			mesStr[mesNum++].Format(_T("%s"), str);
//		file.close();
//	}
//	return mesNum;
//}

void CScoreDao::PraseCString(CString cstr, SCORE &score)
{
	CString model = cstr.Left(2);
	CString name = cstr.Mid(2, 16);
	CString grade = cstr.Mid(18, 5);
	CString level = cstr.Mid(23, 1);

	score.nMode = _ttoi(model);
	score.strName.Format(L"%s", name);
	score.nGrade = _ttoi(grade);
	score.nLevel = _ttoi(level);
}

bool CScoreDao::Save(const CString & filePath, SCORE &score)
{
	CStdioFile file;

	file.Open(filePath, CFile::modeWrite, NULL);
	
	CString cstr;
	cstr.Format(_T("%02d%s%05d%d\n"), score.nMode, score.strName, score.nGrade, score.nLevel);
	file.SeekToEnd();
	file.WriteString(cstr);
	file.Flush();
	
	file.Close();
	return true;
}

int CScoreDao::Read(const CString &filePath, CString mesStr[MAXRANKMES])
{
	CStdioFile file;
	int mesNum = 0;
	file.Open(filePath, CFile::modeRead, NULL);
	
	while (file.ReadString(mesStr[mesNum++]));
	
	file.Close();
	return mesNum;
}
