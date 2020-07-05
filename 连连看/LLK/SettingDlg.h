#pragma once
#include "afxcmn.h"
#include "Config.h"
#include "ThemeOptionDlg.h"
#include "BKOptionDlg.h"
#include "MusicOptionDlg.h"
// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();
	CSettingDlg(CConfig* config, CWnd* pParent = NULL);
// 对话框数据
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CConfig *pConfig;
	CThemeOptionDlg m_dlgTheme;//主题设置对话框
	CBKOptionDlg m_dlgBK;//背景设置对话框
	CMusicOptionDlg m_dlgMusic;//音效设置对话框
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CTabCtrl m_tabSetting;
};
