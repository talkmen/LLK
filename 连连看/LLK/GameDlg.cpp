// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CONSTANT.h"
#include "HelpDialog.h"
#include "BaseGame.h"
#include "SettingDlg.h"
#include "GameLevelDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
// GameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_BGPlaying = false;
	m_gameCM = new CBaseGame();
}

CGameDlg::CGameDlg(CConfig *config, CWnd* pParent /*=NULL*/)
: CDialogEx(CGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BASEGAME);
	m_ptGame.x = STARTTOPLOC;
	m_ptGame.y = STARTLEFTLOC;
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_Playing = false;
	m_Pause = false;
	m_gameCM = new CBaseGame();
	m_Config = config;
	m_BGPlaying = m_Config->getBgMusic();
	m_BGPath.Format(L"%s", m_Config->getMusicPath());
}

CGameDlg::~CGameDlg()
{
	delete m_gameCM;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIME, m_GameProgress);
	DDX_Control(pDX, IDC_STATIC_TIME, m_leastTime);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESORT, &CGameDlg::OnBnClickedButtonResort)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CGameDlg::OnClickedButtonTips)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnClickedButtonHelp)

	ON_BN_CLICKED(IDC_BUTTON_SET, &CGameDlg::OnBnClickedButtonSet)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CGameDlg::OnBnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_END, &CGameDlg::OnBnClickedButtonEnd)
END_MESSAGE_MAP()

// GameDlg ��Ϣ�������
void CGameDlg::InitBackground()
{
	//����API��������λͼ
	CString cstrBGPPath = m_Config->getStrBGPPath();
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

//��ʼ��������
void CGameDlg::initGameProgress()
{
	//��������
	CFont f;
	f.CreatePointFont(150, _T("΢���ź�"), NULL);
	m_leastTime.SetFont(&f);
	int preTimeGrade = (int)sqrt((double)(m_mapSize.col - 2));
	int gameTime = (m_mapSize.row - 2)*(m_mapSize.col - 2) * preTimeGrade;
	//��ʼ������������
	m_GameProgress.SetRange(0, gameTime);
	//���ý���������
	m_GameProgress.SetStep(-1);
	//���ý�������ʼλ��
	m_GameProgress.SetPos(gameTime);

	//Ϊ��������Ӷ�ʱ��
	SetTimer(PLAY_TIMER_ID, 1000, NULL);//��ʱ��IDΪPLAY_TIMER_ID ���ʱ��1000ms �ص�����ΪϵͳĬ��
}

//������Ϸʣ��ʱ��
void CGameDlg::drawGameTime()
{
	CClientDC pDC(this);//��ȡ���ƻ���

	CFont timeFont;
	timeFont.CreatePointFont(200, _T("Microsoft Yahei"));//�߶ȼ�������ʽ
	CFont *oldFont;
	//������ѡ���豸����
	oldFont = pDC.SelectObject(&timeFont);
	//����������ɫ
	pDC.SetTextColor(RGB(255, 0, 0));
	pDC.SetBkMode(TRANSPARENT);
	//��ȡ�������λ��
	CRect textRect;
	(GetDlgItem(IDC_PROGRESS_TIME))->GetClientRect(&textRect);
	textRect.left = textRect.right;
	textRect.right += 60;
	//��������
	CString cstr;
	cstr.Format(L"%d s", m_GameProgress.GetPos());
	pDC.TextOut(textRect.left, textRect.top, cstr);
	//�����廹ԭ
	pDC.SelectObject(oldFont);
	//��������
	InvalidateRect(textRect, TRUE);
}

void CGameDlg::updateGameMap()
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

BOOL CGameDlg::OnInitDialog()
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
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����ϷԪ�ؼ��ص�������
void CGameDlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC cDC(this);
	CString elementPath = m_Config->getStrElemPath();
	CString maskPath = m_Config->getStrMaskPath();
	//CString elementPath = _T("source//element//star.bmp");
	//CString maskPath = _T("source//element//star_mask.bmp");
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

void CGameDlg::OnPaint()
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

void CGameDlg::OnClickedButtonStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_mapSize = m_gameCM->startGame();
	m_Playing = true;
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false); 
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(true);
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;
	//��ʼ����
	updateGameMap();

	//����ʱ��
	initGameProgress();

	Invalidate(FALSE);//���������� ��ԭ�л����Ͻ��и���
}

//Ϊ��Ϸ�е�Ԫ�ػ������
void CGameDlg::drawTipFrame(int nRow, int nCol)
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
void CGameDlg::drawTipLine(int pNode[], int Vexnums)
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

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
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
		//������Ϸ��ͼ
		updateGameMap();
		
		Sleep(200);
		//ʹ����ʾ������
		InvalidateRect(m_gameRect, FALSE);
		//��ʤ
		if (m_gameCM->JudgeWin(m_GameProgress.GetPos()) == GAME_SUCCESS)
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

void CGameDlg::OnBnClickedButtonResort()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_gameCM->ResortGame();
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
}

void CGameDlg::OnClickedButtonTips()
{
	int path[MAXMAPCOL * MAXMAPROW];
	int Vexnums;
	if (m_gameCM->getTips() == TIPS_GET)
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

		//������Ϸ��ͼ
		updateGameMap();

		Sleep(200);
		InvalidateRect(m_gameRect, FALSE);
	}
	else if (TIPS_NOTFIND)
	{
		KillTimer(PLAY_TIMER_ID);
		if (IDYES == MessageBox(_T("�޷���ͨ���Ƿ�����"), _T("��ʾ"), MB_YESNO))
		{
			m_gameCM->ResortGame();
			updateGameMap();
			InvalidateRect(m_gameRect, FALSE);
		}
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
	}
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_Pause)
	{
		if (nIDEvent == PLAY_TIMER_ID)
		{
			m_GameProgress.StepIt();
			CString  str;
			str.Format(L"ʣ��ʱ�䣺 %d s\n����Ϊ��%d", m_GameProgress.GetPos(), m_gameCM->getScore());
			m_leastTime.SetWindowText(str);
			if (GAME_LOSER == m_gameCM->JudgeWin(m_GameProgress.GetPos()))
				GameOver();
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::OnClickedButtonPause()
{
	m_Pause = !m_Pause;
	if (m_Pause)
	{
		KillTimer(PLAY_TIMER_ID);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("������Ϸ"));
		m_dcMem.BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(FALSE);
	}
	else
	{
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("��ͣ"));
		updateGameMap();
		Invalidate(FALSE);
	}
}

void CGameDlg::OnClickedButtonHelp()
{
	KillTimer(PLAY_TIMER_ID);
	CHelpDialog helpDialog(GAME_MODEL_BASE);
	helpDialog.DoModal();
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

CString CGameDlg::getGameOverMes()
{
	CString gameCal;
	gameCal.Format(_T("\t����ģʽ\n\t��Ϸ��ɣ���ϲ��������\n\t���յ÷�:%d\n\n\t�Ƿ񱣴�ɼ���\n"), m_gameCM->calScore(m_GameProgress.GetPos()));
	return gameCal;
}

void CGameDlg::OnBnClickedButtonSet()
{
	if (m_Playing)
		KillTimer(PLAY_TIMER_ID);
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
	if (m_Playing)	
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::updateTheme()
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

void CGameDlg::OnClose()
{
	CDialogEx::OnClose();
}

void CGameDlg::OnBnClickedButtonLevel()
{
	if (m_Playing)
		KillTimer(PLAY_TIMER_ID);
	CGameLevelDlg level(m_gameCM);
	level.DoModal();
	if(m_gameCM->getMapSize().row != m_mapSize.row)
		GameOver();
	else if(m_Playing)
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::GameOver()
{
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	KillTimer(PLAY_TIMER_ID);
	if (m_gameCM->JudgeWin(m_GameProgress.GetPos()) == GAME_SUCCESS)
	{
		if (IDYES == MessageBox(getGameOverMes(), _T("����"), MB_YESNO))
			m_gameCM->saveScore(m_gameCM->calScore(m_GameProgress.GetPos()), GAME_MODEL_BASE);	
	}
	else if (GAME_LOSER == m_gameCM->JudgeWin(m_GameProgress.GetPos()))
		MessageBox(_T("      ʱ�䵽����Ϸʧ�ܣ�����       "), _T("ʧ��"), NULL);
	CString str;
	str.Format(L" ");
	m_leastTime.SetWindowText(str);
	m_gameCM->doAfterGameOver();
	m_Playing = false;
	m_Pause = false;
	m_GameProgress.SetRange(0, 0);
	updateGameMap();
	InvalidateRect(m_gameRect, FALSE);
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_TIPS)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESORT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_END)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_LEVEL)->EnableWindow(false);
}

void CGameDlg::OnBnClickedButtonEnd()
{
	GameOver();
}
