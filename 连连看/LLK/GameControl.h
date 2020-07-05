#pragma once
#include "GameLogic.h"
#include "global.h"
#include "Graph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	int getElement(int nRow, int nCol);
	void setFirstVertex(int nRow, int nCol);//���õ�һ��ѡ�е������
	void setSecVertex(int nRow, int nCol);//���õڶ���ѡ�е������
	Vertex getFirstVertex();//��ȡ��һ��ѡ�е������
	Vertex getSecVertex();//��ȡ�ڶ���ѡ�е������
	int Link(int nRow, int nCol);//��Ӧ�û������ͼ�е�Ԫ��
	LN* getLineOfTwoVex();//���ؿɴ�����
	void ClearLNNode(); //��ʼ��pNode
	void doAfterGameOver(); //����
	int changeGameStatus();//�ı���Ϸ״̬
	int getPath(int path[MAXMAPROW * MAXMAPCOL]);//�õ�����·��
	void addScore();
	int calScore(int time); //�������
	bool saveScore(int nScore, int GameModel); //�������
	int getScore(); //�õ��÷�
	virtual Vertex startGame() = 0;//��ʼ��Ϸ ��Ӧ��ʼ��Ϸ��ť
	virtual int JudgeWin(int Time);//�ж�ʤ��
	virtual int getTips();//��ʾ
	virtual int ResortGame();//����
	void setMapSize(int row, int col);
	Vertex getMapSize();
protected:
	//��������Ҫ����
	CGameLogic m_gameL;//��Ϸ�߼�
	int m_anMap[4][4];//��ͼ����

	CGraph m_graph;
	Vertex m_ptSelFirst;//��һ��ѡ��������
	Vertex m_ptSelSecond;//�ڶ���ѡ�������

	int m_GameStatus;//��Ϸ״̬

	LN m_phNode[MAXLNNUM];
	int m_Path[MAXMAPROW * MAXMAPCOL];//·��
	int m_VexNum;
	int m_Score;		//��Ϸ�÷�
	Vertex m_mapSize;//��Ϸ��ͼ������Ԫ�ظ���
	bool m_bFirstSelect;//�Ƿ�Ϊ��һ��ѡ�У���Ϸ�и����жϴ����߼�

};

