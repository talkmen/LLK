#include "stdafx.h"
#include "EasyGame.h"

CEasyGame::CEasyGame()
{
	m_mapSize.row = MEDIUMMAPROW;
	m_mapSize.col = MEDIUMMAPCOL;
	m_Score = 0;
	m_Tool = 0;
	m_use = false;
	m_count = 0;
}

CEasyGame::~CEasyGame()
{
}

Vertex CEasyGame::startGame()
{
	m_gameL.InitMap(m_graph, m_mapSize);
	//辅助逻辑判断设置为下次选择为第一次选中元素
	m_bFirstSelect = true;

	return m_mapSize;
}

//判断胜负
int CEasyGame::JudgeWin()
{
	if (m_gameL.IsBlank(m_graph, m_mapSize))
		return GAME_SUCCESS;
	else
		return GAME_PLAY;
}

//提示
int CEasyGame::getTips()
{
	m_VexNum = 0;
	if (m_Score < 20)
		return SCORENOTENOUGH;
	else
	{
		m_Score -= 20;
		return m_gameL.SearchValidPath(m_graph, m_Path, m_VexNum, m_mapSize);
	}
}

//重排
int CEasyGame::ResortGame(bool tips)
{
	if (tips)
		m_gameL.Resort(m_graph, m_mapSize);
	if (m_Score < 50)
		return SCORENOTENOUGH;
	else
	{
		m_Score -= 50;
		m_gameL.Resort(m_graph, m_mapSize);
		return SUCCESS;
	}
}

void CEasyGame::addScore()
{
	m_Score += 10;
	m_count += 10;
}

void CEasyGame::updateTool(bool use)
{
	if (use && m_count % 100 == 0)
	{
		m_Tool += 1;
		m_count = 0;

	}
	else if (!use)
		m_Tool -= 1;
}

int CEasyGame::getTool()
{
	return m_Tool;
}

int CEasyGame::Link(int row, int col)
{
	m_VexNum = 0;
	if (m_use && !m_bFirstSelect)
	{
		m_ptSelSecond.row = row;
		m_ptSelSecond.col = col;
		m_bFirstSelect = !m_bFirstSelect;
		int index1 = m_ptSelFirst.row * m_mapSize.col + m_ptSelFirst.col;
		int index2 = m_ptSelSecond.row * m_mapSize.col + m_ptSelSecond.col;
		int vex1 = m_graph.GetVertex(index1);
		int vex2 = m_graph.GetVertex(index2);
		if (vex1 == vex2)
		{
			m_use = !m_use;
			m_gameL.Clear(m_graph, m_ptSelFirst, m_ptSelSecond, m_mapSize);
			return CLEARSELECT;
		}
		return RESELECT;
	}
	else
		return CGameControl::Link(row, col);
}

bool CEasyGame::setUse()
{
	if (m_use)
		return true;
	else if (m_Tool >= 1)
	{
		m_Tool -= 1;
		m_use = true;
		return true;
	}
	else
		return false;
}

int CEasyGame::calScore()
{
	return getScore();
}

void CEasyGame::doAfterGameOver()
{
	m_graph.ClearGraph();
	m_Score = 0;
	m_Tool = 0;
	m_use = 0;
	m_count = 0;
	m_bFirstSelect = true;
}
