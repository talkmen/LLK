#pragma once
#include "CONSTANT.h"
#include "global.h"
#include "GameControl.h"
#include "HelpDialog.h"
#include "EasyGame.h"
#include "afxwin.h"
#include "Config.h"
// CEasyGameDlg 对话框

class CEasyGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEasyGameDlg)

public:
	CEasyGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	CEasyGameDlg(CConfig *config, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEasyGameDlg();

// 对话框数据
	enum { IDD = IDD_EASYGAME_DIALOG };

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

	CString m_StringText;
	CConfig *m_Config;
	CEasyGame *m_gameCM;//游戏控制器
	virtual void InitBackground();
	void InitElement();
	void updateGameMap();
	void drawTipFrame(int nRow, int nCol);
	void drawTipLine(int pNode[], int Vexnums);
	void initGameProgress();//初始进度条资源
	void drawGameTime();//绘制游戏剩余时间
	CString CEasyGameDlg::getScoreAndTool();//得到得分，道具数
	CString getGameOverMes(); //标准化结束语
	void CEasyGameDlg::updateTheme(); //更新主题
	void GameOver();
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonTips();
	afx_msg void OnClickedButtonPause();
	afx_msg void OnClickedButtonResort();
	afx_msg void OnClickedButtonSet();
	afx_msg void OnClickedButtonLevel();
	afx_msg void OnClickedButtonHelp();
	afx_msg void OnClickedButtonTool();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CStatic m_text;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonEnd();
};
