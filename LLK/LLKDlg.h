
// LLKDlg.h : header file
//

#pragma once

// CLLKDlg dialog
class CLLKDlg : public CDialogEx
{
// Construction
public:
	CLLKDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Attributes
	CDC m_memDC;

	// Method
	void InitBackground(void);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedBtnBasic();
public:
	afx_msg void OnClickedBtnEasy();
//	afx_msg void OnClickedBtnGame();
	afx_msg void OnClickedBtnRank();
	afx_msg void OnClickedBtnSetting();
	afx_msg void OnClickedBtnHelp();
	afx_msg void OnClickedBtnLevel();
};
