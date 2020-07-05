// BKOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "BKOptionDlg.h"
#include "afxdialogex.h"
#include "CONSTANT.h"


// CBKOptionDlg 对话框

IMPLEMENT_DYNAMIC(CBKOptionDlg, CDialogEx)

CBKOptionDlg::CBKOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBKOptionDlg::IDD, pParent)
	, m_strBGPPath(_T(""))
{

}

CBKOptionDlg::CBKOptionDlg(CConfig *config, CWnd* pParent /*=NULL*/)
: CDialogEx(CBKOptionDlg::IDD, pParent)
{
	m_Config = config;
}

CBKOptionDlg::~CBKOptionDlg()
{
}

void CBKOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PIC, m_strBGPPath);
}


BEGIN_MESSAGE_MAP(CBKOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_SEA, &CBKOptionDlg::OnBnClickedRadioSea)
	ON_BN_CLICKED(IDC_RADIO_FOREST, &CBKOptionDlg::OnBnClickedRadioForest)
	ON_BN_CLICKED(IDC_RADIO_MYBK, &CBKOptionDlg::OnBnClickedRadioMybk)
	ON_EN_CHANGE(IDC_EDIT_PIC, &CBKOptionDlg::OnEnChangeEditPic)
	ON_BN_CLICKED(IDC_BTBK_PICLOC, &CBKOptionDlg::OnBnClickedBtbkPicloc)
END_MESSAGE_MAP()


// CBKOptionDlg 消息处理程序
void CBKOptionDlg::ChossStyle()
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
			((CButton*)GetDlgItem(IDC_RADIO_SEA))->SetCheck(TRUE);
			break;
	}
}

void CBKOptionDlg::OnBnClickedRadioSea()
{
	m_Config->setBGPStyle(IDC_RADIO_SEA);
	m_Config->setStrBGPPath(DEFAULTBG_SEA);
	GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PIC)->EnableWindow(FALSE);
}


void CBKOptionDlg::OnBnClickedRadioForest()
{
	m_Config->setBGPStyle(IDC_RADIO_FOREST);
	m_Config->setStrBGPPath(DEFAULTBG_FOREST);
	GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PIC)->EnableWindow(FALSE);
}


void CBKOptionDlg::OnBnClickedRadioMybk()
{
	m_Config->setBGPStyle(IDC_RADIO_MYBK);
	GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
}


void CBKOptionDlg::OnEnChangeEditPic()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(FALSE);
	m_Config->setBGPStyle(IDC_RADIO_MYBK);
	m_Config->setStrBGPPath(m_strBGPPath);
	// TODO:  在此添加控件通知处理程序代码
}


void CBKOptionDlg::OnBnClickedBtbkPicloc()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), m_strBGPPath, OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
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


BOOL CBKOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strBGPPath.Format(_T("%s"), m_Config->getStrBGPPath());
	UpdateData(FALSE);
	ChossStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CBKOptionDlg::setConfig(CConfig *pConfig)
{
	m_Config = pConfig;
}
