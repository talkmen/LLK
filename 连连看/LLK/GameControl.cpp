#include "stdafx.h"
#include "GameControl.h"
#include "CONSTANT.h"
#include "ScoreLogic.h"

CGameControl::CGameControl()
{
}

CGameControl::~CGameControl()
{
}

//���õ�һ��ѡ�е������
void CGameControl::setFirstVertex(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

//���õڶ���ѡ�е������
void CGameControl::setSecVertex(int nRow, int nCol)
{
	m_ptSelSecond.row = nRow;
	m_ptSelSecond.col = nCol;
}

//��ȡ��һ��ѡ�е������
Vertex CGameControl::getFirstVertex()
{
	return m_ptSelFirst;
}

//��ȡ�ڶ���ѡ�е������
Vertex CGameControl::getSecVertex()
{
	return m_ptSelSecond;
}

//��ȡ���λ��Ԫ��
int CGameControl::getElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * m_mapSize.col + nCol);
}

LN* CGameControl::getLineOfTwoVex()
{
	return m_phNode;
}

//��յ㼯
void CGameControl::ClearLNNode()
{
	for (int i = 0; i < MAXLNNUM; i++)
	{
		m_phNode[i].row = -1;
		m_phNode[i].col = -1;
		m_phNode[i].info = false;
	}
}

int CGameControl::Link(int nRow, int nCol)
{
	m_VexNum = 0;
	if (m_graph.GetVertex(nRow * m_mapSize.col + nCol) == BLANK)//ѡ�пհ�
	{
		return SELECTBLANK;
	}
	else if (m_bFirstSelect)
	{
		//��һ��ѡ��Ԫ�� ��¼
		m_ptSelFirst.row = nRow;
		m_ptSelFirst.col = nCol;
		m_bFirstSelect = !m_bFirstSelect;

		return FIRSTSELECT;
	}
	else
	{
		//�ڶ���ѡ��Ԫ��
		m_ptSelSecond.row = nRow;
		m_ptSelSecond.col = nCol;
		m_bFirstSelect = !m_bFirstSelect;
		if (m_gameL.IsLink(m_graph, m_ptSelFirst, m_ptSelSecond, m_Path, m_VexNum, m_mapSize))
		{
			m_gameL.Clear(m_graph, m_ptSelFirst, m_ptSelSecond, m_mapSize);
			return CLEARSELECT;
		}
		return RESELECT;
	}
}

int CGameControl::getPath(int path[MAXMAPROW * MAXMAPCOL])
{
	for (int i = 0; i < m_VexNum; i++)
		path[i] = m_Path[i];
	return m_VexNum;
}

//�ж�ʤ��
int CGameControl::JudgeWin(int Time)
{
	if (Time <= 0)
		return GAME_LOSER;
	else if (m_gameL.IsBlank(m_graph, m_mapSize))
		return GAME_SUCCESS;
	else
		return GAME_PLAY;
}

//�޸���Ϸ״̬
int CGameControl::changeGameStatus()
{
	if (m_GameStatus == GAME_PLAY)
	{
		m_GameStatus = GAME_PAUSE;
		return GAME_PAUSE;
	}
	else
	{
		m_GameStatus = GAME_PLAY;
		return GAME_PLAY;
	}
}

//�õ���ʾ
int CGameControl::getTips()
{
	m_VexNum = 0;
	return m_gameL.SearchValidPath(m_graph, m_Path, m_VexNum, m_mapSize);
}

//����
int CGameControl::ResortGame()
{
	m_gameL.Resort(m_graph, m_mapSize);
	return SUCCESS;
}

//��������
void CGameControl::doAfterGameOver()
{
	m_graph.ClearGraph();
	m_Score = 0;
	m_bFirstSelect = true;
}

bool CGameControl::saveScore(int nScore, int GameModel)
{
	SCORE score;
	score.nGrade = nScore;
	score.nMode = GameModel;

	CScoreLogic scoreL;

	return scoreL.SaveScore(score);
}

int CGameControl::getScore()
{
	return m_Score;
}

int CGameControl::calScore(int time)
{
	int timeScore = time*((int)sqrt((double) (m_mapSize.col - 2)));
	return timeScore + m_Score;
}

void CGameControl::addScore()
{
	m_Score += 10;
}

void CGameControl::setMapSize(int row, int col)
{
	m_mapSize.row = row;
	m_mapSize.col = col;
}

Vertex CGameControl::getMapSize()
{
	return m_mapSize;
}