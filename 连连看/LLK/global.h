#pragma once
typedef struct tagVertex
{
	int row;//�к�
	int col;//�к�
	int info;
}Vertex, LN; //ͼ��������Ϣ

typedef struct tagScore
{
	int nMode;//��Ϸģʽ
	int nGrade;//���ַ���
	int nLevel;//���ֵȼ�
	CString strName;//�������
}SCORE;
typedef struct tagRankArray
{
	CString playerName;//����
	int nGrade;//�÷�
}RankArray;
typedef struct tagCString
{
	CString CStr;
	struct tagCString* next;
}CStr, *pCStr;

