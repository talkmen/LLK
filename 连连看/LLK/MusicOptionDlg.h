#pragma once
#include "afxwin.h"
#include "Config.h"
#include "CONSTANT.h"

// CMusicOptionDlg �Ի���

class CMusicOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicOptionDlg)

public:
	CMusicOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMusicOptionDlg();

// �Ի�������
	enum { IDD = IDD_CONFIG_MUSIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CConfig *m_Config;
	DECLARE_MESSAGE_MAP()
	void ChossStyle();
public:
	void setConfig(CConfig* pCg);
	afx_msg void OnBnClickedCheckBgmusic();
	afx_msg void OnBnClickedCheckSound();
	afx_msg void OnBnClickedRadioDefmusic();
	afx_msg void OnBnClickedRadioMymusic();
	afx_msg void OnBnClickedBtmusicMp3loc();
	BOOL m_bBgMusic;
	BOOL m_bSound;
	CString m_strMusicPath;
	BOOL m_nMusicType;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditMusic();
};
