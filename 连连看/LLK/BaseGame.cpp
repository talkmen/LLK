#include "stdafx.h"
#include "BaseGame.h"

CBaseGame::CBaseGame()
{
	m_mapSize.row = MEDIUMMAPROW;
	m_mapSize.col = MEDIUMMAPCOL;
	m_Score = 0;
}

CBaseGame::~CBaseGame()
{
}

Vertex CBaseGame::startGame()
{
	m_gameL.InitMap(m_graph, m_mapSize);
	//辅助逻辑判断设置为下次选择为第一次选中元素
	m_bFirstSelect = true;

	return m_mapSize;
}