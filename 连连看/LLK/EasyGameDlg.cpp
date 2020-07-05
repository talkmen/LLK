// EasyGameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "EasyGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SettingDlg.h"
#include "GameLevelDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// CEasyGameDlg �Ի���

IMPLEMENT_DYNAMIC(CEasyGameDlg, CDialogEx)

CEasyGameDlg::CEasyGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEasyGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CEasyGame();
}

CEasyGameDlg::CEasyGameDlg(CConfig *config, CWnd* pParent /*=NULL*/)
: CDialogEx(CEasyGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CEasyGame();
	m_Config = config;
	m_BGPlaying = m_Config->getBgMusic();
	m_BGPath.Format(L"%s", m_Config->getMusicPath());
}

CEasyGameDlg::~CEasyGameDlg()
{
	delete m_gameCM;
}

void CEasyGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_DES, m_text);
}

BEGIN_MESSAGE_MAP(CEasyGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CEasyGameDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CEasyGameDlg::OnClickedButtonTips)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CEasyGameDlg::OnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_RESORT, &CEasyGameDlg::OnClickedButtonResort)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CEasyGameDlg::OnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CEasyGameDlg::OnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CEasyGameDlg::OnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_TOOL, &CEasyGameDlg::OnClickedButtonTool)
	ON_BN_CLICKED(IDC_BUTTON_END, &CEasyGameDlg::OnBnClickedButtonEnd)
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEasyGameDlg ��Ϣ�������

// GameDlg ��Ϣ�������
void CEasyGameDlg::InitBackground()
{
	//����API��������λͼ
	CString cstrBGPPath = m_Config->getStrBGPPath();
	//CString cstrBGPPath = _T("source\\bmp\\����.bmp");
	HANDLE bmp = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpPause = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��ȡ��ǰDC
	CClientDC clientDC(this);
	//�����뵱ǰ�ڴ���ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&clientDC);
	m_dcPause.CreateCompatibleDC(&clientDC);
	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(bmp);
	m_dcPause.SelectObject(bmpPause);

	//��ʼ����Ƶ�ڴ�DC
	m_dcMem.CreateCompatibleDC(&clientDC);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&clientDC, GAME_WIDTH, GAME_HEIGHT);
	m_dcMem.SelectObject(&bmpMem);
	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
}

void CEasyGameDlg::updateGameMap()
{
	//���Ʊ���ͼƬ
	m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcBG, 0, 0, SRCCOPY);
	//��ʼ����
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j < m_mapSize.col; j++)
		{
			//����˵��
			//ǰ�����������ƻ���λ�� ��һ��Ϊ����� �ڶ���Ϊ���϶�
			//Ȼ���������ƻ��Ƴ���ǰΪ����Ϊ��
			//���ƴӺδ�ȡ
			//�ٽ��ſ���ȡͼƬ��λ��
			//������ȡͼƬ�ķ�ʽ
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//��ڰ�ͼ��� �ڱ�������ʾͼƬ�İ�ɫ���� ��ȫ0 ��ȫ1
			int value = m_gameCM->getElement(i, j);
			if (value == BLANK)	continue;
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask, value * m_sizeElement.cx, 0, SRCPAINT);
			//��ԭͼ���� �ڱ���ͼ������ɫ����
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, value * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

void CEasyGameDlg::OnPaint()
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
		dc.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
	}
}

void CEasyGameDlg::OnClickedButtonStart()
{
	CFont f;
	f.CreatePointFont(150, _T("΢���ź�"), NULL);
	m_text.SetFont(&f);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_mapSize = m_gameCM->startGame();
	m_Playing = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(true);
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;
	//��ʼ����
	updateGameMap();
	getScoreAndTool();
	m_text.SetWindowText(m_StringText);
	Invalidate(FALSE);//���������� ��ԭ�л����Ͻ��и���

}

CString CEasyGameDlg::getScoreAndTool()
{
	m_StringText.Format(L"����Ϊ��%d \n������Ϊ��%d", m_gameCM->getScore(), m_gameCM->getTool());
	return m_StringText;
}

void CEasyGameDlg::OnClickedButtonTips()
{
	int path[MAXMAPCOL * MAXMAPROW];
	int Vexnums;
	int result = m_gameCM->getTips();
	getScoreAndTool();
	m_text.SetWindowText(m_StringText);
	if (result  == TIPS_GET)
	{
		Vexnums = m_gameCM->getPath(path);
		int index1 = path[0];
		int index2 = path[Vexnums - 1];
		int row = index1 / m_mapSize.col;
		int col = index1 % m_mapSize.col;
		drawTipFrame(row, col);//���ƾ��ο�
		row = index2 / m_mapSize.col;
		col = index2 % m_mapSize.col;
		drawTipFrame(row, col);//���ƾ��ο�
		drawTipLine(path, Vexnums);//��������
		
		Sleep(2000);
		InvalidateRect(m_gameRect, FALSE);
	}
	else if (result == TIPS_NOTFIND)
	{
		if (IDYES == MessageBox(_T("�޷���ͨ���Ƿ�����"), _T("��ʾ"), MB_YESNO))
		{
			m_gameCM->ResortGame(true);
			updateGameMap();
			InvalidateRect(m_gameRect, FALSE);
		}
	}
	else if (result == SCORENOTENOUGH)
		MessageBox(_T("      ���ֲ���      "), _T("��ʾ"));
}

void CEasyGameDlg::OnClickedButtonPause()
{
	m_Pause = !m_Pause;
	if (m_Pause)
	{
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("������Ϸ"));
		m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("��ͣ"));
		updateGameMap();
		Invalidate(FALSE);
	}
}

void CEasyGameDlg::OnClickedButtonResort()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int result = m_gameCM->ResortGame();
	if (result == SCORENOTENOUGH)
		MessageBox(_T("      ���ֲ���      "), _T("��ʾ"));
	else if (result == SUCCESS)
	{
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);
		updateGameMap();
		InvalidateRect(m_gameRect, FALSE);
	}	
}

void CEasyGameDlg::OnClickedButtonSet()
{
	m_Config->Load();
	CSettingDlg settingDlg(m_Config);
	if (IDOK == settingDlg.DoModal())
	{
		m_Config->Save();
		updateTheme();
		CString str = m_Config->getMusicPath();
		CString temp;
		if (!m_BGPath.CompareNoCase(str))
		{
			if (m_Config->getBgMusic() && !m_BGPlaying)
			{
				temp.Format(L"play %s repeat", str);
				mciSendString(temp, 0, 0, 0);
				m_BGPlaying = !m_BGPlaying;
			}
			else if (!m_Config->getBgMusic() && m_BGPlaying)
			{
				temp.Format(L"stop %s", str);
				mciSendString(temp, 0, 0, 0);
				m_BGPlaying = !m_BGPlaying;
			}
		}
		else if (m_Config->getBgMusic())
		{
			temp.Format(L"stop %s", m_BGPath);
			mciSendString(temp, 0, 0, 0);
			m_BGPath.Format(L"%s", str);

			temp.Format(L"play %s repeat", str);
			mciSendString(temp, 0, 0, 0);
			m_BGPlaying = true;
		}
		else
		{
			temp.Format(L"stop %s", m_BGPath);
			mciSendString(temp, 0, 0, 0);
			m_BGPath.Format(L"%s", str);
			m_BGPlaying = false;
		}
	}
}

void CEasyGameDlg::OnClickedButtonLevel()
{
	CGameLevelDlg level(m_gameCM);
	level.DoModal();
	if (m_gameCM->getMapSize().row != m_mapSize.row)
		GameOver();
}

void CEasyGameDlg::OnClickedButtonHelp()
{
	CHelpDialog helpDialog(GAME_MODEL_EASY);
	helpDialog.DoModal();
}

void CEasyGameDlg::OnClickedButtonTool()
{
	if (!m_gameCM->setUse())
		MessageBox(_T("���߲���"), _T("��ʾ"));
	else
	{
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);
	}
}

BOOL CEasyGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEasyGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����ϷԪ�ؼ��ص�������
void CEasyGameDlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC cDC(this);
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	/*CString elementPath = _T("source//element//smile.bmp");
	CString maskPath = _T("source//element//smile_mask.bmp");*/
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

void CEasyGameDlg::updateTheme()
{
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	CString bgpPath = m_Config->getStrBGPPath();

	HANDLE hBmpElement = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpBgp = ::LoadImage(NULL, bgpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.SelectObject(hBmpElement);
	m_dcMask.SelectObject(hBmpMask);
	m_dcBG.SelectObject(hBmpBgp);
	m_dcPause.SelectObject(hBmpBgp);

	updateGameMap();
	Invalidate(FALSE);
}

//Ϊ��Ϸ�е�Ԫ�ػ������
void CEasyGameDlg::drawTipFrame(int nRow, int nCol)
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

//������ͼƬ���������
void CEasyGameDlg::drawTipLine(int pNode[], int Vexnums)
{
	//��ȡ��ǰDC
	CClientDC cDC(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//������ѡ��DC
	CPen* pOldPen = cDC.SelectObject(&penLine);

	int row = pNode[0] / m_mapSize.col;
	int col = pNode[0] % m_mapSize.col;
	int nStartX = m_ptGame.x + col*m_sizeElement.cx + m_sizeElement.cx / 2;
	int nStartY = m_ptGame.y + row*m_sizeElement.cy + m_sizeElement.cy / 2;
	//�������
	cDC.MoveTo(nStartX, nStartY);
	for (int i = 1; i < Vexnums; i++)
	{
		//��������
		row = pNode[i] / m_mapSize.col;
		col = pNode[i] % m_mapSize.col;
		nStartX = m_ptGame.x + col*m_sizeElement.cx + m_sizeElement.cx / 2;
		nStartY = m_ptGame.y + row*m_sizeElement.cy + m_sizeElement.cy / 2;

		//��������յ㻭��
		cDC.LineTo(nStartX, nStartY);
	}
	//��ԭ���ʷ���
	cDC.SelectObject(pOldPen);
}

void CEasyGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((point.x <= m_ptGame.x) || (point.y <= m_ptGame.y))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if ((point.x >= m_gameRect.right) || (point.y >= m_gameRect.bottom))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//���ͼƬ�������е����±�
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//���ͼƬ�������е����±�

	switch (m_gameCM->Link(nRow, nCol))
	{
	case SELECTBLANK:
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
		break;
	}
	case FIRSTSELECT:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		break;
	}
	case CLEARSELECT:
	{
		int path[MAXMAPROW * MAXMAPCOL];
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		int vexnum = m_gameCM->getPath(path);
		drawTipLine(path, vexnum);//��������
		m_gameCM->addScore();
		m_gameCM->updateTool(true);
		//������Ϸ��ͼ
		updateGameMap();

		Sleep(200);
		getScoreAndTool();
		m_text.SetWindowText(m_StringText);

		InvalidateRect(m_gameRect, FALSE);
		
		if (m_gameCM->JudgeWin() == GAME_SUCCESS)
			GameOver();
		break;
	}
	case RESELECT:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		InvalidateRect(m_gameRect, FALSE);
		break;
	}
	default:
		break;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

HBRUSH CEasyGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DES)
	{
		pDC->SetTextColor(RGB(255, 0, 0));   //����������ɫ
		pDC->SetBkMode(TRANSPARENT); //�������屳��Ϊ͸��
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);   // ���ñ���ɫ
	}
	else
		return hbr;
}

CString CEasyGameDlg::getGameOverMes()
{
	CString gameCal;
	gameCal.Format(_T("\t����ģʽ\n\t��Ϸ��ɣ���ϲ��������\n\t���յ÷�:%d\n\n\t�Ƿ񱣴�ɼ���\n"), m_gameCM->calScore());
	return gameCal;
}

void CEasyGameDlg::OnBnClickedButtonEnd()
{
	GameOver();
}

void CEasyGameDlg::GameOver()
{
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	if (m_gameCM->JudgeWin() == GAME_SUCCESS)
	{
		if (IDYES == MessageBox(getGameOverMes(), _T("����"), MB_YESNO))
			m_gameCM->saveScore(m_gameCM->calScore(), GAME_MODEL_EASY);
	}
	m_StringText.Format(L" ");
	m_text.SetWindowText(m_StringText);
	m_gameCM->doAfterGameOver();
	m_Playing = false;
	m_Pause = false;
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_TOOL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
}
