// EasyGameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "EasyGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SettingDlg.h"
#include "GameLevelDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// CEasyGameDlg 对话框

IMPLEMENT_DYNAMIC(CEasyGameDlg, CDialogEx)

CEasyGameDlg::CEasyGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEasyGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CEasyGame();
}

CEasyGameDlg::CEasyGameDlg(CConfig *config, CWnd* pParent /*=NULL*/)
: CDialogEx(CEasyGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CEasyGame();
	m_Config = config;
	m_BGPlaying = m_Config->getBgMusic();
	m_BGPath.Format(L"%s", m_Config->getMusicPath());
}

CEasyGameDlg::~CEasyGameDlg()
{
	delete m_gameCM;
}

void CEasyGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_DES, m_text);
}

BEGIN_MESSAGE_MAP(CEasyGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CEasyGameDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CEasyGameDlg::OnClickedButtonTips)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CEasyGameDlg::OnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_RESORT, &CEasyGameDlg::OnClickedButtonResort)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CEasyGameDlg::OnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CEasyGameDlg::OnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CEasyGameDlg::OnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_TOOL, &CEasyGameDlg::OnClickedButtonTool)
	ON_BN_CLICKED(IDC_BUTTON_END, &CEasyGameDlg::OnBnClickedButtonEnd)
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEasyGameDlg 消息处理程序

// GameDlg 消息处理程序
void CEasyGameDlg::InitBackground()
{
	//调用API函数加载位图
	CString cstrBGPPath = m_Config->getStrBGPPath();
	//CString cstrBGPPath = _T("source\\bmp\\海洋.bmp");
	HANDLE bmp = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpPause = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//获取当前DC
	CClientDC clientDC(this);
	//创建与当前内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&clientDC);
	m_dcPause.CreateCompatibleDC(&clientDC);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);
	m_dcPause.SelectObject(bmpPause);

	//初始化视频内存DC
	m_dcMem.CreateCompatibleDC(&clientDC);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&clientDC, GAME_WIDTH, GAME_HEIGHT);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
}

void CEasyGameDlg::updateGameMap()
{
	//绘制背景图片
	m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
	//开始绘制
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j < m_mapSize.col; j++)
		{
			//参数说明
			//前两个参数控制绘制位置 第一个为距左端 第二个为距上端
			//然后两个控制绘制长宽，前为宽，后为长
			//控制从何处取
			//再接着控制取图片的位置
			//最后控制取图片的方式
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//与黑白图相或 在背景上显示图片的白色部分 黑全0 白全1
			int value = m_gameCM->getElement(i, j);
			if (value == BLANK)	continue;
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask, value * m_sizeElement.cx, 0, SRCPAINT);
			//与原图相与 在背景图上填充白色部分
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, value * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

void CEasyGameDlg::OnPaint()
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
		dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
	}
}

void CEasyGameDlg::OnClickedButtonStart()
{
	CFont f;
	f.CreatePointFont(150, _T("微软雅黑"), NULL);
	m_text.SetFont(&f);
	// TODO:  在此添加控件通知处理程序代码
	m_mapSize = m_gameCM->startGame();
	m_Playing = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(true);
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;
	//开始绘制
	updateGameMap();
	getScoreAndTool();
	m_text.SetWindowText(m_StringText);
	Invalidate(FALSE);//不擦除背景 在原有基础上进行更新

}

CString CEasyGameDlg::getScoreAndTool()
{
	m_StringText.Format(L"积分为：%d \n道具数为：%d", m_gameCM->getScore(), m_gameCM->getTool());
	return m_StringText;
}

void CEasyGameDlg::OnClickedButtonTips()
{
	int path[MAXMAPCOL * MAXMAPROW];
	int Vexnums;
	int result = m_gameCM->getTips();
	getScoreAndTool();
	m_text.SetWindowText(m_StringText);
	if (result  == TIPS_GET)
	{
		Vexnums = m_gameCM->getPath(path);
		int index1 = path[0];
		int index2 = path[Vexnums - 1];
		int row = index1 / m_mapSize.col;
		int col = index1 % m_mapSize.col;
		drawTipFrame(row, col);//绘制矩形框
		row = index2 / m_mapSize.col;
		col = index2 % m_mapSize.col;
		drawTipFrame(row, col);//绘制矩形框
		drawTipLine(path, Vexnums);//绘制连线
		
		Sleep(2000);
		InvalidateRect(m_gameRect, FALSE);
	}
	else if (result == TIPS_NOTFIND)
	{
		if (IDYES == MessageBox(_T("无法联通，是否重排"), _T("提示"), MB_YESNO))
		{
			m_gameCM->ResortGame(true);
			updateGameMap();
			InvalidateRect(m_gameRect, FALSE);
		}
	}
	else if (result == SCORENOTENOUGH)
		MessageBox(_T("      积分不足      "), _T("提示"));
}

void CEasyGameDlg::OnClickedButtonPause()
{
	m_Pause = !m_Pause;
	if (m_Pause)
	{
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("继续游戏"));
		m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));
		updateGameMap();
		Invalidate(FALSE);
	}
}

void CEasyGameDlg::OnClickedButtonResort()
{
	// TODO:  在此添加控件通知处理程序代码
	int result = m_gameCM->ResortGame();
	if (result == SCORENOTENOUGH)
		MessageBox(_T("      积分不足      "), _T("提示"));
	else if (result == SUCCESS)
	{
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);
		updateGameMap();
		InvalidateRect(m_gameRect, FALSE);
	}	
}

void CEasyGameDlg::OnClickedButtonSet()
{
	m_Config->Load();
	CSettingDlg settingDlg(m_Config);
	if (IDOK == settingDlg.DoModal())
	{
		m_Config->Save();
		updateTheme();
		CString str = m_Config->getMusicPath();
		CString temp;
		if (!m_BGPath.CompareNoCase(str))
		{
			if (m_Config->getBgMusic() && !m_BGPlaying)
			{
				temp.Format(L"play %s repeat", str);
				mciSendString(temp, 0, 0, 0);
				m_BGPlaying = !m_BGPlaying;
			}
			else if (!m_Config->getBgMusic() && m_BGPlaying)
			{
				temp.Format(L"stop %s", str);
				mciSendString(temp, 0, 0, 0);
				m_BGPlaying = !m_BGPlaying;
			}
		}
		else if (m_Config->getBgMusic())
		{
			temp.Format(L"stop %s", m_BGPath);
			mciSendString(temp, 0, 0, 0);
			m_BGPath.Format(L"%s", str);

			temp.Format(L"play %s repeat", str);
			mciSendString(temp, 0, 0, 0);
			m_BGPlaying = true;
		}
		else
		{
			temp.Format(L"stop %s", m_BGPath);
			mciSendString(temp, 0, 0, 0);
			m_BGPath.Format(L"%s", str);
			m_BGPlaying = false;
		}
	}
}

void CEasyGameDlg::OnClickedButtonLevel()
{
	CGameLevelDlg level(m_gameCM);
	level.DoModal();
	if (m_gameCM->getMapSize().row != m_mapSize.row)
		GameOver();
}

void CEasyGameDlg::OnClickedButtonHelp()
{
	CHelpDialog helpDialog(GAME_MODEL_EASY);
	helpDialog.DoModal();
}

void CEasyGameDlg::OnClickedButtonTool()
{
	if (!m_gameCM->setUse())
		MessageBox(_T("道具不足"), _T("提示"));
	else
	{
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);
	}
}

BOOL CEasyGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEasyGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//将游戏元素加载到程序中
void CEasyGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC cDC(this);
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	/*CString elementPath = _T("source//element//smile.bmp");
	CString maskPath = _T("source//element//smile_mask.bmp");*/
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

void CEasyGameDlg::updateTheme()
{
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	CString bgpPath = m_Config->getStrBGPPath();

	HANDLE hBmpElement = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpBgp = ::LoadImage(NULL, bgpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.SelectObject(hBmpElement);
	m_dcMask.SelectObject(hBmpMask);
	m_dcBG.SelectObject(hBmpBgp);
	m_dcPause.SelectObject(hBmpBgp);

	updateGameMap();
	Invalidate(FALSE);
}

//为游戏中的元素绘制外框
void CEasyGameDlg::drawTipFrame(int nRow, int nCol)
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

//绘制两图片间的连接线
void CEasyGameDlg::drawTipLine(int pNode[], int Vexnums)
{
	//获取当前DC
	CClientDC cDC(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = cDC.SelectObject(&penLine);

	int row = pNode[0] / m_mapSize.col;
	int col = pNode[0] % m_mapSize.col;
	int nStartX = m_ptGame.x + col*m_sizeElement.cx + m_sizeElement.cx / 2;
	int nStartY = m_ptGame.y + row*m_sizeElement.cy + m_sizeElement.cy / 2;
	//设置起点
	cDC.MoveTo(nStartX, nStartY);
	for (int i = 1; i < Vexnums; i++)
	{
		//绘制连线
		row = pNode[i] / m_mapSize.col;
		col = pNode[i] % m_mapSize.col;
		nStartX = m_ptGame.x + col*m_sizeElement.cx + m_sizeElement.cx / 2;
		nStartY = m_ptGame.y + row*m_sizeElement.cy + m_sizeElement.cy / 2;

		//从起点向终点画线
		cDC.LineTo(nStartX, nStartY);
	}
	//将原画笔返回
	cDC.SelectObject(pOldPen);
}

void CEasyGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if ((point.x <= m_ptGame.x) || (point.y <= m_ptGame.y))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if ((point.x >= m_gameRect.right) || (point.y >= m_gameRect.bottom))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//点击图片在数组中的行下标
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//点击图片在数组中的列下标

	switch (m_gameCM->Link(nRow, nCol))
	{
	case SELECTBLANK:
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
		break;
	}
	case FIRSTSELECT:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
		break;
	}
	case CLEARSELECT:
	{
		int path[MAXMAPROW * MAXMAPCOL];
		drawTipFrame(nRow, nCol);//绘制矩形框
		int vexnum = m_gameCM->getPath(path);
		drawTipLine(path, vexnum);//绘制连线
		m_gameCM->addScore();
		m_gameCM->updateTool(true);
		//更新游戏地图
		updateGameMap();

		Sleep(200);
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);

		InvalidateRect(m_gameRect, FALSE);
		
		if (m_gameCM->JudgeWin() == GAME_SUCCESS)
			GameOver();
		break;
	}
	case RESELECT:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
		InvalidateRect(m_gameRect, FALSE);
		break;
	}
	default:
		break;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

HBRUSH CEasyGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DES)
	{
		pDC->SetTextColor(RGB(255, 0, 0));   //设置字体颜色
		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);   // 设置背景色
	}
	else
		return hbr;
}

CString CEasyGameDlg::getGameOverMes()
{
	CString gameCal;
	gameCal.Format(_T("\t休闲模式\n\t游戏完成，恭喜您！！！\n\t最终得分:%d\n\n\t是否保存成绩？\n"), m_gameCM->calScore());
	return gameCal;
}

void CEasyGameDlg::OnBnClickedButtonEnd()
{
	GameOver();
}

void CEasyGameDlg::GameOver()
{
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	if (m_gameCM->JudgeWin() == GAME_SUCCESS)
	{
		if (IDYES == MessageBox(getGameOverMes(), _T("结束"), MB_YESNO))
			m_gameCM->saveScore(m_gameCM->calScore(), GAME_MODEL_EASY);
	}
	m_StringText.Format(L" ");
	m_text.SetWindowText(m_StringText);
	m_gameCM->doAfterGameOver();
	m_Playing = false;
	m_Pause = false;
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
}
