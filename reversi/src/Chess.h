#if !defined(AFX_CHESS_H__8E403367_9C2A_4D6C_8910_808C45066A0B__INCLUDED_)
#define AFX_CHESS_H__8E403367_9C2A_4D6C_8910_808C45066A0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Chess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChess window
#include "Bwfind.h"
#include "LoadBmp.h"
class CChess : public CButton//CBitmapButton
{
// Construction
public:
	CChess();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChess)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ChangeBmp();
	int		m_flag;
	virtual ~CChess();
	int		m_chessx;
	int		m_chessy;
	static CBwfind	g_game;
	CString	m_url;
	CLoadBmp	m_BmpLoader;
	// Generated message map functions
protected:
	//{{AFX_MSG(CChess)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESS_H__8E403367_9C2A_4D6C_8910_808C45066A0B__INCLUDED_)
