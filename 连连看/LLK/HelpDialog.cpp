// HelpDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDialog.h"
#include "afxdialogex.h"
#include "CONSTANT.h"


// CHelpDialog �Ի���

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDialog::IDD, pParent)
{

}

CHelpDialog::CHelpDialog(int nModel, CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	gameModel = nModel;
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HELP_SCROLL, m_ScrollBar);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//��ʼ�������Ի���
BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetClientRect(&helpDlgRect);
	InitHelpPicture();//���ذ���ͼƬ
	InitSrcollBar();//���ع�����

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//����ͼƬ
void CHelpDialog::InitHelpPicture()
{
	HANDLE helpBmp;
	//���ļ��м���ͼƬ
	switch (gameModel)
	{
		case GAME_MAIN_FRAME:
			helpBmp = ::LoadImage(NULL, _T("source\\help\\mainFrame_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case GAME_MODEL_BASE:
			helpBmp = ::LoadImage(NULL, _T("source\\help\\base_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case GAME_MODEL_EASY:
			helpBmp = ::LoadImage(NULL, _T("source\\help\\easy_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		default:
			helpBmp = ::LoadImage(NULL, _T("source\\help\\blank_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); break;
	}
	//��ȡ��ǰ�豸����
	CClientDC cDC(this);
	//��������DC
	m_dcHelp.CreateCompatibleDC(&cDC);
	m_dcMem.CreateCompatibleDC(&cDC);
	//λͼѡ���豸����
	m_dcHelp.SelectObject(helpBmp);
	//��ȡλͼ��Ϣ
	GetObject(helpBmp, sizeof(BITMAP), &bmpMes);

	//��ʼ�������ڴ�
	CBitmap bmpMem;
	bmpMem.CreateDiscardableBitmap(&cDC, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top);
	m_dcMem.SelectObject(&bmpMem);

	//���ư���ͼƬ��������
	m_dcMem.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcHelp, 0, 0, SRCCOPY);
}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = m_ScrollBar.GetScrollPos();
	switch (nSBCode)
	{
		case SB_LINEUP://������ϰ�ť
			pos--;
			break;
		case SB_LINEDOWN:
			pos++;
			break;
		case SB_PAGEUP:
			pos -= helpDlgRect.bottom - helpDlgRect.top;
			break;
		case SB_PAGEDOWN:
			pos += helpDlgRect.bottom - helpDlgRect.top;
			break;
		case SB_TOP:
			pos = 0;
			break;
		case SB_BOTTOM:
			pos = bmpMes.bmHeight - helpDlgRect.bottom + helpDlgRect.top;
			break;
		case SB_THUMBTRACK:
			pos = nPos;
			break;
		case SB_THUMBPOSITION:
			pos = nPos;
			break;
	}
	//���û���λ��
	m_ScrollBar.SetScrollPos(pos);
	//�ػ�ͼƬ
	updataHelpDlg();
	
	Invalidate(FALSE);
	m_ScrollBar.RedrawWindow(FALSE);//��ֹ�����ˢ��
	CDialogEx::OnVScroll(nSBCode, pos, pScrollBar);
}

//��ʼ��������
void CHelpDialog::InitSrcollBar()
{
	m_ScrollBar.SetScrollRange(0, bmpMes.bmHeight - helpDlgRect.bottom + helpDlgRect.top);
	m_ScrollBar.SetScrollPos(0);
}

void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcMem, 0, 0, SRCCOPY);
}

//���ݹ�����λ�� ���ư���ͼƬ
void CHelpDialog::updataHelpDlg()
{
	//��ǰ������λ��
	int nScrollPos = m_ScrollBar.GetScrollPos();

	//��ȡͼƬ���л���
	m_dcMem.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcHelp, 0, nScrollPos, SRCCOPY);
}

