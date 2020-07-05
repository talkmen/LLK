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

//清除可连接图片
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

//三条直线消子时封装的是否可以消子函数
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

//判断是否可以连接
bool CGameLogic::IsLink_Array(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM], Vertex m_mapSize)
{
	//两次选择为同一位置图片
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

//判断同行两点是否可连接
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

//判断同列两点是否可连接
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

//一条直线消子
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

	//横向连线
	inflexion.row = sFirstSelect.row;
	inflexion.col = sSecSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInRow(m_anMap, sFirstSelect, inflexion) && LinkInCol(m_anMap, inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	//纵向连线
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
	//两个拐点
	Vertex inflexionFirst;
	Vertex inflexionSecond;
	//同行且处边缘
	if ((sFirstSelect.row == sSecSelect.row)&&(sFirstSelect.row==0||(sFirstSelect.row==m_mapSize.row-1)))
	{
	//上边缘
		if (sFirstSelect.row == 0)
		{
			inflexionFirst.row = sFirstSelect.row-1;
			inflexionSecond.row = sSecSelect.row - 1;
		}
	//下边缘
		else if(sFirstSelect.row==m_mapSize.row-1)
		{
			inflexionFirst.row = sFirstSelect.row + 1;
			inflexionSecond.row = sSecSelect.row + 1;
		}
			inflexionFirst.col = sFirstSelect.col;
			inflexionSecond.col = sSecSelect.col;
			return setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, -1);			
	}
	//同列且处边缘
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
	
	//非边缘情况  
	//从起点向左右画线 
	int smallerCol;
	int biggerCol;
	bool startSmall;//起点是否在左边
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
	//试试从中间画 
	for (int col = smallerCol + 1; col < biggerCol; col++)
	{
		inflexionFirst.col = col;
		inflexionSecond.col = col;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
		{
			return true;
		}
	}
	if (startSmall)//线路次序为中间 左边 右边
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
		//线路次序为中间 右边 左边
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

	//从起点向上下画线
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
	//试试从中间开始
	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	//从上到下 优先上
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

//连接判断函数
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize)
{
	m_nCorner = 0;
	//获得顶点索引号
	int nV1Index = v1.row * m_mapSize.col + v1.col;
	int nV2Index = v2.row * m_mapSize.col + v2.col;
	if (graph.GetVertex(nV1Index) != graph.GetVertex(nV2Index))
		return false;
	PushVertex(nV1Index, m_Path, m_VexNum);  //压入第一个点
	//搜寻两点之间的连通路径
	if (SearchPath(graph, nV1Index, nV2Index, m_Path, m_VexNum, m_mapSize))
		return true;
	PopVertex(m_Path, m_VexNum);
	return false;
}

//交换
void CGameLogic::swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//得到相连的四个点
void CGameLogic::GetDirect(int index, int target, int direct[], Vertex m_mapSize)
{
	int row = index / m_mapSize.col;
	int col = index % m_mapSize.col;
	int rowt = target / m_mapSize.col;
	int colt = target % m_mapSize.col;
	
	//得到index可能到达的点
	int index1 = 0;
	index1 = index - m_mapSize.col;
	direct[0] = index1;

	index1 = index - 1;
	direct[1] = index1;

	index1 = index + m_mapSize.col;
	direct[2] = index1;

	index1 = index + 1;
	direct[3] = index1;


	//将这四个点根据优先级进行排序
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

//使用深度优先搜索法搜寻一条有效连通路径
bool CGameLogic::SearchPath(CGraph &graph, int nV0, int nV1, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum, Vertex m_mapSize)
{
	int direct[4] = { 0 };
	GetDirect(nV0, nV1, direct, m_mapSize);
	
	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int i = 0; i < 4; i++)	
	{
		if (graph.GetArc(nV0, direct[i]) && !IsExsit(direct[i], m_Path, m_VexNum))
		{
			//压入当前顶点，假设为路径的一个有效顶点
			PushVertex(direct[i], m_Path, m_VexNum);
			//当拐点数大于2 时，直接放弃该顶点
			if (m_nCorner > 2)
			{
				PopVertex(m_Path, m_VexNum);       //取出压入的顶点，与PushWertex(nVi)对应
				continue;
			}
			//当前顶点不是nVi时，继续搜寻下一个相邻且连通的顶点
			if (direct[i] != nV1)
			{
				//当中间顶点不为空时，表示该条路径不通
				if (graph.GetVertex(direct[i]) != BLANK)
				{
					PopVertex(m_Path, m_VexNum);    //取出压入的顶点，与PushWertex(nVi)对应
					continue;
				}
				//如果nVi是一个已消除的点，则判断（nVi，nV1）是否连通
				if (SearchPath(graph, direct[i], nV1, m_Path, m_VexNum, m_mapSize))
					return true;
			}
			else
				return true;

			PopVertex(m_Path, m_VexNum);     //取出压入的顶点，与PushWertex(nVi)对应
		}
	}
	return false;
}

//判断是否在路径中
bool CGameLogic::IsExsit(int nVi, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	for (int i = 0; i < m_VexNum; i++)
	{
		if (m_Path[i] == nVi)
			return true;
	}
	return false;
}

//入栈
int CGameLogic::PushVertex(int nv, int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	m_Path[m_VexNum++] = nv;
	if (IsCornor(m_Path, m_VexNum))
		m_nCorner++;
	return m_nCorner;
}

//出栈
void CGameLogic::PopVertex(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	if (IsCornor(m_Path, m_VexNum))
		m_nCorner--;
	m_VexNum--;
}

//清除可连接图片
void CGameLogic::Clear(CGraph &graph, Vertex sFirstSelect, Vertex sSecSelect, Vertex m_mapSize)
{
	int index1 = sFirstSelect.row * m_mapSize.col + sFirstSelect.col;
	int index2 = sSecSelect.row * m_mapSize.col + sSecSelect.col;
	graph.UpdateVertex(index1, BLANK);
	graph.UpdateVertex(index2, BLANK);
	graph.updateArc(index1, m_mapSize);
	graph.updateArc(index2, m_mapSize);
}

//更新边数组
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

//初始化地图
void CGameLogic::InitMap(CGraph &g, Vertex m_mapSize)
{
	int totalElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//地图初始化
	int randArray[MAXMAPROW * MAXMAPCOL];
	int randArrayIndex[MAXMAPROW * MAXMAPCOL];
	int elementArray[20] = { 0 };

	//地图位置序列 元素序列
	for (int i = 0; i < 20; i++)
	{
		randArrayIndex[i] = i;
		elementArray[i] = i;	//地图元素为0~19
	}
	for (int i = 20; i < totalElementNum; i++)
	{
		randArrayIndex[i] = i;
	}

	//剩余位置个数  以及剩余元素个数
	int leaveElement = 20;
	int leaveIndex = (m_mapSize.row - 2)*(m_mapSize.col - 2);

	//取出行数个元素

	for (int i = 0; i < m_mapSize.row - 2; i++)
	{
		///取出一个元素
		srand(unsigned(time(NULL)));
		int randNum = rand() % leaveElement;
		int curElement = elementArray[randNum];
		//交换元素
		elementArray[randNum] = elementArray[--leaveElement];

		//取出实际列数个位置
		for (int j = 0; j < m_mapSize.col - 2; j++)
		{
			//取出一个位置
			srand(unsigned(time(NULL)));
			int randLocIndex = rand() % leaveIndex;
			//取出该位置
			int relLocIndex = randArrayIndex[randLocIndex];
			//换掉该位置
			randArrayIndex[randLocIndex] = randArrayIndex[--leaveIndex];

			//将元素放入该位置
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

//判断是否为拐点
bool CGameLogic::IsCornor(int m_Path[MAXMAPROW * MAXMAPCOL], int &m_VexNum)
{
	if (m_VexNum >= 3)
		return (m_Path[m_VexNum - 1] + m_Path[m_VexNum - 3]) / 2 != m_Path[m_VexNum - 2];
	return false;
}

//判断是否全部消除
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

//搜寻功能
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