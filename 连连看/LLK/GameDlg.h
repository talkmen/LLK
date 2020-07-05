#pragma once

#include "global.h"
#include "GameControl.h"
#include "CONSTANT.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Config.h"
#include "BaseGame.h"
// GameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	CGameDlg(CConfig *config, CWnd* pParent = NULL);
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon;	//图标
	CDC m_dcMem;	//视频内存
	CDC m_dcBG;//背景图DC
	CDC m_dcElement;//地图元素DC
	CDC m_dcMask;//掩码DC
	CDC m_dcPause;//暂停画面

	bool m_Playing; //正在游戏
	bool m_Pause; //暂停状态
	CPoint m_ptGame;//游戏区域开始位置
	CSize m_sizeElement;//图片大小
	CRect m_gameRect;//游戏矩形大小
	CString m_strCaption;//类名

	Vertex m_mapSize;//游戏地图大小

	//音乐播放
	bool m_BGPlaying;
	CString m_BGPath;

	CConfig  *m_Config;
	CBaseGame *m_gameCM;//游戏控制器
	virtual void InitBackground();
	void InitElement();
	void updateGameMap();
	void drawTipFrame(int nRow, int nCol);
	void drawTipLine(int pNode[], int Vexnums);
	void initGameProgress();//初始进度条资源
	void drawGameTime();//绘制游戏剩余时间
	CString getGameOverMes(); //格式化结束语
	void updateTheme();//更新主题
	void GameOver(); //结束游戏
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonResort();
	afx_msg void OnClickedButtonTips();
	// 进度条控制
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
