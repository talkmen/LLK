#pragma once
#include "Config.h"

// CBKDlg �Ի���

class CBKDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBKDlg)

public:
	CBKDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CBKDlg(CConfig *config, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBKDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CConfig *m_Config;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strBGPPath;
	afx_msg void OnEnChangeEditPic();
	afx_msg void OnBnClickedRadioForest();
	afx_msg void OnBnClickedRadioSea();
	afx_msg void OnBnClickedRadioMybk();
	void setConfig(CConfig* pCg);
	afx_msg void OnBnClickedBtbkPicloc();
	void ChossStyle();
};
