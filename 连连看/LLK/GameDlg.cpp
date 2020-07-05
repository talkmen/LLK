// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CONSTANT.h"
#include "HelpDialog.h"
#include "BaseGame.h"
#include "SettingDlg.h"
#include "GameLevelDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
// GameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_BGPlaying = false;
	m_gameCM = new CBaseGame();
}

CGameDlg::CGameDlg(CConfig *config, CWnd* pParent /*=NULL*/)
: CDialogEx(CGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CBaseGame();
	m_Config = config;
	m_BGPlaying = m_Config->getBgMusic();
	m_BGPath.Format(L"%s", m_Config->getMusicPath());
}

CGameDlg::~CGameDlg()
{
	delete m_gameCM;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIME, m_GameProgress);
	DDX_Control(pDX, IDC_STATIC_TIME, m_leastTime);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESORT, &CGameDlg::OnBnClickedButtonResort)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CGameDlg::OnClickedButtonTips)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnClickedButtonHelp)

	ON_BN_CLICKED(IDC_BUTTON_SET, &CGameDlg::OnBnClickedButtonSet)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CGameDlg::OnBnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_END, &CGameDlg::OnBnClickedButtonEnd)
END_MESSAGE_MAP()

// GameDlg 消息处理程序
void CGameDlg::InitBackground()
{
	//调用API函数加载位图
	CString cstrBGPPath = m_Config->getStrBGPPath();
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

//初始化进度条
void CGameDlg::initGameProgress()
{
	//设置字体
	CFont f;
	f.CreatePointFont(150, _T("微软雅黑"), NULL);
	m_leastTime.SetFont(&f);
	int preTimeGrade = (int)sqrt((double)(m_mapSize.col - 2));
	int gameTime = (m_mapSize.row - 2)*(m_mapSize.col - 2) * preTimeGrade;
	//初始化进度条长度
	m_GameProgress.SetRange(0, gameTime);
	//设置进度条步长
	m_GameProgress.SetStep(-1);
	//设置进度条起始位置
	m_GameProgress.SetPos(gameTime);

	//为进度条添加定时器
	SetTimer(PLAY_TIMER_ID, 1000, NULL);//定时器ID为PLAY_TIMER_ID 间隔时间1000ms 回调函数为系统默认
}

//绘制游戏剩余时间
void CGameDlg::drawGameTime()
{
	CClientDC pDC(this);//获取绘制环境

	CFont timeFont;
	timeFont.CreatePointFont(200, _T("Microsoft Yahei"));//高度及字体样式
	CFont *oldFont;
	//将字体选入设备环境
	oldFont = pDC.SelectObject(&timeFont);
	//设置字体颜色
	pDC.SetTextColor(RGB(255, 0, 0));
	pDC.SetBkMode(TRANSPARENT);
	//获取文字输出位置
	CRect textRect;
	(GetDlgItem(IDC_PROGRESS_TIME))->GetClientRect(&textRect);
	textRect.left = textRect.right;
	textRect.right += 60;
	//绘制文字
	CString cstr;
	cstr.Format(L"%d s", m_GameProgress.GetPos());
	pDC.TextOut(textRect.left, textRect.top, cstr);
	//将字体还原
	pDC.SelectObject(oldFont);
	//绘制区域
	InvalidateRect(textRect, TRUE);
}

void CGameDlg::updateGameMap()
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

BOOL CGameDlg::OnInitDialog()
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
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//将游戏元素加载到程序中
void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC cDC(this);
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	//CString elementPath = _T("source//element//star.bmp");
	//CString maskPath = _T("source//element//star_mask.bmp");
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

void CGameDlg::OnPaint()
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

void CGameDlg::OnClickedButtonStart()
{
	// TODO:  在此添加控件通知处理程序代码
	m_mapSize = m_gameCM->startGame();
	m_Playing = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false); 
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(true);
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;
	//开始绘制
	updateGameMap();

	//绘制时间
	initGameProgress();

	Invalidate(FALSE);//不擦除背景 在原有基础上进行更新
}

//为游戏中的元素绘制外框
void CGameDlg::drawTipFrame(int nRow, int nCol)
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
void CGameDlg::drawTipLine(int pNode[], int Vexnums)
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

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
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
		//更新游戏地图
		updateGameMap();
		
		Sleep(200);
		//使其显示出画线
		InvalidateRect(m_gameRect, FALSE);
		//获胜
		if (m_gameCM->JudgeWin(m_GameProgress.GetPos()) == GAME_SUCCESS)
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

void CGameDlg::OnBnClickedButtonResort()
{
	// TODO:  在此添加控件通知处理程序代码
	m_gameCM->ResortGame();
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
}

void CGameDlg::OnClickedButtonTips()
{
	int path[MAXMAPCOL * MAXMAPROW];
	int Vexnums;
	if (m_gameCM->getTips() == TIPS_GET)
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

		//更新游戏地图
		updateGameMap();

		Sleep(200);
		InvalidateRect(m_gameRect, FALSE);
	}
	else if (TIPS_NOTFIND)
	{
		KillTimer(PLAY_TIMER_ID);
		if (IDYES == MessageBox(_T("无法联通，是否重排"), _T("提示"), MB_YESNO))
		{
			m_gameCM->ResortGame();
			updateGameMap();
			InvalidateRect(m_gameRect, FALSE);
		}
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
	}
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_Pause)
	{
		if (nIDEvent == PLAY_TIMER_ID)
		{
			m_GameProgress.StepIt();
			CString  str;
			str.Format(L"剩余时间： %d s\n积分为：%d", m_GameProgress.GetPos(), m_gameCM->getScore());
			m_leastTime.SetWindowText(str);
			if (GAME_LOSER == m_gameCM->JudgeWin(m_GameProgress.GetPos()))
				GameOver();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::OnClickedButtonPause()
{
	m_Pause = !m_Pause;
	if (m_Pause)
	{
		KillTimer(PLAY_TIMER_ID);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("继续游戏"));
		m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(FALSE);
	}
	else
	{
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));
		updateGameMap();
		Invalidate(FALSE);
	}
}

void CGameDlg::OnClickedButtonHelp()
{
	KillTimer(PLAY_TIMER_ID);
	CHelpDialog helpDialog(GAME_MODEL_BASE);
	helpDialog.DoModal();
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

CString CGameDlg::getGameOverMes()
{
	CString gameCal;
	gameCal.Format(_T("\t基本模式\n\t游戏完成，恭喜您！！！\n\t最终得分:%d\n\n\t是否保存成绩？\n"), m_gameCM->calScore(m_GameProgress.GetPos()));
	return gameCal;
}

void CGameDlg::OnBnClickedButtonSet()
{
	if (m_Playing)
		KillTimer(PLAY_TIMER_ID);
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
	if (m_Playing)	
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::updateTheme()
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

void CGameDlg::OnClose()
{
	CDialogEx::OnClose();
}

void CGameDlg::OnBnClickedButtonLevel()
{
	if (m_Playing)
		KillTimer(PLAY_TIMER_ID);
	CGameLevelDlg level(m_gameCM);
	level.DoModal();
	if(m_gameCM->getMapSize().row != m_mapSize.row)
		GameOver();
	else if(m_Playing)
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::GameOver()
{
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	KillTimer(PLAY_TIMER_ID);
	if (m_gameCM->JudgeWin(m_GameProgress.GetPos()) == GAME_SUCCESS)
	{
		if (IDYES == MessageBox(getGameOverMes(), _T("结束"), MB_YESNO))
			m_gameCM->saveScore(m_gameCM->calScore(m_GameProgress.GetPos()), GAME_MODEL_BASE);	
	}
	else if (GAME_LOSER == m_gameCM->JudgeWin(m_GameProgress.GetPos()))
		MessageBox(_T("      时间到！游戏失败！！！       "), _T("失败"), NULL);
	CString str;
	str.Format(L" ");
	m_leastTime.SetWindowText(str);
	m_gameCM->doAfterGameOver();
	m_Playing = false;
	m_Pause = false;
	m_GameProgress.SetRange(0, 0);
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
}

void CGameDlg::OnBnClickedButtonEnd()
{
	GameOver();
}
