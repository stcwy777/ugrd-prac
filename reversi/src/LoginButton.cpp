// LoginButton.cpp : implementation file
//

#include "stdafx.h"
#include "LoginButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginButton

CLoginButton::CLoginButton()
{
}

CLoginButton::~CLoginButton()
{
}


BEGIN_MESSAGE_MAP(CLoginButton, CButton)
	//{{AFX_MSG_MAP(CLoginButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginButton message handlers

void CLoginButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CRect	rect =  lpDrawItemStruct->rcItem;						//获取外边框
	CDC		*pDC=CDC::FromHandle(lpDrawItemStruct->hDC);			//获取窗口CDC
	int		nSaveDC=pDC->SaveDC();									//保存原设备环境	

	CClientDC ClientDC(this); 
	CLoadBmp LoadBmp(ClientDC);
	LoadBmp.Initial();

	CString	str;													//存放数组		
	this->GetWindowText(str);										//获取按钮标题
	UINT state = lpDrawItemStruct->itemState;						//获取按钮状态

					
	if(state & ODS_SELECTED)						//选中状态
	{	
		LoadBmp.InsertBmp(0,0,71,27,0,0,"Pic/But_Down.bmp");
	}
	else if(state & ODS_FOCUS)
	{
		LoadBmp.InsertBmp(0,0,71,27,0,0,"Pic/But_Focus.bmp");
	}
	else															//非选中状态
	{
		if(m_over)
		{															//在非选中状态下判断是否在按钮区域内并响应
			LoadBmp.InsertBmp(0,0,71,27,0,0,"Pic/But_Hover.bmp");
		}
		else
		{
			LoadBmp.InsertBmp(0,0,71,27,0,0,"Pic/But_Normal.bmp");
	
		}
	}

	COLORREF	Col;												//放置文本颜色
	if (str)
	{			
		LOGFONT	lf;													//字体结构体
		memset(&lf,0,sizeof(LOGFONT));								//设置变量为0
		lf.lfHeight=-12;											//设置大小
		lf.lfCharSet=GB2312_CHARSET;								
		strcpy((LPSTR)&(lf.lfFaceName),"宋体");						

		CFont	cf;													
		cf.CreateFontIndirect(&lf);									//创建字体

		CFont* hOldFont = pDC->SelectObject(&cf);					//装入设备表并保存原有
		int nMode = pDC->SetBkMode(TRANSPARENT);					//设置字体背景透明
		pDC->TextOut(rect.left+12,rect.top+5,str);					//输出在指定坐标
		pDC->SelectObject(hOldFont);
		pDC->SelectObject(&Col);
	}
	pDC->RestoreDC(nSaveDC);										//还原设备环境
	
}

void CLoginButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	TRACKMOUSEEVENT mouse;											//鼠标事件设置
	mouse.cbSize=sizeof(mouse);
	mouse.dwFlags=TME_LEAVE | TME_HOVER;
	mouse.dwHoverTime=10;
	mouse.hwndTrack=m_hWnd;
	_TrackMouseEvent(&mouse);										//有"_"	
	::SetCursor(LoadCursor(NULL,IDC_CROSS));	
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CLoginButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_over=FALSE;
	InvalidateRect(NULL);
	return 0;
}

LRESULT CLoginButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_over =TRUE;
	InvalidateRect(NULL);
	return 0;
}
