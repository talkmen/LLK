// BaseGameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "BaseGameDlg.h"
#include "afxdialogex.h"

// CBaseGameDlg �Ի���

IMPLEMENT_DYNAMIC(CBaseGameDlg, CDialogEx)

CBaseGameDlg::CBaseGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = 50;
	m_ptGame.y = 50;
	m_sizeElement.cx = 40;
	m_sizeElement.cy = 40;
	m_bFristPoint = true;
}

CBaseGameDlg::~CBaseGameDlg()
{
}

void CBaseGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CBaseGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CBaseGameDlg ��Ϣ�������

void CBaseGameDlg::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL,_T("source\\bmp\\����.bmp") , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��ȡ��ǰDC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);
	m_dcMem.SelectObject(bmp);
}

void CBaseGameDlg::updateGameMap()
{
	//���Ʊ���ͼƬ
	m_dcMem.BitBlt(0, 0, 1080, 675, &m_dcBG, 0, 0, SRCCOPY);
	//��ʼ����
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <4; j++)
		{
			//����˵��
			//ǰ�����������ƻ���λ�� ��һ��Ϊ����� �ڶ���Ϊ���϶�
			//Ȼ���������ƻ��Ƴ���ǰΪ����Ϊ��
			//���ƴӺδ�ȡ
			//�ٽ��ſ���ȡͼƬ��λ��
			//������ȡͼƬ�ķ�ʽ
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//��ڰ�ͼ��� �ڱ�������ʾͼƬ�İ�ɫ���� ��ȫ0 ��ȫ1
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask, m_anMap[i][j] * m_sizeElement.cx, 0, SRCPAINT);
			//��ԭͼ���� �ڱ���ͼ������ɫ����
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, m_anMap[i][j] * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

BOOL CBaseGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaseGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//����ϷԪ�ؼ��ص�������
void CBaseGameDlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC cDC(this);
	CString elementPath = _T("source//element//smile.bmp");
	CString maskPath = _T("source//element//smile_mask.bmp");
	//����BmpͼƬ��Դ �Լ�ͼƬ������Դ ����ȡ������ɫ
	HANDLE hBmpBG = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//���������ڴ�DC
	m_dcElement.CreateCompatibleDC(&cDC);
	m_dcMask.CreateCompatibleDC(&cDC);
	//��λͼ������ͼƬ���뵽DC
	m_dcElement.SelectObject(hBmpBG);
	m_dcMask.SelectObject(hBmpMask);
}

void CBaseGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CPaintDC dc(this); // device context for painting
		// TODO:  �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
		dc.BitBlt(0, 0, 1080, 675, &m_dcMem, 0, 0, SRCCOPY);
	}
}


void CBaseGameDlg::OnClickedButtonStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int map[4][4] = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		m_anMap[i][j] = map[i][j];
	
	//��ʼ����
	updateGameMap();
	Invalidate(FALSE);//���������� ��ԭ�л����Ͻ��и���
}


//Ϊ��Ϸ�е�Ԫ�ػ������
void CBaseGameDlg::drawTipFrame(int nRow, int nCol)
{
	CClientDC cDC(this);//��ȡ��ǰ��ƵDC

	CBrush brush(RGB(233, 43, 43));//������ˢ

	//ȷ�����ƾ���λ��
	CRect rtTipFrame;
	rtTipFrame.left = nCol*m_sizeElement.cx + m_ptGame.x;
	rtTipFrame.top = nRow*m_sizeElement.cy + m_ptGame.y;
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;

	//���ƾ���
	cDC.FrameRect(rtTipFrame, &brush);
}

bool CBaseGameDlg::isLink()
{
	
}

void CBaseGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x < m_ptGame.x || point.y < m_ptGame.y)
		return CDialogEx::OnLButtonUp(nFlags, point);
	
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//���ͼƬ�������е����±�
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//���ͼƬ�������е����±�

}
