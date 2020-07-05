// BaseGameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "BaseGameDlg.h"
#include "afxdialogex.h"

// CBaseGameDlg 对话框

IMPLEMENT_DYNAMIC(CBaseGameDlg, CDialogEx)

CBaseGameDlg::CBaseGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = 50;
	m_ptGame.y = 50;
	m_sizeElement.cx = 40;
	m_sizeElement.cy = 40;
	m_bFristPoint = true;
}

CBaseGameDlg::~CBaseGameDlg()
{
}

void CBaseGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CBaseGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CBaseGameDlg 消息处理程序

void CBaseGameDlg::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL,_T("source\\bmp\\海洋.bmp") , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//获取当前DC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);
	m_dcMem.SelectObject(bmp);
}

void CBaseGameDlg::updateGameMap()
{
	//绘制背景图片
	m_dcMem.BitBlt(0, 0, 1080, 675, &m_dcBG, 0, 0, SRCCOPY);
	//开始绘制
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <4; j++)
		{
			//参数说明
			//前两个参数控制绘制位置 第一个为距左端 第二个为距上端
			//然后两个控制绘制长宽，前为宽，后为长
			//控制从何处取
			//再接着控制取图片的位置
			//最后控制取图片的方式
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//与黑白图相或 在背景上显示图片的白色部分 黑全0 白全1
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask, m_anMap[i][j] * m_sizeElement.cx, 0, SRCPAINT);
			//与原图相与 在背景图上填充白色部分
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, m_anMap[i][j] * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

BOOL CBaseGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBaseGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//将游戏元素加载到程序中
void CBaseGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC cDC(this);
	CString elementPath = _T("source//element//smile.bmp");
	CString maskPath = _T("source//element//smile_mask.bmp");
	//加载Bmp图片资源 以及图片掩码资源 用于取出背景色
	HANDLE hBmpBG = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建兼容内存DC
	m_dcElement.CreateCompatibleDC(&cDC);
	m_dcMask.CreateCompatibleDC(&cDC);
	//将位图及掩码图片导入到DC
	m_dcElement.SelectObject(hBmpBG);
	m_dcMask.SelectObject(hBmpMask);
}

void CBaseGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CPaintDC dc(this); // device context for painting
		// TODO:  在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
		dc.BitBlt(0, 0, 1080, 675, &m_dcMem, 0, 0, SRCCOPY);
	}
}


void CBaseGameDlg::OnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码
	int map[4][4] = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		m_anMap[i][j] = map[i][j];
	
	//开始绘制
	updateGameMap();
	Invalidate(FALSE);//不擦除背景 在原有基础上进行更新
}


//为游戏中的元素绘制外框
void CBaseGameDlg::drawTipFrame(int nRow, int nCol)
{
	CClientDC cDC(this);//获取当前视频DC

	CBrush brush(RGB(233, 43, 43));//创建画刷

	//确定绘制矩形位置
	CRect rtTipFrame;
	rtTipFrame.left = nCol*m_sizeElement.cx + m_ptGame.x;
	rtTipFrame.top = nRow*m_sizeElement.cy + m_ptGame.y;
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;

	//绘制矩形
	cDC.FrameRect(rtTipFrame, &brush);
}

bool CBaseGameDlg::isLink()
{
	
}

void CBaseGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x < m_ptGame.x || point.y < m_ptGame.y)
		return CDialogEx::OnLButtonUp(nFlags, point);
	
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//点击图片在数组中的行下标
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//点击图片在数组中的列下标

}
