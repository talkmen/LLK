#pragma once
#include "afxwin.h"


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // 标准构造函数
	CHelpDialog(int nModel, CWnd* pParent = NULL);
	virtual ~CHelpDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//自定义部分
;
private:
	CDC m_dcHelp;//帮助图片
	CDC m_dcMem;//缓存内存
	BITMAP bmpMes;//图片信息
	CRect helpDlgRect;//帮助框矩形

	int gameModel;//帮助框标识

	void InitHelpPicture();//加载帮助图片
	void InitSrcollBar();//初始化滚动条资源
	void updataHelpDlg();//根据滚动条位置更新画面
public:
	CScrollBar m_ScrollBar;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};
