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
	//�����߼��ж�����Ϊ�´�ѡ��Ϊ��һ��ѡ��Ԫ��
	m_bFirstSelect = true;

	return m_mapSize;
}