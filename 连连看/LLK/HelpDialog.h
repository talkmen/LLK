#pragma once
#include "afxwin.h"


// CHelpDialog �Ի���

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CHelpDialog(int nModel, CWnd* pParent = NULL);
	virtual ~CHelpDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//�Զ��岿��
;
private:
	CDC m_dcHelp;//����ͼƬ
	CDC m_dcMem;//�����ڴ�
	BITMAP bmpMes;//ͼƬ��Ϣ
	CRect helpDlgRect;//���������

	int gameModel;//�������ʶ

	void InitHelpPicture();//���ذ���ͼƬ
	void InitSrcollBar();//��ʼ����������Դ
	void updataHelpDlg();//���ݹ�����λ�ø��»���
public:
	CScrollBar m_ScrollBar;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};
