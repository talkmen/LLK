
// LLKDlg.h : 头文件
//

#pragma once
#include "Config.h"
// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//用户自定义的属性及方法定义在此处
protected:
	CDC m_dcMem;//位图内存
	void InitBackground();//加载位图
	CConfig *m_Config;

	//音乐播放
	bool m_BGPlaying;
	CString m_BGPath;
public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnBnClickedButtonCasual();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonRank();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonLevel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};
