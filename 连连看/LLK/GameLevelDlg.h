#pragma once
#include "GameControl.h"

// CGameLevelDlg �Ի���

class CGameLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLevelDlg)

public:
	CGameLevelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CGameLevelDlg(CGameControl *m_gameCM, CWnd* pParent = NULL);
	virtual ~CGameLevelDlg();

// �Ի�������
	enum { IDD = IDD_GAME_LEVEL };

private:
	CGameControl *m_gameCM;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSim();
	afx_msg void OnBnClickedButtonMid();
	afx_msg void OnBnClickedButtonDif();
};
