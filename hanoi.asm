;******************************************************************************************
; How computers play the Hanoi tower - a visualization of Hanoi tower solutions
; 
; This code was written in 2006 when I was learning IBM assembly language.
; I enjoyed writing codes like this, debuing and making it work. To be honest,
; I forgot a lot of the details when I revisited the code 10 years later in 2016,
; but I still remeber the happness at the moment of this program running on my 
; dell inspiron 3200 laptop.
;******************************************************************************************
.MODEL	SMALL
;******************************************************************************************
;DATA STUCTURE					;定义dish结构体表示盘,tower结构体表示塔
tower	STRUC
	tX	dw	?			;塔的位置坐标
	tY	dw	?
	tBottom	dw	?			;塔的长度=原长-盘的数量*10,用于控制盘在某塔上向下移动的极限坐标
tower	ENDS

dish	STRUC
	pX	dw	?			;盘的横坐标
	pY	dw	?			;盘的纵坐标
	pcolor	db	?			;盘的颜色
	psize	dw	?			;盘的长度
dish	ENDS
;******************************************************************************************
;-------------------------------
mQuit	MACRO
	LOCAL	continue
;宏功能:用与退出程序
	mov	ah,1				;BIOS键盘中断,获取缓冲区键扫描值
	int	16h
	cmp	ah,01				;是否按下了ESC
	jnz	continue				
	jmp	exit				;是则退出图形模式
continue:	
	ENDM
;-------------------------------
mRline	MACRO	X,Y,Endl,color
	LOCAL	rot1
;宏功能:画水平线
	IRP	reg,<cx,ax,bx>			;保存寄存器
	push	reg
	ENDM
	mov	cx,X				;存像素坐标到CX=X,DX=Y
	mov	dx,Y

rot1:
	mov	ah,0ch				;调用BIOS 10H中断0CH功能写像素
	mov	al,color			;颜色
	mov	bh,0				;页码
	int	10h
	inc	cx				;水平上下一像素
	cmp	cx,Endl				;是否到最大长度
	jnz	rot1				;否则继续写入像素
	IRP	reg,<bx,ax,cx>			;返回寄存器值
	pop	reg
	ENDM
	ENDM
;--------------------------------
mCline	MACRO	X,Y,Endh,color
	LOCAL	rot2
;宏功能:画垂直线(移动DX值,其他与上同)
	IRP	reg,<cx,ax,bx>
	push	reg
	ENDM
	mov	cx,X
	mov	dx,Y
rot2:
	mov	ah,0ch
	mov	al,color
	mov	bh,0
	int	10h
	inc	dx
	cmp	dx,Endh
	jnz	rot2
	IRP	reg,<bx,ax,cx>
	pop	reg
	ENDM
	ENDM
;---------------------------------
mDrawt	MACRO	
;宏功能:画塔
	mCline	towera.tX,towera.tY,190,8	;画一垂直线表示塔
	mCline	towerb.tX,towerb.tY,190,8
	mCline	towerc.tX,towerc.tY,190,8
	ENDM
;---------------------------------
mPrep	MACRO
;宏功能:初始化画面
	mDrawt					;调用画塔宏
redraw:
	mov	[bx].pY,ax			;画最底层盘
	mRline	[bx].pX,[bx].pY,[bx].psize,[bx].pcolor
	sub	bx,7				;指针指向上一层盘
	sub	[si].tBottom,10			;盘的长度减10
	sub	ax,10				;移动横坐标到上层盘位置
	loop	redraw				;循环 ,直到指定数量盘画完
	ENDM
;---------------------------------
mUpDn	MACRO	speedc,bottom
	LOCAL	rotate1
;宏功能:上下移动盘
rotate1:
	call	flash				;动画效果函数
	sub	[bx].pY,speedc			;修正纵坐标
	mov	cx,bottom			
	cmp	[bx].pY,cx			;是否达到目的地	
	jnz	rotate1				;否则继续
	ENDM
;---------------------------------
mLtRt	MACRO	speedh
	LOCAL	rotate2,again2
;宏功能:左右移动盘
rotate2:
	call	flash
	add	[bx].pX,speedh			;修正横坐标
	add	[bx].psize,speedh		;横坐标改变修正盘长度
	mov	cx,[bx].psize	
	add	cx,[bx].pX
	sar	cx,1				;计算盘的中心位置:(首横坐标+尾横坐标)/2
	cmp	cx,[di].tX			;中心是否和塔重合
	jnz	rotate2				;否则继续移动
	ENDM
;----------------------------------
mMove	MACRO	
	LOCAL	goright,go
;宏功能:实现递归中的盘移动(整合了上面的移动宏)
	mUpDn	1,20				;向上移动到塔顶
	add	[si].tBottom,10			;增加塔的长度,已移走一盘
	mov	cx,[si].tX			;确定水平移动方向			
	cmp	cx,[di].tX
	jl	goright
	mLtRt	-2				;右向左
	jmp	go
goright:
	mLtRt	2				;左向右		
go:
	mUpDn	-1,[di].tBottom			;向下移动到当前塔底
	sub	[di].tBottom,10			;塔上移来一盘,增加纵坐标
	mRline	[bx].pX,[bx].pY,[bx].psize,[bx].pcolor	;由于采用画擦法,最后补上一次作图
	ENDM	
;--------------------------------
mPuts	MACRO	string
;宏功能:输出字符串
	lea	dx,string			;21中断9功能	
	mov	ah,9
	int	21h
	ENDM
;---------------------------------
mGetch	MACRO	char
;宏功能:获取字符
rewrite:
	mov	ah,1
	int	21h
	cmp	al,30h				;比0小,非法输入
	jl	error
	cmp	al,39h			
	jg	error				;比9大,非法输入
	sub	al,30h				
	jmp	ok				;合法输入,调整到数字后存入内存单元	
error:
	mPuts	MEG2
	mov	ah,7				;无回显接受一字符
	int	21h		
	cmp	al,13				;是回车则继续输入
	jz	rewrite
	jmp	exit				;否则退出程序
ok:
	mov	num,al
	ENDM
;********************************************************************************
.STACK	100H
;********************************************************************************
.DATA
MEG1	db	'HOW MANY DISHES?(1-9)',13,10,'$'
MEG2	db	13,10,'ERROR:ONLY NUM ALLOWED(enter to rewrite)',13,10,'$'
MEG3	db	'THANK YOU FOR USEING',13,10,'$'
num	db	?
large	db	7				;一个dish结构体的字节长度
first	dw	?				;保存第一个盘的地址用与比较
save	dw	?				;保存最底层盘,用以初始化画面后从最底盘开始递归
save1	dw	?				;保存1CH中断向量程序入口地址
save2	dw	?
TMcount	dw	0				;记时器
bindary	dw	?				;移动中的边界变量
towera	tower<40,25,190>			;初始化结构变量
towerb	tower<160,25,190>
towerc	tower<280,25,190>
dish1	dish<36,0,1,45>
dish2	dish<32,0,2,49>
dish3	dish<28,0,3,53>
dish4	dish<24,0,4,56>
dish5	dish<20,0,5,60>
dish6	dish<16,0,6,64>
dish7	dish<12,0,7,68>
dish8	dish<8,0,8,72>
dish9	dish<4,0,9,76>
;********************************************************************************
.CODE
;--------------------------------------------------------------------------------
main	proc	far
	mov	ax,@data			;代码段从寄存器
	mov	ds,ax

	call	settime				;设置新的时钟中断向量例行程序地址
	mPuts	MEG1				;欢迎辞
	mGetch	num				;输入并存入内存单元

	mov	ah,0h				;设置图形模式
	mov	al,13h				;320 X 200 256色
	int	10h			

	lea	bx,dish1
	mov	first,bx			;保存第一个dish结构体地址,递归结束判断中使用

	mov	al,num
	dec	al				;存入AX用与计算最后结构体下标
	mul	large
	add	bx,ax				;指向最底端的dish
	mov	save,bx				;保存最底端dish结构体地址,用于递归开始
	mov	cl,num				;存入CX用与初始化时绘盘次数
	mov	ch,0
	mov	ax,190				;底端dish的纵坐标

	mPrep					;调用宏绘制开始画面
	lea	si,towera			;SI指向塔A
	lea	di,towerc			;DI指向塔C
	lea	ax,towerb			;AX指向塔B
	mov	bx,save				;BX指向最底盘

	call	hanoi				;调用HANOI递归函数
	call	kiltime				;恢复1CH中断向量例行程序地址
exit:
	mov	ah,0h				;设置文本模式
	mov	al,3h
	int	10h
	mPuts	MEG3				;打印结束辞

	mov	ah,4ch				;返回操作系统
	int	21h
main	endp	
;------------
delay	proc	near				;新的中断函数
	mov	ax,@data			;设置数据段	
	mov	ds,ax	
	sti	
	inc	TMcount				;记数器+1
	iret
delay	endp
;-----------
settime	proc	near
	mov	al,1ch				;获取中断号
	mov	ah,35h				;21H 35H功能获取中断例行程序地址存入ES,BX
	int	21h				
	mov	save1,es			;保存程序段地址	
	mov	save2,bx			;保存程序偏移地址
	push	ds				;保存数据段

	mov	ax,seg delay			;AX存入新函数段地址
	mov	dx,offset delay			;DX存入新函数有效地址
	mov	ds,ax				;存入DS段地址
	mov	al,1ch				;1CH号功能存入新的中断例行程序地址到1CH中断号中
	mov	ah,25h			
	int	21h			
	pop	ds				;返回数据段
	ret
settime	endp
;-----------
kiltime	proc	near
	mov	ax,save1
	mov	ds,save1			;设置原中断向量
	mov	dx,save2
	mov	al,1ch				;调用1CH功能设置
	mov	ah,25h
	int	21h
	ret
kiltime	endp
;-----------
flash	proc	near				;采用画擦法
	mov	TMcount,0			;新的记时
	mRline	[bx].pX,[bx].pY,[bx].psize,[bx].pcolor	;画图
	mQuit					;接受ESC退出
again:
	cmp	TMcount,1			;延迟功能
	jl	again
	mRline	[bx].pX,[bx].pY,[bx].psize,0	;擦图,采用背景色实现	
	mDrawt					;画塔防止塔的部分被擦
	ret	
flash	endp
;-----------
hanoi	proc	near
	cmp	bx,first			;是否到了第一个盘
	jnz	deliver				;是则从塔A移动到塔B
	mMove	
	jmp	return				;结束递归
		
deliver:

	IRP	reg,<bx,si,ax,di>		;保存上一函数参数
	push	reg
	ENDM

	xchg	ax,di				;交换寄存器内容实现参数传递
	sub	bx,7				;上面的盘

	call	hanoi				;递归调用,即要移动当天盘从A到C,只要移动上面的盘从A借助C到B

	IRP	reg,<di,ax,si,bx>		;返回参数
	pop	reg
	ENDM

	mMove					;上面的盘成功移走,移动当前盘到目的地	
	INT	3H
	IRP	reg,<bx,si,ax,di>
	push	reg
	ENDM
	xchg	si,ax				;参数传递,实现上面的盘从B借助A到C
	sub	bx,7
	
	call	hanoi				;递归移动上面的盘到目的地
	
	IRP	reg,<di,ax,si,bx>
	pop	reg
	ENDM
return:
	ret					
hanoi	endp
;***************************************************************************************
end	