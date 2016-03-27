// LoadBmp.h: interface for the CLoadBmp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADBMP_H__5EB3F5D4_E2AD_4F2D_901D_515B1E0006C1__INCLUDED_)
#define AFX_LOADBMP_H__5EB3F5D4_E2AD_4F2D_901D_515B1E0006C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"

class CLoadBmp  
{
private:
	CDC OpDC;
	CClientDC *ClientDC;
public:
	CLoadBmp();
	CLoadBmp(CClientDC & Client);
	virtual ~CLoadBmp();
	void Initial();
	//拓展高度,拓展宽度,图片长,图片宽,图片开始的位置,图片的路径
	void InsertBmp(int ex_lenth,int ex_width,int pic_lenth,int pic_width,int st_x,int st_y,CString url);
};

#endif // !defined(AFX_LOADBMP_H__5EB3F5D4_E2AD_4F2D_901D_515B1E0006C1__INCLUDED_)
