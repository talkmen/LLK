#include "stdafx.h"
#include "ScoreLogic.h"
#include "CONSTANT.h"
#include <stdlib.h>

CScoreLogic::CScoreLogic()
{
}

CScoreLogic::~CScoreLogic()
{
}

//������Ϸ���
bool CScoreLogic::SaveScore(SCORE &score)
{
	if (score.nGrade < 500)
		score.nLevel = 1;
	else if ((score.nGrade >= 500) && (score.nGrade < 1000))
		score.nLevel = 2;
	else if (score.nGrade >= 1000)
		score.nLevel = 3;
	score.strName.Format(_T("2018062215540000"));

	return scoreDao.Save(RANKFILEPATH, score);
}

int CScoreLogic::SearchRank(RankArray rankArray[MAXRANKLEVEL], int nModel)
{
	//�����ļ��㴦������ȡ��Ϣ
	CString mesStr[MAXRANKMES];
	//��ȡ�ļ���Ϣ
	int mesNum;
	mesNum = scoreDao.Read(RANKFILEPATH, mesStr);
	//�����ļ���Ϣ
	SCORE score[MAXRANKMES];//��Ϣ�洢
	for (int i = 0; i < mesNum; i++)
		scoreDao.PraseCString(mesStr[i], score[i]);

	RankArray temp[MAXRANKMES];

	int count = 0;
	//��������
	for (int i = 0; i < mesNum - 1; i++)
	{
		if (score[i].nMode == nModel)
		{
			temp[count].playerName.Format(L"%s", score[i].strName);
			temp[count++].nGrade = score[i].nGrade;
		}
	}
	int modelMesNum = 0;
	//�������Ľ��������RankArray������
	for (int i = 0; (i < count) && (modelMesNum < MAXRANKLEVEL); i++)
	{
		int flag = i;
		for (int m = i + 1; m < count; m++)
		{
			if (temp[flag].nGrade < temp[m].nGrade)
				flag = m;
		}
		if (flag != i)
			swapRankArray(temp[i], temp[flag]);
		rankArray[modelMesNum].playerName.Format(L"%s", temp[i].playerName);
		rankArray[modelMesNum++].nGrade = temp[i].nGrade;
	}
	//���ػ�������
	return modelMesNum;
}

void CScoreLogic::swapRankArray(RankArray &rankArray1, RankArray &rankArray2)
{
	int tempGrade;
	CString tempName;

	tempGrade = rankArray1.nGrade;
	tempName.Format(L"%s", rankArray1.playerName);

	rankArray1.nGrade = rankArray2.nGrade;
	rankArray1.playerName.Format(L"%s", rankArray2.playerName);

	rankArray2.nGrade = tempGrade;
	rankArray2.playerName.Format(L"%s", tempName);
}