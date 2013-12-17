#pragma once
#include "global.h"
#include "GameControl.h"
// CGameDlg dialog

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGameDlg();

// Dialog Data
	enum { IDD = IDD_GAME_DIALOG };

	// Function
	void UpdateWindow(void);
	void UpdateMap(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	// Attribute
	HICON m_hIcon;
	CDC m_memDC;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcBK;
	bool m_bFirstPoint;		// Check if it is the first selected photo
	Vertex m_ptSelFirst;	// The first selected point (x for column, y for row)
	Vertex m_ptSelSec;		// The second selected point (x for column, y for row)
	CPoint m_ptGameTop;		// Start point of the game zone, coordinate of vertex on the first game map, relative to client area
	CPoint m_ptGameEnd;
	CSize m_sizeElem;		// Element photo size
	CRect m_rtGameRect;		// Game zone size
	CGameControl m_GameC;
	int nElemW;
	int nElemH;
	bool m_bPause;
	bool m_bPlay;

	// Method
	void InitBackground(void);
	void InitElement(void);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex asvPath[4], int nVexNum);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_GameProgress;
	afx_msg void OnClickedBtnPause();
};
