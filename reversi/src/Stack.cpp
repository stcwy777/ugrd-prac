// Stack.cpp: implementation of the CStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Stack.h"
#define	NULL 0
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStack::CStack()
{
	m_bottom=NULL;
	m_top=NULL;
}

CStack::~CStack()
{

}

void CStack::Push(int i,int j,BOARD board[][8])
{
	STACK	temp=new stack;				//申请一个节点
	temp->m_x=i;						//该节点的坐标域
	temp->m_y=j;
	for(int n=0;n<8;n++)				//该节点的棋盘域
		for(int m=0;m<8;m++)
		{
			temp->m_temp[n][m].m_flag=board[n][m].m_flag;
			temp->m_temp[n][m].m_value=board[n][m].m_value;
		}

	temp->next=NULL;				//建立栈
	if(m_bottom==NULL)
	{
		m_bottom=temp;
		temp->back=NULL;
	}
	else
	{
		m_top->next=temp;
		temp->back=m_top;
	}
	m_top=temp;
}

void CStack::Pop(int & i,int &j,BOARD board[][8])
{
	i=m_top->m_x;
	j=m_top->m_y;

	for(int n=0;n<8;n++)
		for(int m=0;m<8;m++)
		{
			board[n][m].m_flag=m_top->m_temp[n][m].m_flag;
			board[n][m].m_value=m_top->m_temp[n][m].m_value;
		}
	STACK	temp=m_top;
	if(m_top->back!=NULL)
		m_top=m_top->back;
	else
	{
		m_top=NULL;
		m_bottom=NULL;
	}
	delete temp;
}

bool CStack::IsNull()
{
	if(m_bottom==m_top)
		return true;
	else
		return false;
}
