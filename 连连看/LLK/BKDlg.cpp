// BKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "BKDlg.h"
#include "afxdialogex.h"
#include "CONSTANT.h"
#include "Resource.h"
// CBKDlg 对话框

IMPLEMENT_DYNAMIC(CBKDlg, CDialogEx)

CBKDlg::CBKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBKDlg::IDD, pParent)
	, m_strBGPPath(_T(""))
{

}

CBKDlg::CBKDlg(CConfig *config ,CWnd* pParent /*=NULL*/)
: CDialogEx(CBKDlg::IDD, pParent)
, m_strBGPPath(_T(""))
{
	m_Config = config;
}

CBKDlg::~CBKDlg()
{
}

void CBKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PIC, m_strBGPPath);
}


BEGIN_MESSAGE_MAP(CBKDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PIC, &CBKDlg::OnEnChangeEditPic)
	ON_BN_CLICKED(IDC_RADIO_FOREST, &CBKDlg::OnBnClickedRadioForest)
	ON_BN_CLICKED(IDC_RADIO_SEA, &CBKDlg::OnBnClickedRadioSea)
	ON_BN_CLICKED(IDC_RADIO_MYBK, &CBKDlg::OnBnClickedRadioMybk)
	ON_BN_CLICKED(IDC_BTBK_PICLOC, &CBKDlg::OnBnClickedBtbkPicloc)
END_MESSAGE_MAP()


// CBKDlg 消息处理程序
void CBKDlg::ChossStyle()
{
	((CButton*)GetDlgItem(IDC_RADIO_SEA))->SetCheck(FALSE);
	int style = m_Config->getBGPStyle();
	switch (style)
	{
	case IDC_RADIO_FOREST:
		((CButton*)GetDlgItem(IDC_RADIO_FOREST))->SetCheck(TRUE);
		break;
	case IDC_RADIO_MYBK:
		((CButton*)GetDlgItem(IDC_RADIO_MYBK))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_RADIO_SMILE))->SetCheck(TRUE);
		break;
	}
}

BOOL CBKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strBGPPath.Format(_T("%s"), m_Config->getStrBGPPath());
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化
	ChossStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBKDlg::OnEnChangeEditPic()
{
	UpdateData(FALSE);
	m_Config->setBGPStyle(IDC_RADIO_MYBK);
	m_Config->setStrBGPPath(m_strBGPPath);
}

void CBKDlg::OnBnClickedRadioForest()
{
	m_Config->setBGPStyle(IDC_RADIO_FOREST);
	m_Config->setStrBGPPath(DEFAULTBG_FOREST);
}


void CBKDlg::OnBnClickedRadioSea()
{
	m_Config->setBGPStyle(IDC_RADIO_SEA);
	m_Config->setStrBGPPath(DEFAULTBG_SEA);
}


void CBKDlg::OnBnClickedRadioMybk()
{
	m_Config->setBGPStyle(IDC_RADIO_MYBK);
	GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
}


void CBKDlg::OnBnClickedBtbkPicloc()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{

		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strBGPPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		m_Config->setBGPStyle(IDC_RADIO_MYBK);
		m_Config->setStrBGPPath(m_strBGPPath);
	}
}

void CBKDlg::setConfig(CConfig* pCg)
{
	m_Config = pCg;
}
