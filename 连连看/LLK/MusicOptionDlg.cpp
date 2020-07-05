// MusicOptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "MusicOptionDlg.h"
#include "afxdialogex.h"


// CMusicOptionDlg �Ի���

IMPLEMENT_DYNAMIC(CMusicOptionDlg, CDialogEx)

CMusicOptionDlg::CMusicOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicOptionDlg::IDD, pParent)
	, m_bBgMusic(FALSE)
	, m_bSound(FALSE)
	, m_strMusicPath(_T(""))
	, m_nMusicType(FALSE)
{

}

CMusicOptionDlg::~CMusicOptionDlg()
{
}

void CMusicOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_BGMUSIC, m_bBgMusic);
	DDX_Check(pDX, IDC_CHECK_SOUND, m_bSound);
	DDX_Text(pDX, IDC_EDIT_MUSIC, m_strMusicPath);
	DDX_Radio(pDX, IDC_RADIO_DEFMUSIC, m_nMusicType);
}


BEGIN_MESSAGE_MAP(CMusicOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_BGMUSIC, &CMusicOptionDlg::OnBnClickedCheckBgmusic)
	ON_BN_CLICKED(IDC_CHECK_SOUND, &CMusicOptionDlg::OnBnClickedCheckSound)
	ON_BN_CLICKED(IDC_RADIO_DEFMUSIC, &CMusicOptionDlg::OnBnClickedRadioDefmusic)
	ON_BN_CLICKED(IDC_RADIO_MYMUSIC, &CMusicOptionDlg::OnBnClickedRadioMymusic)
	ON_BN_CLICKED(IDC_BTMUSIC_MP3LOC, &CMusicOptionDlg::OnBnClickedBtmusicMp3loc)
	ON_EN_CHANGE(IDC_EDIT_MUSIC, &CMusicOptionDlg::OnEnChangeEditMusic)
END_MESSAGE_MAP()


// CMusicOptionDlg ��Ϣ�������


void CMusicOptionDlg::OnBnClickedCheckBgmusic()
{
	m_bBgMusic = !m_bBgMusic;
	m_Config->setBgMusic(m_bBgMusic != FALSE);
}

void CMusicOptionDlg::OnBnClickedCheckSound()
{
	m_bSound = !m_bSound;
	m_Config->setSound(m_bSound != FALSE);
}

void CMusicOptionDlg::OnBnClickedRadioDefmusic()
{
	m_Config->setMusicStyle(IDC_RADIO_DEFMUSIC);
	m_Config->setMusicPath(DEFAULTMUSIC);
	GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(FALSE);
}

void CMusicOptionDlg::OnBnClickedRadioMymusic()
{
	m_Config->setMusicStyle(IDC_RADIO_MYMUSIC);
	GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(SW_SHOW);
	GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(SW_SHOW);
}

void CMusicOptionDlg::OnBnClickedBtmusicMp3loc()
{
	CFileDialog  fileMenu(TRUE, _T("*.mp3"), m_strMusicPath, OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{

		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strMusicPath.Format(_T("%s"), strRelPath);
		UpdateData(false);
		((CButton*)GetDlgItem(IDC_RADIO_DEFMUSIC))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_MYMUSIC))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(SW_SHOW);
		GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(SW_SHOW);

		m_Config->setMusicStyle(IDC_RADIO_MYMUSIC);
		m_Config->setMusicPath(m_strMusicPath);
	}
}

BOOL CMusicOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ChossStyle();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CMusicOptionDlg::setConfig(CConfig* pCg)
{
	m_Config = pCg;
}

void CMusicOptionDlg::ChossStyle()
{
	m_bBgMusic = m_Config->getBgMusic();
	m_bSound = m_Config->getSound();
	int style = m_Config->getMusicStyle();

	m_strMusicPath.Format(_T("%s"), m_Config->getMusicPath());
	UpdateData(FALSE);
	if (style == IDC_RADIO_MYMUSIC)
	{
		((CButton*)GetDlgItem(IDC_RADIO_DEFMUSIC))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_MYMUSIC))->SetCheck(TRUE);
		GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(SW_SHOW);
		GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(SW_SHOW);
	}		
}

void CMusicOptionDlg::OnEnChangeEditMusic()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(FALSE);
	m_Config->setMusicPath(m_strMusicPath);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
