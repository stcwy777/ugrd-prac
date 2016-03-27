// LoadBmp.cpp: implementation of the CLoadBmp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoadBmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadBmp::CLoadBmp()
{

}
CLoadBmp::CLoadBmp(CClientDC &Client)
{
	ClientDC=&Client;
}
CLoadBmp::~CLoadBmp()
{				
}

void CLoadBmp::Initial()
{
	OpDC.CreateCompatibleDC(ClientDC);
}

void CLoadBmp::InsertBmp(int ex_lenth,int ex_width,int pic_lenth,int pic_width,int st_x,int st_y,CString url)
{
	HBITMAP *Hbmp;
	Hbmp=(HBITMAP *)LoadImage(AfxGetInstanceHandle(),url,IMAGE_BITMAP,ex_lenth,ex_width,LR_LOADFROMFILE);
	OpDC.SelectObject(Hbmp);
	ClientDC->BitBlt(st_x,st_y,pic_lenth,pic_width,&OpDC,0,0,SRCCOPY);
}
