#pragma once
#include "global.h"
#include "CONSTANT.h"
#include "ScoreDao.h"
class CScoreLogic
{
protected:
	CScoreDao scoreDao;
public:
	CScoreLogic();
	~CScoreLogic();
	bool SaveScore(SCORE& score);//���������Ϣ
	int SearchRank(RankArray rankArray[MAXRANKLEVEL], int nModel);//��ȡ���а������Ϣ
private:
	void swapRankArray(RankArray &rankArray1, RankArray &rankArray2);//����SCORE��Ϣ
};

