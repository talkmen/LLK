#pragma once
#include "GameLogic.h"
#include "global.h"
#include "Graph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	int getElement(int nRow, int nCol);
	void setFirstVertex(int nRow, int nCol);//设置第一次选中点的坐标
	void setSecVertex(int nRow, int nCol);//设置第二次选中点的坐标
	Vertex getFirstVertex();//获取第一次选中点的坐标
	Vertex getSecVertex();//获取第二次选中点的坐标
	int Link(int nRow, int nCol);//响应用户点击地图中的元素
	LN* getLineOfTwoVex();//返回可达连线
	void ClearLNNode(); //初始化pNode
	void doAfterGameOver(); //清理
	int changeGameStatus();//改变游戏状态
	int getPath(int path[MAXMAPROW * MAXMAPCOL]);//得到消子路径
	void addScore();
	int calScore(int time); //计算分数
	bool saveScore(int nScore, int GameModel); //保存分数
	int getScore(); //得到得分
	virtual Vertex startGame() = 0;//开始游戏 响应开始游戏按钮
	virtual int JudgeWin(int Time);//判断胜负
	virtual int getTips();//提示
	virtual int ResortGame();//重排
	void setMapSize(int row, int col);
	Vertex getMapSize();
protected:
	//控制器必要属性
	CGameLogic m_gameL;//游戏逻辑
	int m_anMap[4][4];//地图矩阵

	CGraph m_graph;
	Vertex m_ptSelFirst;//第一次选择点的坐标
	Vertex m_ptSelSecond;//第二次选择点坐标

	int m_GameStatus;//游戏状态

	LN m_phNode[MAXLNNUM];
	int m_Path[MAXMAPROW * MAXMAPCOL];//路径
	int m_VexNum;
	int m_Score;		//游戏得分
	Vertex m_mapSize;//游戏地图中行列元素个数
	bool m_bFirstSelect;//是否为第一次选中，游戏中辅助判断处理逻辑

};

