#pragma once
#include "global.h"
#include "CONSTANT.h"
#include "Graph.h"
class CGameLogic
{
private :
	int m_nCorner; //拐点数
public:
	CGameLogic();
	~CGameLogic();
	void InitMap_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex mapSize);//初始化地图
	void InitMap(CGraph &g, Vertex m_mapSize);//初始化地图
	bool IsLink_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize);//判断是否可连接
	void Clear_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);//清除选中图片
	void Clear(CGraph &graph, Vertex sFirstSelect, Vertex sSecSelect, Vertex m_mapSize);//清除选中图片
	void Resort(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex m_mapSize);//将元素重排
	void EmptyMap(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex mapSIze);//清空地图
	void UpdateArc(CGraph &g, int nRow, int nCol, Vertex m_mapSize);//更新边
	bool IsBlank(CGraph &g, Vertex m_mapSize);//判断是否全部被删除
	//判断两点是否可消除
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	//搜寻一组可能消除的图片
	int SearchValidPath(CGraph &graph, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	void Resort(CGraph &graph, Vertex m_mapSize);
private:
	//消子规则
	bool ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize);
	//辅助判断
	bool LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	bool LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	//辅助存储
	void setLNArray(LN pNode[MAXLNNUM], Vertex sNode, int nIndex);
	bool setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4, int m_anMap[MAXMAPROW][MAXMAPCOL], int nStatus);

	//深度优先搜索
	bool SearchPath(CGraph &graph, int nV0, int nV1, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	//判断顶点是否在路径中
	bool IsExsit(int nVi, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	int PushVertex(int nv, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	void PopVertex(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	//判断是否为拐点
	bool IsCornor(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	//得到相邻的四个顶点
	void GetDirect(int index, int target, int direct[], Vertex m_mapSize);
	//交换
	void swap(int &a, int &b);
	//判断index是否在边界
	bool IsBoard(int index, Vertex m_mapSize);
};

