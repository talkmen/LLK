#pragma once
typedef struct tagVertex
{
	int row;//行号
	int col;//列号
	int info;
}Vertex, LN; //图中行列信息

typedef struct tagScore
{
	int nMode;//游戏模式
	int nGrade;//积分分数
	int nLevel;//积分等级
	CString strName;//玩家姓名
}SCORE;
typedef struct tagRankArray
{
	CString playerName;//姓名
	int nGrade;//得分
}RankArray;
typedef struct tagCString
{
	CString CStr;
	struct tagCString* next;
}CStr, *pCStr;

