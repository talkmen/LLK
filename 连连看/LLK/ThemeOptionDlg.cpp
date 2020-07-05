// ThemeOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "ThemeOptionDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "CONSTANT.h"

// CThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(CThemeOptionDlg, CDialogEx)

CThemeOptionDlg::CThemeOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThemeOptionDlg::IDD, pParent)
	, m_strMaskPath(_T(""))
	, m_strElemPath(_T(""))
	, m_nThemeType(0)
{

}

CThemeOptionDlg::CThemeOptionDlg(CConfig *pConfig, CWnd* pParent /*=NULL*/)
: CDialogEx(CThemeOptionDlg::IDD, pParent)
, m_strMaskPath(_T(""))
, m_strElemPath(_T(""))
, m_nThemeType(0)
{
	this->pConfig = pConfig;
}

CThemeOptionDlg::~CThemeOptionDlg()
{
}

void CThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASKPATH, m_strMaskPath);
	DDX_Text(pDX, IDC_EDIT_ELEMENTPATH, m_strElemPath);
	DDX_Radio(pDX, IDC_RADIO_SMILE, m_nThemeType);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTTHEME_ELEMENT, &CThemeOptionDlg::OnBnClickedBtthemeElement)
	ON_BN_CLICKED(IDC_BTTHEME_MASK, &CThemeOptionDlg::OnBnClickedBtthemeMask)
	ON_BN_CLICKED(IDC_RADIO_STAR, &CThemeOptionDlg::OnBnClickedRadioStar)
	ON_EN_CHANGE(IDC_EDIT_ELEMENTPATH, &CThemeOptionDlg::OnEnChangeEditElementpath)
	ON_EN_CHANGE(IDC_EDIT_MASKPATH, &CThemeOptionDlg::OnEnChangeEditMaskpath)
	ON_BN_CLICKED(IDC_RADIO_MYTHEME, &CThemeOptionDlg::OnBnClickedRadioMytheme)
	ON_BN_CLICKED(IDC_RADIO_SMILE, &CThemeOptionDlg::OnBnClickedRadioSmile)
END_MESSAGE_MAP()


// CThemeOptionDlg 消息处理程序

void CThemeOptionDlg::OnBnClickedBtthemeElement()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), m_strElemPath, OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{
		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strElemPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
		pConfig->setStrElemPath(m_strElemPath);
	}
}

void CThemeOptionDlg::OnBnClickedBtthemeMask()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), m_strMaskPath, OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{
		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strMaskPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
		pConfig->setStrMaskPath(m_strMaskPath);
	}
}

void CThemeOptionDlg::OnEnChangeEditElementpath()
{
	UpdateData(FALSE);
	pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
	pConfig->setStrElemPath(m_strElemPath);
}

void CThemeOptionDlg::OnEnChangeEditMaskpath()
{
	UpdateData(FALSE);
	pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
	pConfig->setStrMaskPath(m_strMaskPath);
}

BOOL CThemeOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_strElemPath.Format(_T("%s"), pConfig->getStrElemPath());
	m_strMaskPath.Format(_T("%s"), pConfig->getStrMaskPath());
	UpdateData(FALSE);
	ChossStyle();
	return TRUE;  
}

void CThemeOptionDlg::ChossStyle()
{
	((CButton*)GetDlgItem(IDC_RADIO_SMILE))->SetCheck(FALSE);
	int style = pConfig->getThemeStyle();
	switch (style)
	{
	case IDC_RADIO_STAR:
		((CButton*)GetDlgItem(IDC_RADIO_STAR))->SetCheck(TRUE);
		break;
	case IDC_RADIO_MYTHEME:
		((CButton*)GetDlgItem(IDC_RADIO_MYTHEME))->SetCheck(TRUE);
		GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(TRUE);
		break;
	default:
		((CButton*)GetDlgItem(IDC_RADIO_SMILE))->SetCheck(TRUE);
		break;
	}
}

void CThemeOptionDlg::setConfig(CConfig *pCg)
{
	pConfig = pCg;
}

void CThemeOptionDlg::OnBnClickedRadioMytheme()
{
	pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
	GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(TRUE);
}

void CThemeOptionDlg::OnBnClickedRadioStar()
{
	pConfig->setThemeStyle(IDC_RADIO_STAR);
	pConfig->setStrElemPath(DEFAULTELEMENT_STAR);
	pConfig->setStrMaskPath(DEFAULTMASK_STAR);
	GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(FALSE);
}

void CThemeOptionDlg::OnBnClickedRadioSmile()
{
	pConfig->setThemeStyle(IDC_RADIO_SMILE);
	pConfig->setStrElemPath(DEFAULTELEMENT_SMILE);
	pConfig->setStrMaskPath(DEFAULTMASK_SMILE);
	GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(FALSE);
}
