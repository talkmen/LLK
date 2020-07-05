#pragma once
#include "afxcmn.h"
#include "Config.h"
#include "ThemeOptionDlg.h"
#include "BKOptionDlg.h"
#include "MusicOptionDlg.h"
// CSettingDlg �Ի���

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();
	CSettingDlg(CConfig* config, CWnd* pParent = NULL);
// �Ի�������
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CConfig *pConfig;
	CThemeOptionDlg m_dlgTheme;//�������öԻ���
	CBKOptionDlg m_dlgBK;//�������öԻ���
	CMusicOptionDlg m_dlgMusic;//��Ч���öԻ���
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CTabCtrl m_tabSetting;
};
