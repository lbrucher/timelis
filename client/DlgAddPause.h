// $Id: DlgAddPause.h,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#if !defined(AFX_DLGADDPAUSE_H__B4A66416_E1C8_4494_8D80_12DBDD99BB90__INCLUDED_)
#define AFX_DLGADDPAUSE_H__B4A66416_E1C8_4494_8D80_12DBDD99BB90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddPause.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPause dialog

class CDlgAddPause : public CDialog
{
// Construction
public:
	CDlgAddPause(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddPause)
	enum { IDD = IDD_ADDPAUSE };
	CString	m_sFrom;
	CString	m_sTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddPause)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddPause)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDPAUSE_H__B4A66416_E1C8_4494_8D80_12DBDD99BB90__INCLUDED_)
