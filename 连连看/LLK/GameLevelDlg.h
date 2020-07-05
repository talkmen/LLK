#pragma once
#include "GameControl.h"

// CGameLevelDlg 对话框

class CGameLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLevelDlg)

public:
	CGameLevelDlg(CWnd* pParent = NULL);   // 标准构造函数
	CGameLevelDlg(CGameControl *m_gameCM, CWnd* pParent = NULL);
	virtual ~CGameLevelDlg();

// 对话框数据
	enum { IDD = IDD_GAME_LEVEL };

private:
	CGameControl *m_gameCM;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSim();
	afx_msg void OnBnClickedButtonMid();
	afx_msg void OnBnClickedButtonDif();
};
