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
	bool SaveScore(SCORE& score);//储存分数信息
	int SearchRank(RankArray rankArray[MAXRANKLEVEL], int nModel);//获取排行榜分数信息
private:
	void swapRankArray(RankArray &rankArray1, RankArray &rankArray2);//交换SCORE信息
};

