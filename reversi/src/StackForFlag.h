// StackForFlag.h: interface for the CStackForFlag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKFORFLAG_H__17AFB126_150E_464A_825C_81E8D1A88642__INCLUDED_)
#define AFX_STACKFORFLAG_H__17AFB126_150E_464A_825C_81E8D1A88642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStackForFlag  
{
public:
	void Pop(int &item);
	void Push(int item);
	CStackForFlag();
	virtual ~CStackForFlag();

private:
	int m_flags[20];
	int m_bottom;
	int m_top;
};

#endif // !defined(AFX_STACKFORFLAG_H__17AFB126_150E_464A_825C_81E8D1A88642__INCLUDED_)
