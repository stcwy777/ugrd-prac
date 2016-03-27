// BWviewDlg.h : header file
//

#if !defined(AFX_BWVIEWDLG_H__70D72208_AD46_4311_80F6_DA09851972E4__INCLUDED_)
#define AFX_BWVIEWDLG_H__70D72208_AD46_4311_80F6_DA09851972E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBWviewDlg dialog
#include "Chess.h"
#include "LoginButton.h"
class CBWviewDlg : public CDialog
{
// Construction
public:
	CBWviewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBWviewDlg)
	enum { IDD = IDD_BWVIEW_DIALOG };
	CLoginButton	m_quit;
	CLoginButton	m_login;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBWviewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON	m_hIcon;
	CChess	m_chess[8][8];		//Æå×Ó
	// Generated message map functions
	//{{AFX_MSG(CBWviewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnReset();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWVIEWDLG_H__70D72208_AD46_4311_80F6_DA09851972E4__INCLUDED_)
