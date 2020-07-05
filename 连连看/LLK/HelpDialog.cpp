// HelpDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDialog.h"
#include "afxdialogex.h"
#include "CONSTANT.h"


// CHelpDialog 对话框

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

//初始化帮助对话框
BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetClientRect(&helpDlgRect);
	InitHelpPicture();//加载帮助图片
	InitSrcollBar();//加载滚动条

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//加载图片
void CHelpDialog::InitHelpPicture()
{
	HANDLE helpBmp;
	//从文件中加载图片
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
	//获取当前设备环境
	CClientDC cDC(this);
	//创建兼容DC
	m_dcHelp.CreateCompatibleDC(&cDC);
	m_dcMem.CreateCompatibleDC(&cDC);
	//位图选入设备环境
	m_dcHelp.SelectObject(helpBmp);
	//获取位图信息
	GetObject(helpBmp, sizeof(BITMAP), &bmpMes);

	//初始化缓冲内存
	CBitmap bmpMem;
	bmpMem.CreateDiscardableBitmap(&cDC, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top);
	m_dcMem.SelectObject(&bmpMem);

	//绘制帮助图片到缓冲区
	m_dcMem.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcHelp, 0, 0, SRCCOPY);
}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int pos = m_ScrollBar.GetScrollPos();
	switch (nSBCode)
	{
		case SB_LINEUP://点击向上按钮
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
	//设置滑块位置
	m_ScrollBar.SetScrollPos(pos);
	//重绘图片
	updataHelpDlg();
	
	Invalidate(FALSE);
	m_ScrollBar.RedrawWindow(FALSE);//禁止滑块的刷新
	CDialogEx::OnVScroll(nSBCode, pos, pScrollBar);
}

//初始化滚动条
void CHelpDialog::InitSrcollBar()
{
	m_ScrollBar.SetScrollRange(0, bmpMes.bmHeight - helpDlgRect.bottom + helpDlgRect.top);
	m_ScrollBar.SetScrollPos(0);
}

void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcMem, 0, 0, SRCCOPY);
}

//根据滚动条位置 绘制帮助图片
void CHelpDialog::updataHelpDlg()
{
	//当前滚动条位置
	int nScrollPos = m_ScrollBar.GetScrollPos();

	//截取图片进行绘制
	m_dcMem.BitBlt(0, 0, helpDlgRect.right - helpDlgRect.left, helpDlgRect.bottom - helpDlgRect.top, &m_dcHelp, 0, nScrollPos, SRCCOPY);
}

