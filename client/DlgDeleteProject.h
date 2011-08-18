// $Id: DlgDeleteProject.h,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#if !defined(AFX_DLGDELETEPROJECT_H__F22436B4_D63A_4CCC_96AF_B9F7FDAB38C3__INCLUDED_)
#define AFX_DLGDELETEPROJECT_H__F22436B4_D63A_4CCC_96AF_B9F7FDAB38C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeleteProject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeleteProject dialog

class CDlgDeleteProject : public CDialog
{
// Construction
public:
	CDlgDeleteProject(CWnd* pParent = NULL);   // standard constructor

	long m_nSelectedProjectID;

// Dialog Data
	//{{AFX_DATA(CDlgDeleteProject)
	enum { IDD = IDD_DELPROJECT };
	CComboBox	m_Projects;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeleteProject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeleteProject)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDELETEPROJECT_H__F22436B4_D63A_4CCC_96AF_B9F7FDAB38C3__INCLUDED_)
