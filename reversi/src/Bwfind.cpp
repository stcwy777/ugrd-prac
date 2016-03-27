// Bwfind.cpp: implementation of the CBwfind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bwfind.h"
#include "windows.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBwfind::CBwfind()
{
	ComChoice=WHITE;
	ManChoice=BLACK;
	m_board[3][3].m_flag=-1;
	m_board[3][4].m_flag=1;
	m_board[4][3].m_flag=1;
	m_board[4][4].m_flag=-1;
	m_depreq=3;
}

CBwfind::~CBwfind()
{

}

bool CBwfind::FindBegin(int flag)
{
	int		n=m_depreq;					//搜索深度
	int		depth=1;					//当前深度
	int		i=0,j=0;					//坐标
	int		p,q;						//坐标索引
	int		max,min;					//我方,敌方布子的比较量
	int		lastflag=0;					//上一步棋子
	int		samecolor=0;
	m_cut=25000;
	m_bestChoice.m_value=-20000;
	m_stack.Push(i,j,m_board);
	while(n)
	{
		for(;i<8;i++)
		{
			for(;j<8;j++)
			{
				if(i==0&&j==0)							//新的一种棋盘布局
					m_dropped=0;
				if(depth<n)								//没有检索到最后层次
				{
					if(Judge(m_board,i,j,flag))			//判断可下点
					{
						n=m_depreq;
						m_dropped=1;					//设置标志变量
						m_missed=0;
						m_stack.Push(i,j,m_board);
						m_board[i][j].m_flag=flag;
						NewBoard(m_board,i,j);
						m_flags.Push(lastflag);				
						lastflag=flag;
						flag=-flag;
						depth++;
						i=0;
						j=-1;
						continue;
					}
				}
				else if(depth==n)
				{
					max=-20000;
					min= 20000;
					if(m_cut==25000)
					{
//						if(lastflag==ComChoice)
						if(flag==ManChoice)
							m_cut=-20000;
//						else if(lastflag==ManChoice)
						else if(flag==ComChoice)
							m_cut= 20000;
					}
					for(p=0;p<8;p++)
					{
						for(q=0;q<8;q++)
						{
							if(Judge(m_board,p,q,flag))
							{
								if(n==m_depreq)					//最底层
								{
									SaveBoard();
									m_board[p][q].m_flag=flag;
									NewBoard(m_board,p,q);
									m_board[p][q].m_value+=ValueFirst(m_board);
									RestoreBoard();
								}
								m_dropped=1;					//当前棋局该色有子可下
								m_missed=0;						//无子可下
	
								//this for corner
								//if(lastflag==ComChoice)						//上一步是我方下的
								if(flag==ManChoice)
								{
									if(m_board[p][q].m_value<=m_cut&&samecolor==0)			//剪枝
									{
										min=m_board[p][q].m_value;
										p=8;
										q=8;
									}
									else if(min>m_board[p][q].m_value)
									{
										min=m_board[p][q].m_value;
									}
								}
								else if(flag==ComChoice)
								//else if(lastflag==ManChoice)				//上一步是敌方下的
								{
									if(m_board[p][q].m_value>=m_cut&&samecolor==0)
									{
										max=m_board[p][q].m_value;
										p=8;
										q=8;
									}
									else if(max<m_board[p][q].m_value)
									{
										max=m_board[p][q].m_value;									
									}
								}
							}//if
						}//for q
					}//for p
					if(m_dropped==1)
					{
						SaveValue();					
						m_stack.Pop(i,j,m_board);
						RestoreValue();

						SaveBoard();
						m_board[i][j].m_flag=lastflag;
						NewBoard(m_board,i,j);
						LineSence(m_board,i,j);
						Corner(m_board,i,j);
						RestoreBoard();
						if(lastflag==ComChoice)			
						{
							if(samecolor==1)
								m_board[i][j].m_value+=max;
							else
								m_board[i][j].m_value+=min;
							if(m_cut<m_board[i][j].m_value)
								m_cut=m_board[i][j].m_value;
						}
						else if(lastflag==ManChoice)		
						{
							if(samecolor==1)
								m_board[i][j].m_value+=min;
							else
								m_board[i][j].m_value+=max;
							if(m_cut>m_board[i][j].m_value)
								m_cut=m_board[i][j].m_value;
						}
						samecolor=0;					
						flag=lastflag;
						m_flags.Pop(lastflag);
						depth--;
						if(depth==1)
						{
							if(m_bestChoice.m_value<m_board[i][j].m_value)
							{
								m_bestChoice.m_x=i;
								m_bestChoice.m_y=j;
								m_bestChoice.m_value=m_board[i][j].m_value;
							}
						}
					}//if
					else
					{
						if(m_missed>0)
						{
							samecolor=0;
							SaveValue();
							m_stack.Pop(i,j,m_board);
							RestoreValue();
							m_board[i][j].m_value=ValueFirst(m_board);
							flag=lastflag;
							m_flags.Pop(lastflag);
							m_dropped=1;
							depth--;
							if(depth==1)
							{
								if(m_bestChoice.m_value<m_board[i][j].m_value)
								{
									m_bestChoice.m_x=i;
									m_bestChoice.m_y=j;
									m_bestChoice.m_value=m_board[i][j].m_value;
								}
							}
						}
						else
						{
							m_missed++;
							flag=-flag;
							i=0;
							j=-1;
							samecolor=1;
						}
					}
				}
			}//for j
			j=0;
		}//for i
		if(m_dropped==0)
		{
			if(m_missed>0)
			{
				SaveValue();
				m_stack.Pop(i,j,m_board);
				RestoreValue();
				m_board[i][j].m_value=ValueFirst(m_board);
				flag=lastflag;
				depth--;
				m_dropped=1;
				if(depth==1)
				{
					if(m_bestChoice.m_value<m_board[i][j].m_value)
					{
						m_bestChoice.m_x=i;
						m_bestChoice.m_y=j;
						m_bestChoice.m_value=m_board[i][j].m_value;
					}
				}
				j++;
			}
			else
			{
				flag=-flag;
				m_missed++;
				i= 0;
				j= 0;
			}
		}
		else if(m_dropped==1)
		{
			if(m_stack.IsNull())
				break;
			else
			{
				n--;
				i=0;
				j=0;
//				flag=lastflag;
//				m_flags.Pop(lastflag);
				if(flag==ManChoice)
				{
					m_cut=-20000;
				}
				else if(flag==ComChoice)
				{
					m_cut=20000;
				}
			}
		}
	
	}//while n
	m_stack.Pop(i,j,m_board);
	m_board[m_bestChoice.m_x][m_bestChoice.m_y].m_flag=-1;
	CBwfind::NewBoard(m_board,m_bestChoice.m_x,m_bestChoice.m_y);
	if(CBwfind::Search(m_board,BLACK))
		return true;
	else
		return false;
}

bool CBwfind::Judge(BOARD tb[][8],int chess_x,int chess_y,int flag)
{
	//向左上角斜向搜索

	int temptx=chess_x;									//暂时储存x,y的坐标，以便搜索
	int tempty=chess_y;
	if	(tb[temptx][tempty].m_flag!=EMPTY)
		return false;									//必须是一个空白的地方
	
	if (temptx>=2&&tempty>=2)
	{
		if (tb[temptx-1][tempty-1].m_flag==-flag)		//构成放子条件
		{
			temptx=temptx-2;		
			tempty=tempty-2;
			while(temptx>=0&&tempty>=0)					//边界检测
			{	
				if (tb[temptx][tempty].m_flag==flag)	//找到自己配对的己方的棋子
					return true;						//返回
				else if (tb[temptx][tempty].m_flag==-flag)
				{
					temptx=temptx-1;
					tempty=tempty-1;
				}
				else
				{
					temptx=-1;
					tempty=-1;
				}
			}
		}
	}
	//向上直着搜索
	temptx=chess_x;
	tempty=chess_y;
	if(temptx>=2)										//符合向上搜索条件
	{
		if (tb[temptx-1][tempty].m_flag==-flag)			//向上相邻的一颗是敌方的棋子
		{
			temptx=temptx-2;
			while (temptx>=0)
			{
				if (tb[temptx][tempty].m_flag==-flag)
				{
					temptx=temptx-1;
				}
				else if (tb[temptx][tempty].m_flag==flag)
					return true;
				else
					temptx=-1;
			}
		}
			
	}
	//向右上搜索
	temptx=chess_x;
	tempty=chess_y;
	if(tempty<=5&&temptx>=2)
	{
		if (tb[temptx-1][tempty+1].m_flag==-flag)
		{	
			temptx-=2;
			tempty+=2;
			while(tempty<=7&&temptx>=0)
			{
				if(tb[temptx][tempty].m_flag==-flag)
				{
					temptx-=1;
					tempty+=1;
				}
				else if(tb[temptx][tempty].m_flag==flag)
					return true;
				else 
				{
					tempty=8;
					temptx=-1;
				}
			}
		}

	}
	//向左搜索
	temptx=chess_x;
	tempty=chess_y;
	if (tempty>=2)
	{
		if(tb[temptx][tempty-1].m_flag==-flag)
		{
			tempty-=2;
			while (tempty>=0)
			{
				if(tb[temptx][tempty].m_flag==-flag)
					tempty-=1;
				else if(tb[temptx][tempty].m_flag==flag)
					return true;
				else
					tempty=-1;
			}
		}
	}
	//向右搜索
	temptx=chess_x;
	tempty=chess_y;
	if(tempty<=5)
	{
		if(tb[temptx][tempty+1].m_flag==-flag)
		{
			tempty+=2;
			while (tempty<=7)
			{
				if (tb[temptx][tempty].m_flag==-flag)
					tempty+=1;
				else if (tb[temptx][tempty].m_flag==flag)
					return true;
				else 
					tempty=8;								//没有找到
			}
		}
	}
	//向左下搜索
	temptx=chess_x;
	tempty=chess_y;
	if (tempty>=2&&temptx<=5)
	{
		if(tb[temptx+1][tempty-1].m_flag==-flag)
		{
			temptx+=2;
			tempty-=2;
			while(temptx<=7&&tempty>=0)
			{
				if(tb[temptx][tempty].m_flag==-flag)
				{
					temptx+=1;
					tempty-=1;
				}
				else if (tb[temptx][tempty].m_flag==flag)
				{
					return true;
				}
				else
				{
					temptx=8;
					tempty=-1;
				}
			}
		}
	}
//向下搜索
	temptx=chess_x;
	tempty=chess_y;
	if (temptx<=5)
	{
		if (tb[temptx+1][tempty].m_flag==-flag)
		{
			temptx+=2;
			while(temptx<=7)
			{
				if(tb[temptx][tempty].m_flag==-flag)
					temptx+=1;
				else if(tb[temptx][tempty].m_flag==flag)
					return true;
				else 
					temptx=8;
			}
		}
	}
//向右下
	temptx=chess_x;
	tempty=chess_y;
	if (temptx<=5&&tempty<=5)
	{
		if(tb[temptx+1][tempty+1].m_flag==-flag)
		{
			tempty+=2;
			temptx+=2;
			while(temptx<=7&&tempty<=7)
			{
				if(tb[temptx][tempty].m_flag==-flag)
				{	
					temptx+=1;
					tempty+=1;
				}
				else if(tb[temptx][tempty].m_flag==flag)
					return true;
				else
				{
					temptx=8;
					tempty=8;
				}
					
			}
		}
	}
	return false;
	
}

void CBwfind::NewBoard(BOARD tb[][8],int chess_x,int chess_y)
{
	int temptx=chess_x,tempty=chess_y;	 //暂时储存棋盘的信息
	int flag=tb[chess_x][chess_y].m_flag;
	//左上吃子
	if (chess_x>=2&&chess_y>=2)
	{
		if(tb[temptx-1][tempty-1].m_flag==-flag)	//可以吃子
			temptx=temptx-2;
			tempty=tempty-2;
			while(temptx>=0&&tempty>=0)
			{
				if (tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx,j=tempty;i!=chess_x;i++,j++)
						tb[i][j].m_flag=flag;			//将吃掉的子变成我方的棋子
					temptx=-1;
					tempty=-1;
				}
				else if (tb[temptx][tempty].m_flag==0)
				{
					temptx=-1;
					tempty=-1;
				}
				else
				{
					temptx-=1;
					tempty-=1;
				}
			}
	}
	//向上吃子
	temptx=chess_x;
	tempty=chess_y;
	if(temptx>=2)	//符合向上搜索条件
	{
		if (tb[temptx-1][tempty].m_flag==-flag) //向上相邻的一颗是敌方的棋子
		{
			temptx=temptx-2;
			while (temptx>=0)
			{
				if (tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx;i!=chess_x;i++)
						tb[i][tempty].m_flag=flag;
					temptx=-1;
				}
				else if (tb[temptx][tempty].m_flag==0)
				{
					temptx=-1;
				}
				else 
					temptx-=1;
			}
		}
	
	}
	//向右上吃子
	temptx=chess_x;
	tempty=chess_y;
	if(tempty<=5&&temptx>=2)
	{
		if (tb[temptx-1][tempty+1].m_flag==-flag)
		{	
			temptx-=2;
			tempty+=2;
			while(tempty<=7&&temptx>=0)
			{
				if(tb[temptx][tempty].m_flag==0)
				{
					temptx=-1;
					tempty=8;
				}
				else if(tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx,j=tempty;i!=chess_x;i++,j--)
						tb[i][j].m_flag=flag;
					temptx=-1;
				}
				else 
				{
					temptx-=1;
					tempty+=1;
				}
			}
		}
		
	}
//向左吃子
	temptx=chess_x;
	tempty=chess_y;
	if (tempty>=2)
	{
		if(tb[temptx][tempty-1].m_flag==-flag)
		{
				tempty-=2;
				while (tempty>=0)
				{
					if(tb[temptx][tempty].m_flag==0)
						tempty=-1;
					else if(tb[temptx][tempty].m_flag==flag)
					{
						for(int i=tempty;i<chess_y;i++)
							tb[temptx][i].m_flag=flag;
						tempty=-1;
					}
					else
						tempty-=1;
				}
		}
	}
    //向右吃子
	temptx=chess_x;
	tempty=chess_y;
	if(tempty<=5)
	{
		if(tb[temptx][tempty+1].m_flag==-flag)
		{
			tempty+=2;
			while (tempty<=7)
			{
					if (tb[temptx][tempty].m_flag==0)
						tempty=8;
					else if (tb[temptx][tempty].m_flag==flag)
					{
						for(int i=tempty;i>chess_y;i--)
						{
							tb[temptx][i].m_flag=flag;
						}
						tempty=8;
					}
					else 
						tempty+=1;	//没有找到
			}
		}
	}

    //向左下吃子
	temptx=chess_x;
	tempty=chess_y;
	if (tempty>=2&&temptx<=5)
	{
		if(tb[temptx+1][tempty-1].m_flag==-flag)
		{
			temptx+=2;
			tempty-=2;
			while(temptx<=7&&tempty>=0)
			{
				if(tb[temptx][tempty].m_flag==0)
				{
					temptx=8;
					continue;
				}
				else if (tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx,j=tempty;i!=chess_x;i--,j++)
						tb[i][j].m_flag=flag;
					temptx=8;
				}
				else
				{
					temptx+=1;
					tempty-=1;
				}
			}
		}
	}
    //向下吃子
	temptx=chess_x;
	tempty=chess_y;
	if (temptx<=5)
	{
		if (tb[temptx+1][tempty].m_flag==-flag)
		{
			temptx+=2;
			while(temptx<=7)
			{
				if(tb[temptx][tempty].m_flag==0)
					temptx=8;
				else if(tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx;i!=chess_x;i--)
						tb[i][tempty].m_flag=flag;
					temptx=8;
				}
				else 
					temptx+=1;
			}
		}
	}
    //向右下
	temptx=chess_x;
	tempty=chess_y;
	if (temptx<=5&&tempty<=5)
	{
		if(tb[temptx+1][tempty+1].m_flag==-flag)
		{
			tempty+=2;
			temptx+=2;
			while(temptx<=7&&tempty<=7)
			{
				if(tb[temptx][tempty].m_flag==0)
				{	
					temptx=8;
				}
				else if(tb[temptx][tempty].m_flag==flag)
				{
					for(int i=temptx,j=tempty;i!=chess_x;i--,j--)
						tb[i][j].m_flag=flag;
					temptx=8;
				}
				else
				{
					temptx+=1;
					tempty+=1;
				}
				
			}
		}
	}
}

void CBwfind::SaveBoard()
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			m_save[i][j].m_flag=m_board[i][j].m_flag;
			m_save[i][j].m_value=m_board[i][j].m_value;
		}
}
void CBwfind::SaveValue()
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			m_save[i][j].m_value=m_board[i][j].m_value;
		}
}
void CBwfind::RestoreValue()
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			m_board[i][j].m_value=m_save[i][j].m_value;
		}
}

void CBwfind::RestoreBoard()
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			m_board[i][j].m_flag=m_save[i][j].m_flag;
		}
}


int CBwfind::ValueFirst(BOARD tb[][8])
{
	int	flag=ComChoice;
	int ComMobil=Mobility(tb,ComChoice);
	int ManMobil=Mobility(tb,ManChoice);
	int DiffMobil=ComMobil-ManMobil;			//敌我双方的行动力的差别
	int minus;
	int danger;
	int value;
	if(flag==BLACK)
	{
		minus=White(tb)-Black(tb);
		danger=Black(tb);				//最小吃子法
	}
	if (flag==WHITE)
	{
		minus=Black(tb)-White(tb);
		danger=White(tb);
	}
	
	value=minus+2*DiffMobil;		//估值的合并
	if(danger==0)
		value=-10000;
	if (Search(tb,ComChoice)==false&&Search(tb,ManChoice)==false)	//白子和黑子都没得下了
	{
		if(ComChoice==BLACK)		//我方黑子
		{
			if(Black(tb)-White(tb)>0)
				value=10000;
			else					//我方白子
				value=-10000;
		}
		if (ManChoice==BLACK)		//敌方黑子
		{
			if(White(tb)-Black(tb)>0)
				value=10000;
			else
				value=-10000;

		}
	}
	return value;
}

//行动力,当前可以落子的点
int CBwfind::Mobility(BOARD tb[][8],int flag)
{
	int move=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++){
			if (Judge(tb,i,j,flag))
				move++;
		}
	return move;
}

void CBwfind::LineSence	(BOARD tb[][8],int chess_x,int chess_y)
{
	int line=0;
	int j=0;
    //左上顶角
	if (tb[0][0].m_flag==ManChoice)
	{
		if (chess_x==0)				//棋子在y轴
		{
			while (tb[0][j].m_flag==ManChoice)
				j++;
			if (tb[0][j].m_flag==ComChoice)
			{
				while (j<8&&tb[0][j].m_flag==ComChoice)
					j++;
				if(j<8&&tb[0][j].m_flag==0)
					line-=1000;
			}	
		}
		if(chess_y==0)			//棋子在x轴
		{
			j=0;
			while(tb[j][0].m_flag==ManChoice)
				j++;
			if(tb[j][0].m_flag==ComChoice)
				while(j<8&&tb[j][0].m_flag==ComChoice)
					j++;
				if (j<8&&tb[j][0].m_flag==0)
				{
					line-=1000;
				}
		}		
	}
    //右上顶角
	if (tb[0][7].m_flag==ManChoice)
	{
		j=7;
		if (chess_x==0)
		{
			while (tb[0][j].m_flag==ManChoice)
				j--;
			if (tb[0][j].m_flag==ComChoice)
			{
				while (j>=0&&tb[0][j].m_flag==ComChoice)
					j--;
					if(j>=0&&tb[0][j].m_flag==0)
						line-=1000;
			}	
		}
		if(chess_y==7)
		{
			j=0;
			while(tb[j][7].m_flag==ManChoice)
				j++;
			if(tb[j][7].m_flag==ComChoice)
				while(j<8&&tb[j][7].m_flag==ComChoice)
					j++;
					if (j<8&&tb[j][7].m_flag==0)
					{
						line-=1000;
					}
		}		
	}
    //左下顶角
	if (tb[7][0].m_flag==ManChoice)
	{
		j=0;
		if (chess_x==7)
		{
			while (tb[7][j].m_flag==ManChoice)
					j++;
			if (tb[7][j].m_flag==ComChoice)
			{
				while (j<8&&tb[7][j].m_flag==ComChoice)
					j++;
					if(j<8&&tb[7][j].m_flag==0)
						line-=1000;
			}	
		}
		if(chess_y==0)
		{
			j=7;
			while(tb[j][0].m_flag==ManChoice)
				j--;
			if(tb[j][0].m_flag==ComChoice)
				while(j>=0&&tb[j][0].m_flag==ComChoice)
					j--;
					if (j>=0&&tb[j][0].m_flag==0)
					{
						line-=1000;
					}
		}		
	}
    //右下顶角
	if (tb[7][7].m_flag==ManChoice)
	{
		if (chess_x==7)
		{
			j=7;
			while (tb[7][j].m_flag==ManChoice)
				j--;
			if (tb[7][j].m_flag==ComChoice)
			{
				while (j>=0&&tb[7][j].m_flag==ComChoice)
						j--;
					if(j>=0&&tb[7][j].m_flag==0)
						line-=1000;
			}	
		}
		if(chess_y==7)
		{
			j=7;
			while(tb[j][7].m_flag==ManChoice)
				j--;
			if(tb[j][7].m_flag==ComChoice)
				while(j>=0&&tb[j][7].m_flag==ComChoice)
					j--;
					if (j>=0&&tb[j][7].m_flag==0)
					{
						line-=1000;
					}
		}		
	}
	tb[chess_x][chess_y].m_value+=line;
}


int CBwfind::White(BOARD tb[][8])
{
	int nWhite=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(tb[i][j].m_flag==WHITE)
				nWhite++;
	return nWhite;
}

int CBwfind::Black(BOARD tb[][8])
{
	int nBlack=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(tb[i][j].m_flag==BLACK)
				nBlack++;
	return nBlack;
}

//搜索放棋子的地方，有棋子可以放返回真
bool CBwfind::Search(BOARD tb[][8],int flag)
{
	for (int i=0;i<8;i++)
		for (int j=0;j<8;j++)
			if (Judge(tb,i,j,flag))
				return true;
	return false;
}

void CBwfind::Corner(BOARD tb[][8],int chess_x,int chess_y)
{
	int flag=ComChoice;
	int corner=0;
	int value=0;
	int i,j;
	int temptx=chess_x;
	int	tempty=chess_y;
	if(temptx==0&&tempty==0&&tb[0][0].m_flag==flag) 
		value+=2000;
	if(temptx==0&&tempty==7&&tb[0][7].m_flag==flag) 
		value+=2000;
	if(temptx==7&&tempty==0&&tb[7][0].m_flag==flag) 
		value+=2000;
	if(temptx==7&&tempty==7&&tb[7][7].m_flag==flag) 
		value+=2000;

	if(tb[0][0].m_flag==0){
		if(tb[0][1].m_flag==flag){
			j=1;
			while(j<8&&tb[0][j].m_flag==flag) 
				j++;
			if(j<8&&tb[0][j].m_flag==-flag) 
				value-=5000;
		}
		if(tb[1][0].m_flag==flag){
			i=1;
			while(i<8&&tb[i][0].m_flag==flag) 
				i++;
			if(i<8&&tb[i][0].m_flag==-flag) 
				value-=5000;
		}
	}


	if(tb[0][7].m_flag==0){
		if(tb[0][6].m_flag==flag){
			j=6;
			while(j>=0&&tb[0][j].m_flag==flag) 
				j--;
			if(j>=0&&tb[0][j].m_flag==-flag) 
				value-=5000;
		}
		
		if(tb[1][7].m_flag==flag){
			i=1;
			while(i<8&&tb[i][7].m_flag==flag)
				i++;
			if(i<8&&tb[i][7].m_flag==-flag) 
				value-=5000;
		}
	}


	if(tb[7][0].m_flag==0){
		if(tb[7][1].m_flag==flag){
			j=1;
			while(j<8&&tb[7][j].m_flag==flag) 
				j++;
			if(j<8&&tb[7][j].m_flag==-flag) 
				value-=5000;
		}
		if(tb[6][0].m_flag==flag){
			i=6;
			while(i>=0&&tb[i][0].m_flag==flag) 
				i--;
			if(i>=0&&tb[i][0].m_flag==-flag) 
				value-=5000;
		}
	}

	if(tb[7][7].m_flag==0){
		if(tb[7][6].m_flag==flag){
			j=6;
			while(j>=0&&tb[7][j].m_flag==flag) 
				j--;
			if(j>=0&&tb[7][j].m_flag==-flag) 
				value-=5000;
		}
		if(tb[6][7].m_flag==flag){
			i=6;
			while(i>=0&&tb[i][7].m_flag==flag)
				i--;
			if(i>=0&&tb[i][7].m_flag==-flag)
				value-=5000;
		}
	}
	
	temptx=chess_x;tempty=chess_y;
	if(temptx==1&&tempty==1&&tb[0][0].m_flag-flag!=0&&tb[temptx][tempty].m_flag==flag)
		value-=2000;
	if(temptx==1&&tempty==6&&tb[0][7].m_flag-flag!=0&&tb[temptx][tempty].m_flag==flag)
		value-=2000;
	if(temptx==6&&tempty==1&&tb[7][0].m_flag-flag!=0&&tb[temptx][tempty].m_flag==flag)
		value-=2000;
	if(temptx==6&&tempty==6&&tb[7][7].m_flag-flag!=0&&tb[temptx][tempty].m_flag==flag)
		value-=2000;
	
	tb[temptx][tempty].m_value+=value;
}