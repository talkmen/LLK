// GameLevelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameLevelDlg.h"
#include "afxdialogex.h"


// CGameLevelDlg �Ի���

IMPLEMENT_DYNAMIC(CGameLevelDlg, CDialogEx)

CGameLevelDlg::CGameLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameLevelDlg::IDD, pParent)
{
	
}

CGameLevelDlg::CGameLevelDlg(CGameControl *m_gameCM, CWnd* pParent /*=NULL*/)
: CDialogEx(CGameLevelDlg::IDD, pParent)
{
	this->m_gameCM = m_gameCM;
}

CGameLevelDlg::~CGameLevelDlg()
{
}

void CGameLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameLevelDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SIM, &CGameLevelDlg::OnBnClickedButtonSim)
	ON_BN_CLICKED(IDC_BUTTON_MID, &CGameLevelDlg::OnBnClickedButtonMid)
	ON_BN_CLICKED(IDC_BUTTON_DIF, &CGameLevelDlg::OnBnClickedButtonDif)
END_MESSAGE_MAP()


// CGameLevelDlg ��Ϣ�������


void CGameLevelDlg::OnBnClickedButtonSim()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_gameCM->setMapSize(EASYMAPROW, EASYMAPCOL);
	EndDialog(0);
}


void CGameLevelDlg::OnBnClickedButtonMid()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_gameCM->setMapSize(MEDIUMMAPROW, MEDIUMMAPCOL);
	EndDialog(0);
}


void CGameLevelDlg::OnBnClickedButtonDif()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_gameCM->setMapSize(DIFFICULTMAPROW, DIFFICULTMAPCOL);
	EndDialog(0);
}
