#pragma once
#include "global.h"
#include "CONSTANT.h"
#include "Graph.h"
class CGameLogic
{
private :
	int m_nCorner; //�յ���
public:
	CGameLogic();
	~CGameLogic();
	void InitMap_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex mapSize);//��ʼ����ͼ
	void InitMap(CGraph &g, Vertex m_mapSize);//��ʼ����ͼ
	bool IsLink_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize);//�ж��Ƿ������
	void Clear_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);//���ѡ��ͼƬ
	void Clear(CGraph &graph, Vertex sFirstSelect, Vertex sSecSelect, Vertex m_mapSize);//���ѡ��ͼƬ
	void Resort(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex m_mapSize);//��Ԫ������
	void EmptyMap(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex mapSIze);//��յ�ͼ
	void UpdateArc(CGraph &g, int nRow, int nCol, Vertex m_mapSize);//���±�
	bool IsBlank(CGraph &g, Vertex m_mapSize);//�ж��Ƿ�ȫ����ɾ��
	//�ж������Ƿ������
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	//��Ѱһ�����������ͼƬ
	int SearchValidPath(CGraph &graph, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	void Resort(CGraph &graph, Vertex m_mapSize);
private:
	//���ӹ���
	bool ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize);
	//�����ж�
	bool LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	bool LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	//�����洢
	void setLNArray(LN pNode[MAXLNNUM], Vertex sNode, int nIndex);
	bool setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4, int m_anMap[MAXMAPROW][MAXMAPCOL], int nStatus);

	//�����������
	bool SearchPath(CGraph &graph, int nV0, int nV1, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize);
	//�ж϶����Ƿ���·����
	bool IsExsit(int nVi, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	int PushVertex(int nv, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	void PopVertex(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	//�ж��Ƿ�Ϊ�յ�
	bool IsCornor(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum);
	//�õ����ڵ��ĸ�����
	void GetDirect(int index, int target, int direct[], Vertex m_mapSize);
	//����
	void swap(int &a, int &b);
	//�ж�index�Ƿ��ڱ߽�
	bool IsBoard(int index, Vertex m_mapSize);
};

