// Bwfind.h: interface for the CBwfind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWFIND_H__1ED34A60_7733_4E54_A662_18E73F309354__INCLUDED_)
#define AFX_BWFIND_H__1ED34A60_7733_4E54_A662_18E73F309354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stack.h"
#include "StackForFlag.h"

#define BLACK 1
#define WHITE -1
#define EMPTY 0
typedef struct bestchoice
{
	int m_x;
	int m_y;
	int m_value;
}BESTCHOICE;
class CBwfind  
{
public:
	void RestoreValue();
	void SaveValue();
	void RestoreValue(BOARD tb[][8]);
	BOARD	m_board[8][8];		//棋盘
	void Corner(BOARD tb[][8],int x,int y,int &value);
	bool Search(BOARD tb[][8],int flag);
	int  Black(BOARD tb[][8]);
	int  White(BOARD tb[][8]);
	int  ValueFirst(BOARD tb[][8]);
	void LineSence	(BOARD tb[][8],int chess_x,int chess_y);
	void Corner(BOARD tb[][8],int chess_x,int chess_y);
	int	 Mobility(BOARD tb[][8],int flag);
	void RestoreBoard();
	void SaveBoard();          
	bool FindBegin(int flag);  //Alpha-Beta剪枝
	bool Judge(BOARD tb[][8],int chess_x,int chess_y,int flag);
	void NewBoard(BOARD tb[][8],int chess_x,int chess_y);
	CBwfind();
	virtual ~CBwfind();
private:
	int		m_cut;				//Alpha-Beta剪枝参数
	int		m_dropped;			//当前棋盘有子可下
	int		m_missed;			//无子可下连续轮数
	int		m_depreq;			//要求深度
	BESTCHOICE	m_bestChoice;		//当前最好选择
	int		ManChoice;			//敌方行动	
	int		ComChoice;			//我方行动
	BOARD	m_save[8][8];		//算法中保存棋盘
	CStack	m_stack;			//棋局栈
	CStackForFlag m_flags;		//棋子栈
};

#endif // !defined(AFX_BWFIND_H__1ED34A60_7733_4E54_A662_18E73F309354__INCLUDED_)
