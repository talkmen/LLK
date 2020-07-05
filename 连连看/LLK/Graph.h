#pragma once
#include "CONSTANT.h"
#include "global.h"
class CGraph
{
public:
	CGraph();
	~CGraph();
	void initGraph();
	void UpdateVertex(int index, int info);
	int GetVexnum();
	bool GetArc(int nV0, int nVi);
	void AddArc(int nV0, int nVi);
	int GetVertex(int nVi);
	void CGraph::updateArc(int index, Vertex m_mapSize);
	void ClearGraph();//清理图结构
	int getArcNum();
	void addVertex(int index, int info);
private:
	int m_Vertices[MAXMAPROW * MAXMAPCOL];
	bool m_AdjMatrix[MAXMAPROW * MAXMAPCOL][MAXMAPROW * MAXMAPCOL];
	int m_Vexnum; //顶点个数
	int m_nArcnum; //边个数

};

