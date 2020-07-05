#pragma once
#include "CONSTANT.h"
#include "global.h"
#include "GameControl.h"
#include "HelpDialog.h"
#include "EasyGame.h"
#include "afxwin.h"
#include "Config.h"
// CEasyGameDlg �Ի���

class CEasyGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEasyGameDlg)

public:
	CEasyGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CEasyGameDlg(CConfig *config, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEasyGameDlg();

// �Ի�������
	enum { IDD = IDD_EASYGAME_DIALOG };

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

	CString m_StringText;
	CConfig *m_Config;
	CEasyGame *m_gameCM;//��Ϸ������
	virtual void InitBackground();
	void InitElement();
	void updateGameMap();
	void drawTipFrame(int nRow, int nCol);
	void drawTipLine(int pNode[], int Vexnums);
	void initGameProgress();//��ʼ��������Դ
	void drawGameTime();//������Ϸʣ��ʱ��
	CString CEasyGameDlg::getScoreAndTool();//�õ��÷֣�������
	CString getGameOverMes(); //��׼��������
	void CEasyGameDlg::updateTheme(); //��������
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
