// $Id: DlgAddEditTask.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGADDEDITTASK_H__6CCA013F_ABBE_4C95_8985_5EF8F492EB08__INCLUDED_)
#define AFX_DLGADDEDITTASK_H__6CCA013F_ABBE_4C95_8985_5EF8F492EB08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddEditTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddEditTask dialog

class CDlgAddEditTask : public CDialog
{
// Construction
public:
	CDlgAddEditTask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddEditTask)
	enum { IDD = IDD_EDITTASK };
	CStatic	m_TimeInfoLabel;
	CComboBox	m_Projects;
	CString	m_sTime;
	CString	m_sOfficialDescription;
	CString	m_sPrivateDescription;
	//}}AFX_DATA

	long m_nSelectedActivityID;
	long m_nTaskTime;
	bool m_bAllowNoTime;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddEditTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddEditTask)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CStringArray m_itemDatas;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDEDITTASK_H__6CCA013F_ABBE_4C95_8985_5EF8F492EB08__INCLUDED_)
