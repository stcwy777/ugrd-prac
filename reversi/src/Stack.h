// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__5285110D_2692_4BCA_A028_6FFF18A27537__INCLUDED_)
#define AFX_STACK_H__5285110D_2692_4BCA_A028_6FFF18A27537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct	board
{
	int	m_value;
	int m_flag;
}BOARD;

typedef struct	stack
{
	int		m_x;			//存放棋子坐标
	int		m_y;			
	BOARD	m_temp[8][8];			//存放棋盘
	stack	*next;
	stack	*back;
}*STACK;

class CStack  
{
public:
	bool IsNull();
	STACK	m_bottom;
	STACK	m_top;
	void	Push(int i,int j,BOARD board[][8]);
	void	Pop(int &i,int &j, BOARD  board[][8]);
	CStack();
	virtual ~CStack();

};

#endif // !defined(AFX_STACK_H__5285110D_2692_4BCA_A028_6FFF18A27537__INCLUDED_)
