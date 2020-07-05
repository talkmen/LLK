#pragma once

#include "global.h"
#include "GameControl.h"
#include "CONSTANT.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Config.h"
#include "BaseGame.h"
// GameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CGameDlg(CConfig *config, CWnd* pParent = NULL);
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_GAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon;	//ͼ��
	CDC m_dcMem;	//��Ƶ�ڴ�
	CDC m_dcBG;//����ͼDC
	CDC m_dcElement;//��ͼԪ��DC
	CDC m_dcMask;//����DC
	CDC m_dcPause;//��ͣ����

	bool m_Playing; //������Ϸ
	bool m_Pause; //��ͣ״̬
	CPoint m_ptGame;//��Ϸ����ʼλ��
	CSize m_sizeElement;//ͼƬ��С
	CRect m_gameRect;//��Ϸ���δ�С
	CString m_strCaption;//����

	Vertex m_mapSize;//��Ϸ��ͼ��С

	//���ֲ���
	bool m_BGPlaying;
	CString m_BGPath;

	CConfig  *m_Config;
	CBaseGame *m_gameCM;//��Ϸ������
	virtual void InitBackground();
	void InitElement();
	void updateGameMap();
	void drawTipFrame(int nRow, int nCol);
	void drawTipLine(int pNode[], int Vexnums);
	void initGameProgress();//��ʼ��������Դ
	void drawGameTime();//������Ϸʣ��ʱ��
	CString getGameOverMes(); //��ʽ��������
	void updateTheme();//��������
	void GameOver(); //������Ϸ
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonResort();
	afx_msg void OnClickedButtonTips();
	// ����������
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonPause();
	afx_msg void OnClickedButtonHelp();
	CStatic m_leastTime;
//	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnClose();

	afx_msg void OnBnClickedButtonLevel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonEnd();
};
