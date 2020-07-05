
// LLKDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLLKDlg �Ի���



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


// CLLKDlg ��Ϣ�������

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitBackground();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		CDialogEx::OnPaint();		
	}
	else
	{
		CPaintDC cpDC(this);//����DC

		//��λͼ��λͼ�ڴ濽��ֽ��Ƶ�ڴ���ȥ
		cpDC.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
		////����CPaintPC����
		//CPaintDC dc(this);
		//
		////��������
		//CFont font;
		//font.CreatePointFont(200, _T("Microsoft Yahei"));

		////������ѡ��DC
		//CFont *oldFront;
		//oldFront = dc.SelectObject(&font);
		//
		////����������ɫ
		//dc.SetTextColor(RGB(125, 125, 125));
		//dc.SetBkColor(RGB(249, 205, 173));

		////�����������
		//CRect rect;
		//GetClientRect(&rect);
		//CString  strText = _T("Welcome to LLK-GAME");
		//CSize size = dc.GetTextExtent(strText, strText.GetLength());
		//int x = (rect.Width() - size.cx + 1) / 2;
		//int y = (rect.Height() - size.cy + 1) / 2;

		////���öԻ��򱳾���ɫ
		//dc.FillSolidRect(rect, RGB(249, 205, 173));

		////���ƻ�ӭ��
		//dc.TextOut(x, y, strText);
		//

		//CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground()
{
	//����λͼ
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_MAIN_BG);//����λͼ

	//��������DC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);

	//��ͼƬѡ��DC
	m_dcMem.SelectObject(&bmpMain);
}

//����ģʽ��ť���ʱ����ִ�еĲ���
void CLLKDlg::OnClickedButtonBasic()
{
	m_Config->Load();
	this->ShowWindow(SW_HIDE);//��ǰ�������������
	CGameDlg testDlg(m_Config);
	testDlg.DoModal();

	m_BGPath.Format(L"%s", m_Config->getMusicPath());
	m_BGPlaying = m_Config->getBgMusic();
	//������Ϸ�Ի���
	//��Ϸ�Ի���ִ�н��� ��������ʾ

	this->ShowWindow(SW_SHOW);

}

//����ģʽ��ť���ʱ����ִ�еĲ���
void CLLKDlg::OnBnClickedButtonCasual()
{
	this->ShowWindow(SW_HIDE);//��ǰ�������������
	m_Config->Load();
	CEasyGameDlg testDlg(m_Config);
	testDlg.DoModal();

	//������Ϸ�Ի���

	m_BGPath.Format(L"%s", m_Config->getMusicPath());
	m_BGPlaying = m_Config->getBgMusic();


	//��Ϸ�Ի���ִ�н��� ��������ʾ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CLLKDlg::OnBnClickedButtonSet()
{ 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	delete m_Config;
	CDialogEx::OnClose();
}


