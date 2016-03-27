// Chess.cpp : implementation file
//

#include "stdafx.h"
#include "BWview.h"
#include "Chess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChess
CBwfind	CChess::g_game;
CChess::CChess()
{
	m_url="pic/empty.bmp";
}

CChess::~CChess()
{
}


BEGIN_MESSAGE_MAP(CChess, CButton)
	//{{AFX_MSG_MAP(CChess)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChess message handlers

void CChess::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CChess	(*parent)[8]=(CChess (*)[8])(this-m_chessx*8-m_chessy);
	int i,j;
	bool	goon=false;

	if(CChess::g_game.Judge(CChess::g_game.m_board,m_chessx,m_chessy,BLACK))
	{
		//this->LoadBitmaps(IDB_BLACK);
		m_url="pic/black.bmp";
		//InvalidateRect(NULL);
		SendMessage(WM_PAINT);
		g_game.m_board[m_chessx][m_chessy].m_flag=BLACK;
		m_flag=BLACK;
		g_game.NewBoard(CChess::g_game.m_board,m_chessx,m_chessy);
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				parent[i][j].ChangeBmp();
			goon=false;
			while(!goon)
			{
				if(CChess::g_game.Search(CChess::g_game.m_board,WHITE))
				{
					goon=g_game.FindBegin(WHITE);
					for(i=0;i<8;i++)
						for(j=0;j<8;j++)
							parent[i][j].ChangeBmp();
					if(goon==false)
						MessageBox("��û������!���Լ���");
				}
				else
				{
					if(CChess::g_game.Search(CChess::g_game.m_board,BLACK))
					{
						goon=true;
						AfxMessageBox("����û������!�����");
					}
					else
					{
						if(CChess::g_game.White(CChess::g_game.m_board)>CChess::g_game.Black(CChess::g_game.m_board))
								AfxMessageBox("����Ӯ��!");
						else if(CChess::g_game.White(CChess::g_game.m_board)==CChess::g_game.Black(CChess::g_game.m_board))
								AfxMessageBox("�;�!");
						else
								AfxMessageBox("��Ӯ��!");
						break;
					}
				}

			}
	}
//	CButton::OnLButtonDown(nFlags, point);
}



void CChess::ChangeBmp()
{
	if(m_flag!=g_game.m_board[m_chessx][m_chessy].m_flag)
	{
		m_flag=g_game.m_board[m_chessx][m_chessy].m_flag;
		switch(m_flag)
		{
		case 1:
//			this->LoadBitmaps(IDB_BLACK);
			m_url="pic/black.bmp";
			break;
		case -1:
//			this->LoadBitmaps(IDB_WHITE);
			m_url="pic/white.bmp";
			break;
		case 0:
//			this->LoadBitmaps(IDB_EMPTY);
			m_url="pic/empty.bmp";
		}
		SendMessage(WM_PAINT);
	}
}


void CChess::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CClientDC ClientDC(this); 
	CLoadBmp LoadBmp(ClientDC);
	LoadBmp.Initial();
	LoadBmp.InsertBmp(0,0,50,50,0,0,m_url);
//	InvalidateRect(NULL);	
}

void CChess::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(LoadCursor(NULL,IDC_CROSS));		
	CButton::OnMouseMove(nFlags, point);
}
