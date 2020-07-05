#pragma once
#include "afxcmn.h"


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRankDlg();
// 对话框数据
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void DisplayRank(int nModel);//展示排行榜
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRank;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioBase();
	afx_msg void OnBnClickedRadioEasy();
};
