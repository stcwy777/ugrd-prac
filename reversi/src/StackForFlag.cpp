// StackForFlag.cpp: implementation of the CStackForFlag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BWview.h"
#include "StackForFlag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStackForFlag::CStackForFlag()
{
	m_top=0;
	m_bottom=0;
}

CStackForFlag::~CStackForFlag()
{

}

void CStackForFlag::Push(int item)
{
	m_flags[m_top]=item;
	m_top++;
}

void CStackForFlag::Pop(int &item)
{
	item=m_flags[m_top-1];
	m_top--;
}
