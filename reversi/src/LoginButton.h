#if !defined(AFX_LOGINBUTTON_H__4538DD38_5163_45C7_8698_20F3E2769386__INCLUDED_)
#define AFX_LOGINBUTTON_H__4538DD38_5163_45C7_8698_20F3E2769386__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginButton window
#include "LoadBmp.h"
class CLoginButton : public CButton
{
// Construction
public:
	CLoginButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoginButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLoginButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_over;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINBUTTON_H__4538DD38_5163_45C7_8698_20F3E2769386__INCLUDED_)
