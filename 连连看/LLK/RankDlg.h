#pragma once
#include "afxcmn.h"


// CRankDlg �Ի���

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRankDlg();
// �Ի�������
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void DisplayRank(int nModel);//չʾ���а�
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRank;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioBase();
	afx_msg void OnBnClickedRadioEasy();
};
