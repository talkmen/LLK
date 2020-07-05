#pragma once
#include "afxwin.h"
#include "Config.h"

// CBKOptionDlg 对话框

class CBKOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBKOptionDlg)

public:
	CBKOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	CBKOptionDlg(CConfig *config, CWnd* pParent = NULL);   
	virtual ~CBKOptionDlg();

// 对话框数据
	enum { IDD = IDD_CONFIG_BK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CConfig *m_Config;
	DECLARE_MESSAGE_MAP()
	void ChossStyle();
public:
	afx_msg void OnBnClickedRadioSea();
	afx_msg void OnBnClickedRadioForest();
	afx_msg void OnBnClickedRadioMybk();
	afx_msg void OnEnChangeEditPic();
	afx_msg void OnBnClickedBtbkPicloc();
	
	virtual BOOL OnInitDialog();
	CString m_strBGPPath;

	void setConfig(CConfig *pConfig);
};
