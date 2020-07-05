
// LLKDlg.h : ͷ�ļ�
//

#pragma once
#include "Config.h"
// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//�û��Զ�������Լ����������ڴ˴�
protected:
	CDC m_dcMem;//λͼ�ڴ�
	void InitBackground();//����λͼ
	CConfig *m_Config;

	//���ֲ���
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
