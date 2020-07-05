#pragma once
#include "Config.h"

// CBKDlg 对话框

class CBKDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBKDlg)

public:
	CBKDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBKDlg(CConfig *config, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBKDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CConfig *m_Config;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strBGPPath;
	afx_msg void OnEnChangeEditPic();
	afx_msg void OnBnClickedRadioForest();
	afx_msg void OnBnClickedRadioSea();
	afx_msg void OnBnClickedRadioMybk();
	void setConfig(CConfig* pCg);
	afx_msg void OnBnClickedBtbkPicloc();
	void ChossStyle();
};
