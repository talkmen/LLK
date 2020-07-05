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
	int JudgeWin();//�ж�ʤ��
	int getTips();//��ʾ
	int ResortGame(bool tips = false);//����
	void addScore();
	void updateTool(bool use);
	int Link(int row, int col);
	int getTool();
	bool setUse();
	int calScore();
	void doAfterGameOver(); //����
private:
	int m_Tool;
	bool m_use;
	int m_count;
};

