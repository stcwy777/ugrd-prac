/*****
*  The game of Snake implemented in Turboc
*
*  Author: Yun Wang 
*
*  This program was written in 2005 when I was a freshmen in CS. I wrote this
*  program to understand pointers and linked list in C. By then I did follow
*  any good coding standards and even worse no comments for this code. But it
*  is still fun to revisit it as it reminds me those old days. 
*  Just archive it for my own records:)
******/

#define LEN         sizeof(struct point)
#define DELAY(x)    while(t<x);t=0;
#define CONDITION   (p->x-a[i].x)*(p->x-a[i].x)+(p->y-a[i].y)*(p->y-a[i].y)<=r*r+10&&a[i].eat==0
#define CONDITION1  (l->x-p->x)*(l->x-p->x)+(l->y-p->y)*(l->y-p->y)<2*r
#define CONDITION2  p->x>=640||p->x<=10||p->y>=480||p->y<=0
#define INFORM         outtextxy(300,200,"QQ:170319080");\
                       outtextxy(300,250,"CLICK ENTER");\
                       outtextxy(400,400,"PRODUCED BY WANG YUN");
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <malloc.h>
#include <bios.h>

void start(void);
void gameset(void);
void snake(struct point*) ;
void randpoint(void);
void delete(void);
void draw(int,int,int,int);
void interrupt new(void);
void Settime(void interrupt (*fun)());
void killtime(void);
struct point * creat(void);
void interrupt (*old)();
int t;
int nuts,slenth,speed,score,num;
float r=9;
float key1,key2;
struct point *q;
struct point
{
    float x;
    float y;
    int eat;
    struct point *next;
}a[10];


initgr()
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

void Settime(void interrupt (*fun)())
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

void gameset()
{
    char c[2];
    closegraph();     
    printf("1.EASY\n2.NORMAL\n3.HARD\n");
    do
    {
        scanf("%s",c);
        switch(c[0]) 
        {
            case '1':  nuts=3;slenth=1;speed=5;break;
            case '2':  nuts=5;slenth=3;speed=3;break;
            case '3':  nuts=9;slenth=5;speed=1;break;
        }

    }while(c[0]>'3'||c[0]<'1');    

    initgr(); 
}
void start()
{
    float key;
    void  *buf;
    cleardevice();

    setbkcolor(0);
    Settime(new);

    setfillstyle(1,4);
    bar(1,10,637,319); 
    setfillstyle(1,6);
    bar(150,90,450,240);
    setfillstyle(1,9);
    bar(10,30,637,10);
    bar(1,10,20,319);
    bar(10,290,637,319);
    bar(618,319,637,30);

    setcolor(2);
    moveto(160,100);   
    settextstyle(0,0,6);
    outtext("EATING"); 
    moveto(190,180);   
    settextstyle(0,0,6);
    outtext("SNAKE");
    setcolor(15);
    moveto(100,400);
    settextstyle(0,0,1);
    outtext("verb 1.5 2006.1.8    HARBIN INSITUTE OF TECHNOLOGY IN WEIHAI");
    rectangle(0,8,639,472);

    while(1)
    { 
        setcolor(15);
        moveto(250,300); 
        settextstyle(0,0,1);
        outtext("PRESS ANYKEY TO PLAY"); 
        DELAY(12);
        setcolor(0);
        moveto(250,300);
        settextstyle(0,0,1);
        outtext("PRESS ANYKEY TO PLAY");      
        DELAY(12);
        if(bioskey(1))     
        {      
            gameset();   
            break;
        } 
    }    
    killtime();
}



struct point * creat()
{
    struct point *head,*p1,*p2;
    int i;
    p1=p2=head=(struct point*)malloc(LEN);
    for(i=0;i<=slenth;i++)
    {
        p1=(struct point*)malloc(LEN);
        p2->next=p1;
        p2=p1;
    }
    p2->next=NULL;

    return (head);
}

void draw(int c,int x,int y,int r)
{
    setcolor(c);
    setfillstyle(1,c);
    pieslice(x, y,0,360,r);
}

void delete()
{
    struct point *p1;
    while(q)
    {
        p1=q;
        q=q->next;
        free(p1);
    }
}

void pause()
{
    while(1)
    {
        if(bioskey(1))  
        {
            key1=bioskey(0);
            if(key1==0x011b)
                break;
        }
    }
}

void randpoint()
{
    int i;
    for(i=0;i<=nuts;i++)
    { 
        a[i].x=random(64)*10;
        a[i].y=random(48)*10;
        a[i].eat=0;
        draw(4,a[i].x,a[i].y,5);     
    }
}

void snake(struct point* q)
{
    int i,death=score=0;
    float d1=15,d2=0;
    struct point *p,*h,*l;

    for(p=q,i=0;p!=NULL;p=p->next,i++)
    {
        p->x=100+r*i;
        p->y=100;
    }

    Settime(new);
    rectangle(1,1,639,479);  
    printf("BONUS:0");

    while(1)
    {         
        if(num==nuts+1)
        {  
            num=0;
            randpoint();
        }

        for(p=q;p!=NULL;p=p->next)       
        {  
            draw(2,p->x,p->y,r);
            if(p->next==NULL)
            {
                draw(7,p->x+r/2,p->y+r/2,r/4);
                draw(7,p->x+r/2,p->y-r/2,r/4);
            } 
        }
        DELAY(speed);

        for(p=q;p!=NULL;p=p->next)
        {
            draw(0,p->x,p->y,r);
        }

        for(p=q;p->next!=NULL;p=p->next)
        {
            p->x=p->next->x;
            p->y=p->next->y;
        }

        if(bioskey(1))
        { 
            key1=bioskey(0);
            if(key1==0x4b00&&d2!=0) {d1=-15;d2=0;}
            else if(key1==0x4d00&&d2!=0) {d1=15;d2=0;}
            else if(key1==0x5000&&d1!=0) {d1=0;d2=15;}
            else if(key1==0x4800&&d1!=0) {d1=0;d2=-15;}
            else if(key1==0x011b)      {pause();}
        }
        p->x=p->x+d1;
        p->y=p->y+d2;

        for(i=0;i<=9;i++)
        {
            if(CONDITION)
            {
                draw(0,a[i].x,a[i].y,5);       
                a[i].eat=1;
                num++;
                score+=100;
                printf("\rBONUS:%d",score);             

                h=(struct point*)malloc(LEN);
                h->x=q->x;
                h->y=q->y;
                h->next=q;
                q=h;
            }
        }

        for(l=q;l->next->next->next!=NULL;l=l->next)
        if(CONDITION1)
        death=1;

        if(CONDITION2)    
        death=1;

        if(death)
        {
            cleardevice();
            setbkcolor(0);

            setcolor(6);
            moveto(150,80);                 
            settextstyle(0,0,5);
            outtext("GAME OVER");

            moveto(300,180);
            settextstyle(0,0,1);
            outtext("PRESS ENTER TO REPLAY ESC TO QUIT");

            delete();
            death=0;
            break;
        }                 
    }
    killtime();
}

main()
{
    registerbgidriver(EGAVGA_driver);
    initgr();
    INFORM
    while(1)
    {           
        if(bioskey(1))
        { 
            key2=bioskey(0);

            if(key2==0x1c0d) 
            {
                start();
                cleardevice();
                q=creat();        
                randpoint();
                snake(q);      
            }
            else if(key2==0x011b)
            { 
                cleardevice(); 
                break;
            } 
        }
    }
}