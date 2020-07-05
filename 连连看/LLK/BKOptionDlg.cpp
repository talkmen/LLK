// BKOptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "BKOptionDlg.h"
#include "afxdialogex.h"
#include "CONSTANT.h"


// CBKOptionDlg �Ի���

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


// CBKOptionDlg ��Ϣ�������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(FALSE);
	m_Config->setBGPStyle(IDC_RADIO_MYBK);
	m_Config->setStrBGPPath(m_strBGPPath);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CBKOptionDlg::OnBnClickedBtbkPicloc()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), m_strBGPPath, OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strBGPPath.Format(_T("%s"), m_Config->getStrBGPPath());
	UpdateData(FALSE);
	ChossStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CBKOptionDlg::setConfig(CConfig *pConfig)
{
	m_Config = pConfig;
}
