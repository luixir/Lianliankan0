
// LLKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "afxdialogex.h"
#include "GameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg dialog




CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_EASY, &CLLKDlg::OnClickedBtnEasy)
//	ON_BN_CLICKED(IDC_BTN_Game, &CLLKDlg::OnClickedBtnGame)
	ON_BN_CLICKED(IDC_BTN_RANK, &CLLKDlg::OnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CLLKDlg::OnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLLKDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CLLKDlg::OnClickedBtnLevel)
END_MESSAGE_MAP()


// CLLKDlg message handlers

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

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

	// Initialize background
	InitBackground();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		
		// Get client area size
		CRect rect;
		GetClientRect(&rect);

		// Create text font
		CFont font;
		if(!font.CreatePointFont(200, _T("Courier New")))
		{
			AfxMessageBox(_T("Error set font type!"));
			return;
		}

		// Select font type into dc
		CFont* oldFont;
		oldFont = dc.SelectObject(&font);

		// Create greeting text
		CString strWel = _T("Welcome to LLK-Game!");

		// Set text colour
		dc.SetTextColor(RGB(0, 0, 255));

		// Set background colour
		dc.SetBkColor(RGB(255, 255, 255));

		// Get text width and height
		CSize size;
		size = dc.GetTextExtent(strWel, strWel.GetLength());

		// Change the position of greeting text
		int xWel = (rect.Width() - size.cx)/2;
		int yWel = (rect.Height() - size.cy)/2;

		// Draw greeting text
		dc.TextOut(xWel, yWel, strWel);

		// Copy the  image drawn in memory bitmap to the screen  in one go
		dc.BitBlt(0, 0, 800, 600, &m_memDC, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground(void)
{
	// Get video memory for the current dialog box.
	CClientDC dc(this);
	
	// Load BMP image resource
	CBitmap bitmap;
	if(!bitmap.LoadBitmap(IDB_MAIN_BG))
	{
		AfxMessageBox(_T("Error loading bitmap, main background!"));
		return;
	}

	// Create a memory DC compatible with the client  video device DC.
	if (!m_memDC.CreateCompatibleDC(&dc))
	{
		AfxMessageBox(_T("Error create compatible dc, main background!"));
		return;
	}

	// Select bitmap resource into dc
	m_memDC.SelectObject(&bitmap);
}

void CLLKDlg::OnClickedBtnBasic()
{
	// TODO: Add your control notification handler code here
	// Hide the current window
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg;
	// Change the window
	dlg.DoModal();
	// Show the other window
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnEasy()
{
	// TODO: Add your control notification handler code here
}


//void CLLKDlg::OnClickedBtnGame()
//{
//	// TODO: Add your control notification handler code here
//}


void CLLKDlg::OnClickedBtnRank()
{
	// TODO: Add your control notification handler code here
}


void CLLKDlg::OnClickedBtnSetting()
{
	// TODO: Add your control notification handler code here
}


void CLLKDlg::OnClickedBtnHelp()
{
	// TODO: Add your control notification handler code here
}


void CLLKDlg::OnClickedBtnLevel()
{
	// TODO: Add your control notification handler code here
}
