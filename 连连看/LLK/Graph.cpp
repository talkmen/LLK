#include "stdafx.h"
#include "Graph.h"

CGraph::CGraph()
{
	initGraph();
}

CGraph::~CGraph()
{
}

void CGraph::initGraph()
{
	for (int i = 0; i < MAXMAPROW*MAXMAPCOL; i++)
	{
		m_Vertices[i] = BLANK;
		for (int j = 0; j < MAXMAPROW * MAXMAPCOL; j++)
			m_AdjMatrix[i][j] = 0;
	}
	m_Vexnum = 0;
	m_nArcnum = 0;
}

void CGraph::UpdateVertex(int index, int info)
{
	if (index < m_Vexnum)
		m_Vertices[index] = info;
}

void CGraph::addVertex(int index, int info)
{
	if (index < MAXMAPCOL * MAXMAPROW)
	{
		m_Vertices[index] = info;
		m_Vexnum++;
	}
}

int CGraph::GetVexnum()
{
	return m_Vexnum;
}

bool CGraph::GetArc(int nV0, int nVi)
{
	if (nV0 < m_Vexnum && nVi < m_Vexnum)
		return m_AdjMatrix[nV0][nVi];
	return false;
}

void CGraph::AddArc(int nV0, int nVi)
{
	if (nV0 < m_Vexnum && nV0 < m_Vexnum)
	{
		m_AdjMatrix[nV0][nVi] = 1;
		m_AdjMatrix[nVi][nV0] = 1;
		m_nArcnum += 2;
	}		
}

int CGraph::GetVertex(int nVi)
{
	if (nVi < m_Vexnum)
		return m_Vertices[nVi];
	return BLANK;
}

void CGraph::updateArc(int index, Vertex m_mapSize)
{
	int row = index / m_mapSize.col;
	int col = index % m_mapSize.col;
	int index1 = 0;
	if (row >= 1)
	{
		index1 = index - m_mapSize.col;
		if (m_Vertices[index1] == m_Vertices[index] || m_Vertices[index1] == BLANK || m_Vertices[index] == BLANK)
		{
			if (!m_AdjMatrix[index1][index])
			{
				m_AdjMatrix[index1][index] = 1;
				m_AdjMatrix[index][index1] = 1;
				m_nArcnum += 2;
			}
		}
	}
	if (row < m_mapSize.row - 1)
	{
		index1 = index + m_mapSize.col;
		if (m_Vertices[index1] == m_Vertices[index] || m_Vertices[index1] == BLANK || m_Vertices[index] == BLANK)
		{
			if (!m_AdjMatrix[index1][index])
			{
				m_AdjMatrix[index1][index] = 1;
				m_AdjMatrix[index][index1] = 1;
				m_nArcnum += 2;
			}
		}
	}
	if (col >= 1)
	{
		index1 = index - 1;
		if (m_Vertices[index1] == m_Vertices[index] || m_Vertices[index1] == BLANK || m_Vertices[index] == BLANK)
		{
			if (!m_AdjMatrix[index1][index])
			{
				m_AdjMatrix[index1][index] = 1;
				m_AdjMatrix[index][index1] = 1;
				m_nArcnum += 2;
			}
		}
	}
	if (col < m_mapSize.col - 1)
	{
		index1 = index + 1;
		if (m_Vertices[index1] == m_Vertices[index] || m_Vertices[index1] == BLANK || m_Vertices[index] == BLANK)
		{
			if (!m_AdjMatrix[index1][index])
			{
				m_AdjMatrix[index1][index] = 1;
				m_AdjMatrix[index][index1] = 1;
				m_nArcnum += 2;
			}
		}
	}
}

int CGraph::getArcNum()
{
	return m_nArcnum;
}

void CGraph::ClearGraph()
{
	initGraph();
}
