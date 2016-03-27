/*****
*  The game of TETRIS implemented in Turboc
*
*  Author: Yun Wang
*
*  This code was written in 2005 when I was a freshmen in CS.
*  The coding style didn't follow any standards. Original comments were in 
*  Chinese and not sufficient. Instead of leaving the code in my old hard 
*  drive, I decide to archive these codes online to remind me those old days :)
******/

#define DELAY(x) while(t<x);t=0;
#define BOARD(x,y,X,i) bandary[((y+X.b[2*i]+y+X.b[2*i+1])/2-100)/20+1][((x+X.a[2*i]+x+X.a[2*i+1])/2-190)/20+1]
#define INFORM         outtextxy(250,180,"QQ:170319080");\
                       outtextxy(250,220,"CLICK ENTER");\
                       outtextxy(400,400,"PRODUCED BY WANG YUN");
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <bios.h>
#include <malloc.h>
#include <teris.h>
/*方块坐标转换公式:(限制数组与实际坐标)
           {[(基坐标+板偶坐标)+(基坐标+板奇坐标)]/2-100}/20+1*/

struct board /*方块结构体*/
{
    int a[8];
    int b[8];
    struct board*next;
}A1,A2,A3,A4,B1,B2,B3,B4,C1,D1,D2,D3,D4,E1,E2,F1,F2,G1,G2,X,X1;


void interrupt new(void);
void settime(void interrupt (*fun)());
void killtime(void);
void gamepad (void);
void gameset(void);
void start(void);
void setgameboard(void);
void draw(int,struct board,int,int);
void decidepad(struct board *,int *);
void congratulation(int,int);
int  transform(void);
int  judge(int,int);
void control(int *);
void clear(void);
void death(void);


int key;
int x,y;
int dly;
int down,left,right,dead;
int record,flag1,flag2;
int bandary[17][15];
int t;
int size;
void *buf;
void interrupt (*old)();

initgr()  /*初始化Turboc图形模式*/
{
    int a,b;
    a=DETECT;
    b=getgraphmode();
    initgraph(&a,&b,"");
}

void interrupt new()
{
    t++;
}

void settime(void interrupt (*fun)())  /*设置中断向量*/
{
    old=getvect(0x1c);
    disable();
    setvect(0x1c,fun);
    enable();
}

void killtime()
{
    disable();
    setvect(0x1c,old);
    enable();
}

void gamepad()    /*每种方块的形态存在一个链表里*/
{
    A1.a[0]=0;A1.a[1]=20;A1.a[2]=0;A1.a[3]=20;
    A1.a[4]=0;A1.a[5]=20;A1.a[6]=20;A1.a[7]=40;
    A1.b[0]=0;A1.b[1]=20;A1.b[2]=20;A1.b[3]=40;
    A1.b[4]=40;A1.b[5]=60;A1.b[6]=0;A1.b[7]=20;
    A2.a[0]=0;A2.a[1]=20;A2.a[2]=0;A2.a[3]=20;
    A2.a[4]=20;A2.a[5]=40;A2.a[6]=40;A2.a[7]=60;
    A2.b[0]=0;A2.b[1]=20;A2.b[2]=20;A2.b[3]=40;
    A2.b[4]=20;A2.b[5]=40;A2.b[6]=20;A2.b[7]=40;
    A3.a[0]=20;A3.a[1]=40;A3.a[2]=40;
    A3.a[3]=60;A3.a[4]=40;A3.a[5]=60;
    A3.a[6]=40;A3.a[7]=60;
    A3.b[0]=40;A3.b[1]=60;A3.b[2]=0;
    A3.b[3]=20;A3.b[4]=20;A3.b[5]=40;
    A3.b[6]=40;A3.b[7]=60;
    A4.a[0]=0;A4.a[1]=20;
    A4.a[2]=20;
    A4.a[3]=40;A4.a[4]=40;
    A4.a[5]=60;
    A4.a[6]=40;A4.a[7]=60;
    A4.b[0]=0;A4.b[1]=20;
    A4.b[2]=0;
    A4.b[3]=20;A4.b[4]=0;
    A4.b[5]=20;
    A4.b[6]=20;A4.b[7]=40;
    A1.next=&A2;A2.next=&A3;A3.next=&A4;A4.next=&A1;

    B1.a[0]=20;B1.a[1]=40;B1.a[2]=40;B1.a[3]=60;
    B1.a[4]=40;B1.a[5]=60;B1.a[6]=40;B1.a[7]=60;
    B1.b[0]=0;B1.b[1]=20;B1.b[2]=0;B1.b[3]=20;
    B1.b[4]=20;B1.b[5]=40;B1.b[6]=40;B1.b[7]=60;
    B2.a[0]=0;B2.a[1]=20;B2.a[2]=20;
    B2.a[3]=40;B2.a[4]=40;B2.a[5]=60;
    B2.a[6]=40;B2.a[7]=60;
    B2.b[0]=20;B2.b[1]=40;B2.b[2]=20;
    B2.b[3]=40;B2.b[4]=20;B2.b[5]=40;
    B2.b[6]=0;B2.b[7]=20;
    B3.a[0]=0;B3.a[1]=20;
    B3.a[2]=0;B3.a[3]=20;
    B3.a[4]=0;B3.a[5]=20;
    B3.a[6]=20;B3.a[7]=40;
    B3.b[0]=0;B3.b[1]=20;B3.b[2]=20;
    B3.b[3]=40;B3.b[4]=40;
    B3.b[5]=60;B3.b[6]=40;
    B3.b[7]=60;
    B4.a[0]=0;B4.a[1]=20;
    B4.a[3]=40;B4.a[2]=20;
    B4.a[4]=40;B4.a[5]=60;
    B4.a[6]=0;B4.a[7]=20;
    B4.b[0]=0;B4.b[1]=20;
    B4.b[2]=0;B4.b[3]=20;
    B4.b[4]=0;B4.b[5]=20;
    B4.b[6]=20;B4.b[7]=40;
    B1.next=&B2;B2.next=&B3;B3.next=&B4;B4.next=&B1;

    C1.a[0]=0;C1.a[1]=20;C1.a[2]=20;C1.a[3]=40;
    C1.a[4]=0;C1.a[5]=20;C1.a[6]=20;C1.a[7]=40;
    C1.b[0]=0;C1.b[1]=20;C1.b[2]=0;C1.b[3]=20;
    C1.b[4]=20;C1.b[5]=40;C1.b[6]=20;C1.b[7]=40;
    C1.next=&C1;

    D1.a[0]=0;D1.a[1]=20;D1.a[2]=0;D1.a[3]=20;
    D1.a[4]=0;D1.a[5]=20;D1.a[6]=20;D1.a[7]=40;
    D1.b[0]=0;D1.b[1]=20;D1.b[2]=20;D1.b[3]=40;
    D1.b[4]=40;D1.b[5]=60;D1.b[6]=20;D1.b[7]=40;
    D2.a[0]=20;D2.a[1]=40;D2.a[2]=0;D2.a[3]=20;
    D2.a[4]=20;D2.a[5]=40;D2.a[6]=40;D2.a[7]=60;
    D2.b[0]=20;D2.b[1]=40;D2.b[2]=40;D2.b[3]=60;
    D2.b[4]=40;D2.b[5]=60;D2.b[6]=40;D2.b[7]=60;
    D3.a[0]=20;D3.a[1]=40;D3.a[2]=40;
    D3.a[3]=60;D3.a[4]=40;D3.a[5]=60;
    D3.a[6]=40;D3.a[7]=60;
    D3.b[0]=20;D3.b[1]=40;D3.b[2]=0;
    D3.b[3]=20;D3.b[4]=20;D3.b[5]=40;
    D3.b[6]=40;D3.b[7]=60;
    D4.a[0]=0;D4.a[1]=20;D4.a[2]=20;
    D4.a[3]=40;D4.a[4]=40;D4.a[5]=60;
    D4.a[6]=20;D4.a[7]=40;
    D4.b[0]=0;D4.b[1]=20;
    D4.b[2]=0;D4.b[3]=20;
    D4.b[4]=0;D4.b[5]=20;
    D4.b[6]=20;D4.b[7]=40;
    D1.next=&D2;D2.next=&D3;D3.next=&D4;D4.next=&D1;

    E1.a[0]=0;E1.a[1]=20;E1.a[2]=20;E1.a[3]=40;
    E1.a[4]=20;E1.a[5]=40;E1.a[6]=40;E1.a[7]=60;
    E1.b[0]=20;E1.b[1]=40;E1.b[2]=20;E1.b[3]=40;
    E1.b[4]=0;E1.b[5]=20;E1.b[6]=0;E1.b[7]=20;
    E2.a[0]=0;E2.a[1]=20;E2.a[2]=0;
    E2.a[3]=20;E2.a[4]=20;E2.a[5]=40;
    E2.a[6]=20;E2.a[7]=40;
    E2.b[0]=0;E2.b[1]=20;E2.b[2]=20;
    E2.b[3]=40;E2.b[4]=20;E2.b[5]=40;
    E2.b[6]=40;E2.b[7]=60;
    E1.next=&E2;E2.next=&E1;

    F1.a[0]=0;F1.a[1]=20;F1.a[2]=20;F1.a[3]=40;
    F1.a[4]=20;F1.a[5]=40;F1.a[6]=40;F1.a[7]=60;
    F1.b[0]=0;F1.b[1]=20;F1.b[2]=0;F1.b[3]=20;
    F1.b[4]=20;F1.b[5]=40;F1.b[6]=20;F1.b[7]=40;
    F2.a[0]=40;F2.a[1]=60;F2.a[2]=40;
    F2.a[3]=60;F2.a[4]=20;F2.a[5]=40;
    F2.a[6]=20;F2.a[7]=40;
    F2.b[0]=0;F2.b[1]=20;F2.b[2]=20;
    F2.b[3]=40;F2.b[4]=20;F2.b[5]=40;
    F2.b[6]=40;F2.b[7]=60;
    F1.next=&F2;F2.next=&F1;

    G1.a[0]=0;G1.a[1]=20;G1.a[2]=0;G1.a[3]=20;
    G1.a[4]=0;G1.a[5]=20;G1.a[6]=0;G1.a[7]=20;
    G1.b[0]=0;G1.b[1]=20;G1.b[2]=20;G1.b[3]=40;
    G1.b[4]=40;G1.b[5]=60;G1.b[6]=60;G1.b[7]=80;
    G2.a[0]=0;G2.a[1]=20;G2.a[2]=20;
    G2.a[3]=40;G2.a[4]=40;G2.a[5]=60;
    G2.a[6]=60;G2.a[7]=80;
    G2.b[0]=0;G2.b[1]=20;G2.b[2]=0;
    G2.b[3]=20;G2.b[4]=0;G2.b[5]=20;
    G2.b[6]=0;G2.b[7]=20;
    G1.next=&G2;G2.next=&G1;
}

void start()  /*美化界面*/
{
    int n=0;
    struct board M1=A1,M2=C1,M3=D1,M4=E1;
    cleardevice();
    settime(new);
    setcolor(6);
    moveto(140,80);
    settextstyle(0,0,6);
    outtext("RUSSIAN");
    moveto(210,160);
    settextstyle(0,0,6);
    outtext("CUBE");

    setcolor(15);
    moveto(100,360);
    settextstyle(0,0,1);
    outtext("verb 1.0 2006.1.13    HARBIN INSITUTE OF TECHNOLOGY IN WEIHAI");
    rectangle(0,8,639,472);

    while(1)
    {
        setcolor(15);
        moveto(230,280);
        settextstyle(0,0,1);
        outtext("PRESS ANYKEY TO PLAY");
        DELAY(12);

        switch(n%4)
        {
            case 0:  draw(14,M1,0,10);break;
            case 1:  draw(11,M2,590,10);break;
            case 2:  draw(6,M3,0,410);break;
            case 3:  draw(9,M4,570,410);
        }

        setcolor(0);
        moveto(230,280);
        settextstyle(0,0,1);
        outtext("PRESS ANYKEY TO PLAY");
        DELAY(12);      

        switch(n%4)
        {
            case 0:  draw(0,M1,0,10);M1=*M1.next;n++;break;
            case 1:  draw(0,M2,590,10);M2=*M2.next;n++;break;
            case 2:  draw(0,M3,0,410);M3=*M3.next;n++;break;
            case 3:  draw(0,M4,570,410);M4=*M4.next;n++;
        }

        if(bioskey(1))  /*BIOS中断读取键盘输入*/
        {
            break;
        } 
    }    

    killtime();
    cleardevice(); 
}


void setgameboard()
{
    int i,j;
    for(i=0;i<=16;i++)
    {
        for(j=0;j<=14;j++)
            bandary[i][j]=0;
    }


    for(i=1;i<=14;i++)
        bandary[16][i]=1;  

    for(i=1;i<=15;i++)
        bandary[i][1]=bandary[i][14]=1;
}    
   
void draw(int c,struct board M,int x,int y)
{
    int i;
    setfillstyle(1,c);        
    for(i=0;i<=3;i++)
        bar(x+M.a[2*i]+2,y+M.b[2*i]+2,x+M.a[2*i+1]-2,y+M.b[2*i+1]-2); 
}



void decidepad(struct board * p,int *c)
{
    static n;
    randomize();
    n+=random(19);

    switch(n%19)
    {
        case 0:  *p=A1;*c=14;break;
        case 1:  *p=A2;*c=14;break;
        case 2:  *p=A3;*c=14;break;
        case 3:  *p=A4;*c=14;break;
        case 4:  *p=B1;*c=7; break;
        case 5:  *p=B2;*c=7; break;
        case 6:  *p=B3;*c=7; break;
        case 7:  *p=B4;*c=7; break;
        case 8:  *p=C1;*c=11;break;
        case 9:  *p=D1;*c=6; break;
        case 10: *p=D2;*c=6; break;
        case 11: *p=D3;*c=6; break;
        case 12: *p=D4;*c=6; break;
        case 13: *p=E1;*c=9; break;
        case 14: *p=E2;*c=9; break;
        case 15: *p=F1;*c=10;break;
        case 16: *p=F2;*c=10;break;
        case 17: *p=G1;*c=4; break;
        case 18: *p=G2;*c=4;
        }
}



int transform()
{
    struct board Y;
    int i,savex,flag=0;

    savex=x;
    Y=*X.next;

    while(1)
    {
        for(i=0;i<=3;i++)
        {
            if(BOARD(x,y+20,Y,i)==1)        /*变形要到的地方已经有格子在*/
            break;   
            else if(i==3)
            return 1;
        }     

        if(flag==0||flag==1||flag==3)  /*尝试右移动最多3次*/
        {
            x+=20;
            flag++;   
        }
        else if(flag==4)           /*尝试向左移动也是3次,但第一次把前面向右的弥补回来*/
        {
            x-=80;
            flag++;
        }
        else if(flag==5||flag==6)
        {
            x-=20;
            flag++;             
        } 
        else                /*最后尝试向上移动*/
        {    
            x=savex;
            y-=20;
        } 
    }
}

void congratulation(int i,int n)    /*消行后的鼓励,与消的行数有关*/
{
    switch(n)
    {  
        case 1:    setcolor(i);moveto(0,180);settextstyle(0,0,2);outtext("GOOD~");DELAY(1);break;
        case 2:    setcolor(i*2);moveto(0,180);settextstyle(0,0,2);outtext("GOGOGO!");DELAY(1);break;
        case 3:    setcolor(i*3);moveto(0,180);settextstyle(0,0,2);outtext("BRILLIANT!!");DELAY(1);break;
        case 4:    setcolor(i*i/2);moveto(0,180);settextstyle(0,0,2);outtext("PERFECT!!!");DELAY(1);
    }
}

int judge(int d,int i)
{
    if(BOARD(x+d,y,X,i)==1)
        return 1;
    else
        return 0;
}

void control(int *d)
{
    int i; 

    if(bioskey(1)) 
    { 
        key=bioskey(0);

        for(i=0;i<=3;i++)               /*向左右移动可能性的判断*/
        {
            if(judge(20,i))  
                right=1;

            if(judge(-20,i))
                left=1;                       
        }
        if(key==0x4b00&&left!=1)   /*处理向左右移动,同时设置移动标志*/
        {
            if(!flag1)
            {
                x-=20; 
                y-=20;
                flag1++;
                flag2++;
            } 
        }
        else if(key==0x4d00&&right!=1)                 
        {
            x+=20;
            if(!flag2)
            {
        
                y-=20;
                flag2++;
                flag1++;
            }
        }       
        else if(key==0x4800&&transform())     
            X=*X.next;         

        else if(key==0x5000) 
            *d=3;         
    }
}


void clear()
{
    int i,j,h;
    int full=0;
    int n=0;

    for(i=15;i>=1;i--) 
    {
        for(j=2;j<=13;j++)
        {
            if(bandary[i][j]==1)
                full++;          
        }

        if(full==12)                              /*当一行全部为"1"时,表示满了要消行*/
        {              
            getimage(200,90,440,390-(16-i)*20,buf);  
            putimage(200,110,buf,0);                         

            for(h=15-i;h<=13;h++)  
            { 
                for(j=2;j<=13;j++)
                {
                    bandary[15-h][j]=bandary[14-h][j];            
                }
            }    
            i++;
            n++;
        }       
        full=0; 
    }  
    congratulation(4,n);
    record=n;                 /*记录鼓励的语句号,以便擦去*/
}

void death()
{
    cleardevice();               
                 
    setcolor(6);
    moveto(150,80);                 
    settextstyle(0,0,5);
    outtext("GAME OVER");
                 
    moveto(300,180);
    settextstyle(0,0,1);
    outtext("PRESS ENTER TO REPLAY ESC TO QUIT");

    dead=0;
}


void game()
{
    int i,j;
    int dx,dy;
    int colr,colr1;
    int flagy;
    int score=0;

    size=imagesize(200,90,440,370);
    buf=malloc(size);

    settime(new);
    setgameboard();      
    setcolor(15);
    rectangle(199,89,441,391);    /*游戏框架*/

    decidepad(&X,&colr);                                           

    while(dead!=1)
    {      
        x=300;y=90;down=0;left=0;right=0;dx=480;dy=90;

        decidepad(&X1,&colr1);

        while(down!=1)
        {
            left=0;right=0;dly=8;
            flagy=y;
            draw(colr1,X1,dx,dy);         
            control(&dly);                          
            y+=20;
            if(y!=flagy)                  /*如果向下移动了,则恢复标志状态为可动*/
            {
                flag1=0;
                flag2=0;
            }

            draw(colr,X,x,y);      
            DELAY(dly);
            draw(0,X,x,y);

            congratulation(0,record);

            for(i=0;i<=3;i++)
            {
                if(BOARD(x,y+20,X,i)==1)
                {
                    draw(colr,X,x,y); 
                    down=1;

                    for(j=0;j<=3;j++)
                     BOARD(x,y,X,j)=1;
                }
            } 
        }          

        clear();

        draw(0,X1,dx,dy);       

        for(i=2;i<=13;i++)
        {
            if((bandary[2][i])==1)    /*一旦顶上有格子则判断为死亡*/
            dead=1;               
        }

        X=X1;                        /*将提示游戏板附给下一块出现的游戏板*/
        colr=colr1;
    }
    death();
    killtime();
}  

main()
{
    registerbgidriver(EGAVGA_driver);
    initgr();
    gamepad();
    INFORM                        /*个人信息:宏形式*/

    while(1)
    {           
        if(bioskey(1))          /*游戏总控制*/
        { 
            key=bioskey(0);

         if(key==0x1c0d)     
         {
            start();
            game();    
         }
         else if(key==0x011b)
         { 
            cleardevice(); 
            break;
         } 
        }
    }
}