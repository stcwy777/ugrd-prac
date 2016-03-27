// BWview.h : main header file for the BWVIEW application
//

#if !defined(AFX_BWVIEW_H__1E758A0C_C5EB_4FC2_875E_49C58173717D__INCLUDED_)
#define AFX_BWVIEW_H__1E758A0C_C5EB_4FC2_875E_49C58173717D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBWviewApp:
// See BWview.cpp for the implementation of this class
//

class CBWviewApp : public CWinApp
{
public:
	CBWviewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBWviewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBWviewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWVIEW_H__1E758A0C_C5EB_4FC2_875E_49C58173717D__INCLUDED_)
