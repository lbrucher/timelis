// $Id: ChildView.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_CHILDVIEW_H__C134E571_2C5B_4A61_A9BA_B99C7959DE6A__INCLUDED_)
#define AFX_CHILDVIEW_H__C134E571_2C5B_4A61_A9BA_B99C7959DE6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__C134E571_2C5B_4A61_A9BA_B99C7959DE6A__INCLUDED_)
