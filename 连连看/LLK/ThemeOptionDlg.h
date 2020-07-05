#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Config.h"

// CThemeOptionDlg 对话框

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	CThemeOptionDlg(CConfig* pConfig, CWnd* pParent = NULL);
	virtual ~CThemeOptionDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_THEME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void ChossStyle(); //
	DECLARE_MESSAGE_MAP()
protected:
	CConfig *pConfig;
public:
	void setConfig(CConfig *pCg);
	afx_msg void OnBnClickedBtthemeElement();
	afx_msg void OnBnClickedBtthemeMask();
	afx_msg void OnBnClickedRadioStar();
	afx_msg void OnEnChangeEditElementpath();
	afx_msg void OnEnChangeEditMaskpath();
	virtual BOOL OnInitDialog();
	CString m_strMaskPath;
	CString m_strElemPath;
	int m_nThemeType;
	afx_msg void OnBnClickedRadioMytheme();
	afx_msg void OnBnClickedRadioSmile();
};
