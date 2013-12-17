// GameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

	// set element size
	nElemW = 40;
	nElemH = 40;

	// Set top point
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	// set end point
	m_ptGameEnd.x = 210;
	m_ptGameEnd.y = 210;

	m_rtGameRect.SetRect(m_ptGameTop, m_ptGameEnd);
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnClickedBtnPause)
END_MESSAGE_MAP()


// CGameDlg message handlers


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize background
	InitBackground();

	// Initialize Element
	InitElement();

	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	// Draw background image
	dc.BitBlt(0, 0, 800, 600, &m_memDC, 0, 0, SRCCOPY);
}


void CGameDlg::InitBackground(void)
{
	// Get video memory for the current dialog box.
	CClientDC dc(this);
	
	// Load BMP image resource
	HANDLE hBitmap = ::LoadImageW(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(!hBitmap)
	{
		AfxMessageBox(_T("Error loading bitmap, background!"));
		return;
	}
	

	if(!m_dcBK.CreateCompatibleDC(&dc))
	{
		AfxMessageBox(_T("Error create compatible dc, background!"));
		return;
	}
	m_dcBK.SelectObject(hBitmap);


	// Create a memory DC compatible with the client  video device DC.
	if (!m_memDC.CreateCompatibleDC(&dc))
	{
		AfxMessageBox(_T("Error create compatible dc, background!"));
		return;
	}

	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	// Select bitmap resource into memory dc
	m_memDC.SelectObject(&bmpMem);

	m_memDC.BitBlt(0, 0, 800, 600, &m_dcBK, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement(void)
{
	// Get video memory for the current dialog box.
	CClientDC dc(this);

	HANDLE hEBitmap = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(!hEBitmap)
	{
		AfxMessageBox(_T("Error loading bitmap, fruit element!"));
		return;
	}
	// Create a memory DC compatible with the client  video device DC.
	if (!m_dcElement.CreateCompatibleDC(&dc))
	{
		AfxMessageBox(_T("Error create compatible dc, fruit element!"));
		return;
	}

	// Select bitmap resource into dc
	m_dcElement.SelectObject(hEBitmap);

	HANDLE hMBitmap = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(!hMBitmap)
	{
		AfxMessageBox(_T("Error loading bitmap, fruit mask!"));
		return;
	}
	// Create a memory DC compatible with the client  video device DC.
	if (!m_dcMask.CreateCompatibleDC(&dc))
	{
		AfxMessageBox(_T("Error create compatible dc, fruit mask!"));
		return;
	}

	// Select bitmap resource into dc
	m_dcMask.SelectObject(hMBitmap);

}

void CGameDlg::UpdateWindow()
{
	// Adjust window size
	CRect rtWin;
	CRect rtClient;
	this -> GetWindowRect(rtWin);			// Get window size
	this -> GetClientRect(rtClient);		// Get client area size
	
	// Size of title bar & outer frame size
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	// Set window size
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	// Align window in centre
	CenterWindow();
}

void CGameDlg::UpdateMap(void)
{
	// Draw image
	m_memDC.BitBlt(0, 0, 800, 600, &m_dcBK, 0, 0, SRCCOPY);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Execute OR to the background & mask image
			m_memDC.BitBlt (m_ptGameTop.y + j * nElemW, m_ptGameTop.x + i * nElemH, nElemW, nElemH, 
				&m_dcMask, 0, m_GameC.GetElement(i,j) * nElemH, SRCPAINT);
			// Execute AND to  And element image
			m_memDC.BitBlt (m_ptGameTop.y + j * nElemW, m_ptGameTop.x + i * nElemH, nElemW, nElemH, 
				&m_dcElement, 0, m_GameC.GetElement(i,j) * nElemH, SRCAND);
		}
	}
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::OnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	m_bPlay = true;
	m_GameC.StartGame();
	UpdateMap();
	m_GameProgress.SetRange(0, 300);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(300);
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (point.y < m_ptGameTop.y || point.x < m_ptGameTop.x)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else
	{
		int nRow = (point.y - m_ptGameTop.y)/nElemH;
		int nCol = (point.x - m_ptGameTop.x)/nElemW;
		if ( nRow < 4 && nRow >= 0 && nCol < 4 && nCol >= 0 && m_GameC.GetElement(nRow,nCol) != BLANK)
		{
			DrawTipFrame (nRow,nCol);
			if (m_bFirstPoint)
			{
				m_GameC.SetFirstPoint(nRow, nCol);
				m_bFirstPoint = false;
			}
			else
			{
				m_GameC.SetSecPoint(nRow, nCol);
				Vertex avPath[4];
				int nVexNum;
				m_bFirstPoint = true;
				if (m_GameC.Link(avPath, nVexNum))
				{
					// Draw tip line
					DrawTipLine(avPath, nVexNum);
				}
				Sleep(200);
				UpdateMap();
				InvalidateRect(m_rtGameRect, FALSE);
			}
		}
	}
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CDC* pDC = GetDC();
	CBrush brush(RGB(233,43,43));
	RECT rect = {nCol*40+50, nRow*40+50, (nCol+1)*40+50, (nRow+1)*40+50};
	pDC->SelectObject(&brush);
	pDC->FrameRect(&rect, &brush);
	ReleaseDC(pDC);
}

void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexNum)
{
	// Get DC
	CDC *pDC = GetDC();
	// Set pen
	CPen pen(PS_SOLID, 2, RGB(0, 255, 0));
	// Insert pen into DC
	pDC->SelectObject(&pen);

	for (int i = nVexNum - 1; i > 0; i--)
	{
		pDC->MoveTo(70+(asvPath[i].col*40), 70+(asvPath[i].row*40));
		pDC->LineTo(70+(asvPath[i-1].col*40), 70+(asvPath[i-1].row*40));
	}
	pDC->SelectObject(pen);
	ReleaseDC(pDC);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//if (nIDEvent ==  PLAY_TIMER_ID && m_bPlay && m_bPause == false)
	//{
		m_GameProgress.StepIt();
	//}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnClickedBtnPause()
{
	// TODO: Add your control notification handler code here
	m_bPause = true;
}
