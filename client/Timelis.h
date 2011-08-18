// $Id: Timelis.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
// Timelis.h : main header file for the TIMELIS application
//

#if !defined(AFX_TIMELIS_H__CFEC5185_7648_4995_8EF3_A940F00C29E2__INCLUDED_)
#define AFX_TIMELIS_H__CFEC5185_7648_4995_8EF3_A940F00C29E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimelisApp:
// See Timelis.cpp for the implementation of this class
//

class CTimelisApp : public CWinApp
{
public:
	CTimelisApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimelisApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CTimelisApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMELIS_H__CFEC5185_7648_4995_8EF3_A940F00C29E2__INCLUDED_)
