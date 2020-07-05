#include "stdafx.h"
#include "GameLogic.h"
#include "CONSTANT.h"
#include<fstream>
using namespace std;
CGameLogic::CGameLogic()
{
	m_nCorner = 0;
}

CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex m_mapSize)
{
	int anMap[4][4] = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j < m_mapSize.col; j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}
}

//���������ͼƬ
void CGameLogic::Clear_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	m_anMap[sFirstSelect.row][sFirstSelect.col] = BLANK;
	m_anMap[sSecSelect.row][sSecSelect.col] = BLANK;
}

void CGameLogic::setLNArray(LN pNode[MAXLNNUM], Vertex sNode, int nIndex)
{
	pNode[nIndex].row = sNode.row;
	pNode[nIndex].col = sNode.col;
	pNode[nIndex].info = true;
}

//����ֱ������ʱ��װ���Ƿ�������Ӻ���
bool CGameLogic::setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4, int m_anMap[MAXMAPROW][MAXMAPCOL], int nStatus)
{
	if (nStatus == -1)
	{
		setLNArray(pNode, v1, 0);
		setLNArray(pNode, v2, 1);
		setLNArray(pNode, v3, 2);
		setLNArray(pNode, v4, 3);
		return true;
	}
	if (nStatus == 0)
	{
		if ((m_anMap[v2.row][v2.col] == BLANK) && (m_anMap[v3.row][v3.col] == BLANK) && LinkInCol(m_anMap, v1, v2) && LinkInRow(m_anMap, v2, v3) && LinkInCol(m_anMap, v3, v4))
		{
			setLNArray(pNode, v1, 0);
			setLNArray(pNode, v2, 1);
			setLNArray(pNode, v3, 2);
			setLNArray(pNode, v4, 3);
			return true;
		}
	}
	else if (nStatus == 1)
	{
		if ((m_anMap[v2.row][v2.col] == BLANK) && (m_anMap[v3.row][v3.col] == BLANK) && LinkInRow(m_anMap, v1, v2) && LinkInCol(m_anMap, v2, v3) && LinkInRow(m_anMap, v3, v4))
		{
			setLNArray(pNode, v1, 0);
			setLNArray(pNode, v2, 1);
			setLNArray(pNode, v3, 2);
			setLNArray(pNode, v4, 3);
			return true;
		}
	}

	return false;
}

//�ж��Ƿ��������
bool CGameLogic::IsLink_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize)
{
	//����ѡ��Ϊͬһλ��ͼƬ
	if ((sFirstSelect.row == sSecSelect.row) && (sFirstSelect.col == sSecSelect.col))
		return false;
	else if (m_anMap[sFirstSelect.row][sFirstSelect.col] != m_anMap[sSecSelect.row][sSecSelect.col])
		return false;
	else if (ClearElementByOneLine(m_anMap, sFirstSelect, sSecSelect, pNode))
		return true;
	else if (ClearElementByTwoLine(m_anMap, sFirstSelect, sSecSelect, pNode))
		return true;
	else if (ClearElementByThreeLine(m_anMap, sFirstSelect, sSecSelect, pNode, m_mapSize))
		return true;
	return false;
}

//�ж�ͬ�������Ƿ������
bool CGameLogic::LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	int nRow = sFirstSelect.row;
	int smallerCol;
	int biggerCol;
	if (sFirstSelect.col < sSecSelect.col)
	{
		smallerCol = sFirstSelect.col;
		biggerCol = sSecSelect.col;
	}
	else
	{
		smallerCol = sSecSelect.col;
		biggerCol = sFirstSelect.col;
	}

	for (int i = smallerCol + 1; i < biggerCol; i++)
	{
		if (m_anMap[nRow][i] != BLANK)
		{
			return false;
		}
	}
	return true;
}

//�ж�ͬ�������Ƿ������
bool CGameLogic::LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	int nCol = sFirstSelect.col;
	int smallerRow;
	int biggerRow;
	if (sFirstSelect.row < sSecSelect.row)
	{
		smallerRow = sFirstSelect.row;
		biggerRow = sSecSelect.row;
	}
	else
	{
		smallerRow = sSecSelect.row;
		biggerRow = sFirstSelect.row;
	}

	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		if (m_anMap[row][nCol] != BLANK)
		{
			return false;
		}
	}
	return true;
}

//һ��ֱ������
bool CGameLogic::ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM])
{
	if (sFirstSelect.row == sSecSelect.row)
	{
		if (LinkInRow(m_anMap, sFirstSelect, sSecSelect))
		{
			setLNArray(pNode, sFirstSelect, 0);
			setLNArray(pNode, sSecSelect, 1);
			return true;
		}
	}
	if (sFirstSelect.col == sSecSelect.col)
	{
		if (LinkInCol(m_anMap, sFirstSelect, sSecSelect))
		{
			setLNArray(pNode, sFirstSelect, 0);
			setLNArray(pNode, sSecSelect, 1);
			return true;
		}
	}
	return false;
}

bool CGameLogic::ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM])
{
	Vertex inflexion;

	//��������
	inflexion.row = sFirstSelect.row;
	inflexion.col = sSecSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInRow(m_anMap, sFirstSelect, inflexion) && LinkInCol(m_anMap, inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	//��������
	inflexion.row = sSecSelect.row;
	inflexion.col = sFirstSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInCol(m_anMap, sFirstSelect, inflexion) && LinkInRow(m_anMap, inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	return false;
}

bool CGameLogic::ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize)
{
	//�����յ�
	Vertex inflexionFirst;
	Vertex inflexionSecond;
	//ͬ���Ҵ���Ե
	if ((sFirstSelect.row == sSecSelect.row)&&(sFirstSelect.row==0||(sFirstSelect.row==m_mapSize.row-1)))
	{
	//�ϱ�Ե
		if (sFirstSelect.row == 0)
		{
			inflexionFirst.row = sFirstSelect.row-1;
			inflexionSecond.row = sSecSelect.row - 1;
		}
	//�±�Ե
		else if(sFirstSelect.row==m_mapSize.row-1)
		{
			inflexionFirst.row = sFirstSelect.row + 1;
			inflexionSecond.row = sSecSelect.row + 1;
		}
			inflexionFirst.col = sFirstSelect.col;
			inflexionSecond.col = sSecSelect.col;
			return setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, -1);			
	}
	//ͬ���Ҵ���Ե
	if ((sFirstSelect.col == sSecSelect.col) && (sFirstSelect.col == 0 || sFirstSelect.col == m_mapSize.col - 1))
	{
		if (sFirstSelect.col == 0)
		{
			inflexionFirst.col = -1;
			inflexionSecond.col = -1;
		}
		else if (sFirstSelect.col == m_mapSize.col - 1)
		{
			inflexionFirst.col = m_mapSize.col;
			inflexionSecond.col = m_mapSize.col;
		}
		inflexionFirst.row = sFirstSelect.row;
		inflexionSecond.row = sSecSelect.row;
		return setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, -1);
	}
	
	//�Ǳ�Ե���  
	//����������һ��� 
	int smallerCol;
	int biggerCol;
	bool startSmall;//����Ƿ������
	if (sFirstSelect.col > sSecSelect.col)
	{
		smallerCol = sSecSelect.col;
		biggerCol = sFirstSelect.col;
		startSmall = false;
	}
	else
	{
		smallerCol = sFirstSelect.col;
		biggerCol = sSecSelect.col;
		startSmall = true;
	}

	inflexionFirst.row = sFirstSelect.row;
	inflexionSecond.row = sSecSelect.row;
	//���Դ��м仭 
	for (int col = smallerCol + 1; col < biggerCol; col++)
	{
		inflexionFirst.col = col;
		inflexionSecond.col = col;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
		{
			return true;
		}
	}
	if (startSmall)//��·����Ϊ�м� ��� �ұ�
	{
		for (int col = smallerCol - 1; col >= 0; col--)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
		for (int col = biggerCol + 1; col < m_mapSize.col; col++)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
	}
	else
	{
		//��·����Ϊ�м� �ұ� ���
		for (int col = biggerCol + 1; col < m_mapSize.col; col++)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
		for (int col = smallerCol - 1; col >= 0; col--)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
	}

	//����������»���
	int smallerRow;
	int biggerRow;
	if (sFirstSelect.row > sSecSelect.row)
	{
		smallerRow = sSecSelect.row;
		biggerRow = sFirstSelect.row;
	}
	else
	{
		smallerRow = sFirstSelect.row;
		biggerRow = sSecSelect.row;
	}

	inflexionFirst.col = sFirstSelect.col;
	inflexionSecond.col = sSecSelect.col;
	//���Դ��м俪ʼ
	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	//���ϵ��� ������
	for (int row = smallerRow - 1; row >= 0; row--)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	for (int row = biggerRow + 1; row<m_mapSize.row; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	return false;
}

//�����жϺ���
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize)
{
	m_nCorner = 0;
	//��ö���������
	int nV1Index = v1.row * m_mapSize.col + v1.col;
	int nV2Index = v2.row * m_mapSize.col + v2.col;
	if (graph.GetVertex(nV1Index) != graph.GetVertex(nV2Index))
		return false;
	PushVertex(nV1Index, m_Path, m_VexNum);  //ѹ���һ����
	//��Ѱ����֮�����ͨ·��
	if (SearchPath(graph, nV1Index, nV2Index, m_Path, m_VexNum, m_mapSize))
		return true;
	PopVertex(m_Path, m_VexNum);
	return false;
}

//����
void CGameLogic::swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//�õ��������ĸ���
void CGameLogic::GetDirect(int index, int target, int direct[], Vertex m_mapSize)
{
	int row = index / m_mapSize.col;
	int col = index % m_mapSize.col;
	int rowt = target / m_mapSize.col;
	int colt = target % m_mapSize.col;
	
	//�õ�index���ܵ���ĵ�
	int index1 = 0;
	index1 = index - m_mapSize.col;
	direct[0] = index1;

	index1 = index - 1;
	direct[1] = index1;

	index1 = index + m_mapSize.col;
	direct[2] = index1;

	index1 = index + 1;
	direct[3] = index1;


	//�����ĸ���������ȼ���������
	if (row == rowt)
	{
		swap(direct[0], direct[1]);
		if (col < colt)
			swap(direct[0], direct[3]);
	}
	else if (col == colt)
	{
		swap(direct[2], direct[3]);
		if (row < rowt)
			swap(direct[3], direct[0]);
	}
	else if (row > rowt)
	{
		swap(direct[3], direct[2]); 
		if (colt > col)
			swap(direct[1], direct[2]);
	}
	else if (row < rowt)
	{
		swap(direct[3], direct[2]);
		if (colt > col)
			swap(direct[1], direct[2]);
		swap(direct[0], direct[3]);
	}
}

//ʹ�����������������Ѱһ����Ч��ͨ·��
bool CGameLogic::SearchPath(CGraph &graph, int nV0, int nV1, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize)
{
	int direct[4] = { 0 };
	GetDirect(nV0, nV1, direct, m_mapSize);
	
	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int i = 0; i < 4; i++)	
	{
		if (graph.GetArc(nV0, direct[i]) && !IsExsit(direct[i], m_Path, m_VexNum))
		{
			//ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
			PushVertex(direct[i], m_Path, m_VexNum);
			//���յ�������2 ʱ��ֱ�ӷ����ö���
			if (m_nCorner > 2)
			{
				PopVertex(m_Path, m_VexNum);       //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
				continue;
			}
			//��ǰ���㲻��nViʱ��������Ѱ��һ����������ͨ�Ķ���
			if (direct[i] != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
				if (graph.GetVertex(direct[i]) != BLANK)
				{
					PopVertex(m_Path, m_VexNum);    //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
					continue;
				}
				//���nVi��һ���������ĵ㣬���жϣ�nVi��nV1���Ƿ���ͨ
				if (SearchPath(graph, direct[i], nV1, m_Path, m_VexNum, m_mapSize))
					return true;
			}
			else
				return true;

			PopVertex(m_Path, m_VexNum);     //ȡ��ѹ��Ķ��㣬��PushWertex(nVi)��Ӧ
		}
	}
	return false;
}

//�ж��Ƿ���·����
bool CGameLogic::IsExsit(int nVi, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	for (int i = 0; i < m_VexNum; i++)
	{
		if (m_Path[i] == nVi)
			return true;
	}
	return false;
}

//��ջ
int CGameLogic::PushVertex(int nv, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	m_Path[m_VexNum++] = nv;
	if (IsCornor(m_Path, m_VexNum))
		m_nCorner++;
	return m_nCorner;
}

//��ջ
void CGameLogic::PopVertex(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	if (IsCornor(m_Path, m_VexNum))
		m_nCorner--;
	m_VexNum--;
}

//���������ͼƬ
void CGameLogic::Clear(CGraph &graph, Vertex sFirstSelect, Vertex sSecSelect, Vertex m_mapSize)
{
	int index1 = sFirstSelect.row * m_mapSize.col + sFirstSelect.col;
	int index2 = sSecSelect.row * m_mapSize.col + sSecSelect.col;
	graph.UpdateVertex(index1, BLANK);
	graph.UpdateVertex(index2, BLANK);
	graph.updateArc(index1, m_mapSize);
	graph.updateArc(index2, m_mapSize);
}

//���±�����
void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol, Vertex m_mapSize)
{
	int index1 = nRow * m_mapSize.col + nCol;
	g.updateArc(index1, m_mapSize);
}

bool CGameLogic::IsBoard(int index, Vertex m_mapSize)
{
	if (index / m_mapSize.col == 0 || index / m_mapSize.col == m_mapSize.row - 1)
		return true;
	else if (index % m_mapSize.col == 0 || index % m_mapSize.col == m_mapSize.col - 1)
		return true;
	return false;
}

//��ʼ����ͼ
void CGameLogic::InitMap(CGraph &g, Vertex m_mapSize)
{
	int totalElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//��ͼ��ʼ��
	int randArray[MAXMAPROW * MAXMAPCOL];
	int randArrayIndex[MAXMAPROW * MAXMAPCOL];
	int elementArray[20] = { 0 };

	//��ͼλ������ Ԫ������
	for (int i = 0; i < 20; i++)
	{
		randArrayIndex[i] = i;
		elementArray[i] = i;	//��ͼԪ��Ϊ0~19
	}
	for (int i = 20; i < totalElementNum; i++)
	{
		randArrayIndex[i] = i;
	}

	//ʣ��λ�ø���  �Լ�ʣ��Ԫ�ظ���
	int leaveElement = 20;
	int leaveIndex = (m_mapSize.row - 2)*(m_mapSize.col - 2);

	//ȡ��������Ԫ��

	for (int i = 0; i < m_mapSize.row - 2; i++)
	{
		///ȡ��һ��Ԫ��
		srand(unsigned(time(NULL)));
		int randNum = rand() % leaveElement;
		int curElement = elementArray[randNum];
		//����Ԫ��
		elementArray[randNum] = elementArray[--leaveElement];

		//ȡ��ʵ��������λ��
		for (int j = 0; j < m_mapSize.col - 2; j++)
		{
			//ȡ��һ��λ��
			srand(unsigned(time(NULL)));
			int randLocIndex = rand() % leaveIndex;
			//ȡ����λ��
			int relLocIndex = randArrayIndex[randLocIndex];
			//������λ��
			randArrayIndex[randLocIndex] = randArrayIndex[--leaveIndex];

			//��Ԫ�ط����λ��
			randArray[relLocIndex] = curElement;
		}
	}
	int i = 0;
	int j = 0;
	while (j < m_mapSize.row * m_mapSize.col)
	{
		if (IsBoard(j,  m_mapSize))
			g.addVertex(j++, BLANK);
		else
			g.addVertex(j++, randArray[i++]);
			
	}

	fstream f("Vex.txt", ios::app);
	for (i = 0; i < m_mapSize.row * m_mapSize.col; i++)
	{
		g.updateArc(i, m_mapSize);
		if (i / m_mapSize.col == m_mapSize.row - 1)
			f << g.GetVertex(i) << " ";
	}
	f << endl;
		
	
}

//�ж��Ƿ�Ϊ�յ�
bool CGameLogic::IsCornor(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	if (m_VexNum >= 3)
		return (m_Path[m_VexNum - 1] + m_Path[m_VexNum - 3]) / 2 != m_Path[m_VexNum - 2];
	return false;
}

//�ж��Ƿ�ȫ������
bool CGameLogic::IsBlank(CGraph &g, Vertex m_mapSize)
{
	/*int vexNum = g.GetVexnum();
	int arcNum = g.getArcNum();
	int row = m_mapSize.row;
	int col = m_mapSize.col;
	int around = col * 2 + (row - 2) * 2; 
	int blankNum = 3 * around + 4 * (vexNum - around) - 4;

	if (blankNum == arcNum)
	{
		g.ClearGraph();
		return true;
	}
	return false;*/


	int vexNum = g.GetVexnum();
	for (int i = 0; i < vexNum; i++)
		if (g.GetVertex(i) != BLANK)
			return false;
	return true;
}

//��Ѱ����
int CGameLogic::SearchValidPath(CGraph &graph, int m_Path[MAXMAPROW * MAXMAPCOL], int &VexNum, Vertex m_mapSize)
{
	int temp;
	int g_vexnum = graph.GetVexnum();
	Vertex v1;
	Vertex v2;
	for (int i = 0; i < g_vexnum; i++)
	{
		temp = graph.GetVertex(i);
		if (temp != BLANK)
		{
			v1.row = i / m_mapSize.col;
			v1.col = i % m_mapSize.col;
			for (int j = i; j < g_vexnum; j++)
			if (graph.GetVertex(j) == temp)
			{
				VexNum = 0;
				v2.row = j / m_mapSize.col;
				v2.col = j % m_mapSize.col;
				if (IsLink(graph, v1, v2, m_Path, VexNum, m_mapSize))
					return TIPS_GET;
			}
		}	
	}
	return TIPS_NOTFIND;
}

void CGameLogic::Resort(CGraph &graph, Vertex m_mapSize)
{
	int vexnum = graph.GetVexnum();
	int row = m_mapSize.row;
	int col = m_mapSize.col;
	srand(unsigned(time(NULL)));
	int i = 0;
	while (i < 100)
	{
		int index1 = rand() % vexnum;
		int index2 = rand() % vexnum;
		if (IsBoard(index1, m_mapSize) || IsBoard(index2, m_mapSize))
			continue;
		int value1 = graph.GetVertex(index1);
		int value2 = graph.GetVertex(index2);
		graph.UpdateVertex(index1, value2);
		graph.UpdateVertex(index2, value1);
		i++;
	}
	for (i = 0; i < vexnum; i++)
		graph.updateArc(i, m_mapSize);
}