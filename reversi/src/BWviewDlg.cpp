// BWviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BWview.h"
#include "BWviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBWviewDlg dialog

CBWviewDlg::CBWviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBWviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBWviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBWviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBWviewDlg)
	DDX_Control(pDX, IDC_QUIT, m_quit);
	DDX_Control(pDX, IDC_RESET, m_login);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBWviewDlg, CDialog)
	//{{AFX_MSG_MAP(CBWviewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBWviewDlg message handlers

BOOL CBWviewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
//	CButton*		Reset=(CButton*)GetDlgItem(IDC_RESET);
//	Reset->EnableWindow(FALSE);	
	CRect	Client;
	GetClientRect(&Client);
	CRect	rect;
	rect.top=Client.top+100;
	rect.left=Client.left+50;
	rect.bottom=rect.top+50;
	rect.right=rect.left+50;

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			m_chess[i][j].Create("Chess",WS_VISIBLE|WS_CHILD |BS_OWNERDRAW|BS_NOTIFY,rect, this,(i*j+1)*100);
	//		m_chess[i][j].LoadBitmaps(IDB_EMPTY);
			m_chess[i][j].m_chessx=i;
			m_chess[i][j].m_chessy=j;
			m_chess[i][j].m_flag=0;
			rect.left+=50;
			rect.right+=50;
		}
		rect.top+=50;
		rect.bottom+=50;
		rect.left=Client.left+50;
		rect.right=rect.left+50;
	}
/*	m_chess[3][3].LoadBitmaps(IDB_WHITE);
	m_chess[3][3].m_flag=-1;
	m_chess[3][4].LoadBitmaps(IDB_BLACK);
	m_chess[3][4].m_flag=1;
	m_chess[4][3].LoadBitmaps(IDB_BLACK);
	m_chess[4][3].m_flag=1;
	m_chess[4][4].LoadBitmaps(IDB_WHITE);
	m_chess[4][4].m_flag=-1;
*/	// TODO: Add extra initialization here
	m_chess[3][3].m_url="pic/white.bmp";
	m_chess[3][3].m_flag=-1;
	m_chess[3][3].InvalidateRect(NULL);
	m_chess[3][4].m_url="pic/black.bmp";
	m_chess[3][4].m_flag=1;
	m_chess[3][4].InvalidateRect(NULL);
	m_chess[4][3].m_url="pic/black.bmp";
	m_chess[4][3].m_flag=1;
	m_chess[4][3].InvalidateRect(NULL);
	m_chess[4][4].m_url="pic/white.bmp";
	m_chess[4][4].m_flag=-1;
	m_chess[4][4].InvalidateRect(NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBWviewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBWviewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBWviewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBWviewDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CBWviewDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CBWviewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CBWviewDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC ClientDC(this); 
	CRect bg;
	GetClientRect(&bg);

	CLoadBmp LoadBmp(ClientDC);
	LoadBmp.Initial();
	LoadBmp.InsertBmp(bg.right,0,bg.right,33,0,70,"Pic/BG_TOP.bmp");
	LoadBmp.InsertBmp(bg.right,bg.bottom-70,bg.right,bg.bottom-70,0,103,"Pic/BG_MID.bmp");
	LoadBmp.InsertBmp(bg.right-175,0,bg.right-175,90,0,0,"Pic/Banner_Mid.bmp");
	LoadBmp.InsertBmp(0,0,175,90,bg.right-175,0,"Pic/Banner_Right.bmp");
	LoadBmp.InsertBmp(0,0,352,90,bg.left+130,0,"Pic/Banner_Cen.bmp");
	InvalidateRect(&bg,FALSE);	
	return TRUE;
}

void CBWviewDlg::OnReset() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			m_chess[i][j].m_flag=0;
			m_chess[i][j].m_url="pic/empty.bmp";
			m_chess[i][j].InvalidateRect(NULL);
			CChess::g_game.m_board[i][j].m_flag=0;
			CChess::g_game.m_board[i][j].m_value=0;
		}
	}
	m_chess[3][3].m_url="pic/white.bmp";
	m_chess[3][3].m_flag=-1;
	CChess::g_game.m_board[3][3].m_flag=-1;
	m_chess[3][3].InvalidateRect(NULL);
	m_chess[3][4].m_url="pic/black.bmp";
	m_chess[3][4].m_flag=1;
	CChess::g_game.m_board[3][4].m_flag=1;
	m_chess[3][4].InvalidateRect(NULL);
	m_chess[4][3].m_url="pic/black.bmp";
	m_chess[4][3].m_flag=1;
	CChess::g_game.m_board[4][3].m_flag=1;
	m_chess[4][3].InvalidateRect(NULL);
	m_chess[4][4].m_url="pic/white.bmp";
	m_chess[4][4].m_flag=-1;
	CChess::g_game.m_board[4][4].m_flag=-1;
	m_chess[4][4].InvalidateRect(NULL);	
}

void CBWviewDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	CBWviewDlg::OnCancel();
}
