#pragma once
#include "GameControl.h"

class CEasyGame :
	public CGameControl
{
public:
	CEasyGame();
	~CEasyGame();
	void setUseTool();

	Vertex startGame();
	int JudgeWin();//判断胜负
	int getTips();//提示
	int ResortGame(bool tips = false);//重排
	void addScore();
	void updateTool(bool use);
	int Link(int row, int col);
	int getTool();
	bool setUse();
	int calScore();
	void doAfterGameOver(); //清理
private:
	int m_Tool;
	bool m_use;
	int m_count;
};

