// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "SettingDlg.h"
#include "afxdialogex.h"

// CSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::CSettingDlg(CConfig* config, CWnd* pParent /*=NULL*/)
: CDialogEx(CSettingDlg::IDD, pParent)
{
	this->pConfig = config;
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &CSettingDlg::OnTcnSelchangeTabSetting)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSettingDlg ��Ϣ�������


void CSettingDlg::OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	switch (m_tabSetting.GetCurSel())
	{
		case 0:
			m_dlgTheme.ShowWindow(SW_SHOW);
			m_dlgBK.ShowWindow(SW_HIDE);
			m_dlgMusic.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_dlgTheme.ShowWindow(SW_HIDE);
			m_dlgBK.ShowWindow(SW_SHOW);
			m_dlgMusic.ShowWindow(SW_HIDE);
			break;
		case 2:
			m_dlgTheme.ShowWindow(SW_HIDE);
			m_dlgBK.ShowWindow(SW_HIDE);
			m_dlgMusic.ShowWindow(SW_SHOW);
			break;
		default:
			break;
	}
}


void CSettingDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CSettingDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tabSetting.InsertItem(0, _T("��������"));
	m_tabSetting.InsertItem(1, _T("��������"));
	m_tabSetting.InsertItem(2, _T("��Ч����"));
	//������Tabҳ
	m_dlgTheme.setConfig(pConfig);
	m_dlgTheme.Create(IDD_CONFIG_THEME, &m_tabSetting);
	m_dlgBK.setConfig(pConfig);
	m_dlgBK.Create(IDD_CONFIG_BK, &m_tabSetting);
	m_dlgMusic.setConfig(pConfig);
	m_dlgMusic.Create(IDD_CONFIG_MUSIC, &m_tabSetting);


	//��ȡ����ʼ����ʾλ��
	CRect dlgRect;
	m_tabSetting.GetClientRect(&dlgRect);

	dlgRect.top += 30;
	dlgRect.left += 1;
	dlgRect.right -= 1;
	//������ʾλ��
	m_dlgTheme.MoveWindow(dlgRect);
	m_dlgBK.MoveWindow(dlgRect);
	m_dlgMusic.MoveWindow(dlgRect);
	//���ñ�ǩҳ0Ϊ��ʾ
	m_dlgTheme.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
