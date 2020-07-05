
// LLKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "GameDlg.h"
#include "HelpDialog.h"
#include "EasyGameDlg.h"
#include "RankDlg.h"
#include "Config.h"
#include "SettingDlg.h"
#include <fstream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg 对话框



CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLLKDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_CASUAL, &CLLKDlg::OnBnClickedButtonCasual)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLLKDlg::OnBnClickedButtonRank)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLLKDlg::OnBnClickedButtonSet)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	InitBackground();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
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
		CDialogEx::OnPaint();		
	}
	else
	{
		CPaintDC cpDC(this);//绘制DC

		//将位图从位图内存拷贝纸视频内存中去
		cpDC.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
		////创建CPaintPC对象
		//CPaintDC dc(this);
		//
		////创建字体
		//CFont font;
		//font.CreatePointFont(200, _T("Microsoft Yahei"));

		////将字体选进DC
		//CFont *oldFront;
		//oldFront = dc.SelectObject(&font);
		//
		////设置字体颜色
		//dc.SetTextColor(RGB(125, 125, 125));
		//dc.SetBkColor(RGB(249, 205, 173));

		////设置字体居中
		//CRect rect;
		//GetClientRect(&rect);
		//CString  strText = _T("Welcome to LLK-GAME");
		//CSize size = dc.GetTextExtent(strText, strText.GetLength());
		//int x = (rect.Width() - size.cx + 1) / 2;
		//int y = (rect.Height() - size.cy + 1) / 2;

		////设置对话框背景颜色
		//dc.FillSolidRect(rect, RGB(249, 205, 173));

		////绘制欢迎语
		//dc.TextOut(x, y, strText);
		//

		//CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground()
{
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_MAIN_BG);//加载位图

	//创建兼容DC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);

	//将图片选入DC
	m_dcMem.SelectObject(&bmpMain);
}

//基本模式按钮点击时，所执行的操作
void CLLKDlg::OnClickedButtonBasic()
{
	m_Config->Load();
	this->ShowWindow(SW_HIDE);//当前主程序界面隐藏
	CGameDlg testDlg(m_Config);
	testDlg.DoModal();

	m_BGPath.Format(L"%s", m_Config->getMusicPath());
	m_BGPlaying = m_Config->getBgMusic();
	//创建游戏对话框
	//游戏对话框执行结束 主界面显示

	this->ShowWindow(SW_SHOW);

}

//休闲模式按钮点击时，所执行的操作
void CLLKDlg::OnBnClickedButtonCasual()
{
	this->ShowWindow(SW_HIDE);//当前主程序界面隐藏
	m_Config->Load();
	CEasyGameDlg testDlg(m_Config);
	testDlg.DoModal();

	//创建游戏对话框

	m_BGPath.Format(L"%s", m_Config->getMusicPath());
	m_BGPlaying = m_Config->getBgMusic();


	//游戏对话框执行结束 主界面显示

	this->ShowWindow(SW_SHOW);

	
}

void CLLKDlg::OnBnClickedButtonHelp()
{
	CHelpDialog helpDlg(GAME_MAIN_FRAME);

	helpDlg.DoModal();
}

void CLLKDlg::OnBnClickedButtonRank()
{
	CRankDlg rankDlg;
	rankDlg.DoModal();
}

void CLLKDlg::OnBnClickedButtonLevel()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CLLKDlg::OnBnClickedButtonSet()
{ 
	// TODO: 在此添加控件通知处理程序代码
	m_Config->Load();
	CSettingDlg settingDlg(m_Config);
	if (IDOK == settingDlg.DoModal())
	{
		m_Config->Save();
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

int CLLKDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_Config = new CConfig();
	m_Config->Load();
	m_BGPlaying = m_Config->getBgMusic();
	m_BGPath.Format(L"%s", m_Config->getMusicPath());
	if (m_BGPlaying)
	{
		CString str = m_Config->getMusicPath();
		str.Format(L"play %s repeat", str);
		mciSendString(str, 0, 0, 0);
	}
	return 1;
}

void CLLKDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	delete m_Config;
	CDialogEx::OnClose();
}


