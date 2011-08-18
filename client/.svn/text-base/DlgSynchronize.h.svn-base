// $Id: DlgSynchronize.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGSYNCHRONIZE_H__22441FA4_B225_4D19_8DC6_022DF3249FB2__INCLUDED_)
#define AFX_DLGSYNCHRONIZE_H__22441FA4_B225_4D19_8DC6_022DF3249FB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSynchronize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSynchronize dialog

class CDlgSynchronize : public CDialog
{
// Construction
public:
	CDlgSynchronize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSynchronize)
	enum { IDD = IDD_SYNCHRONIZE };
	BOOL	m_bGetProjects;
	BOOL	m_bSendTimesheet;
	int		m_nSendType;
	COleDateTime	m_SendAllTo;
	COleDateTime	m_SendAllFrom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSynchronize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSynchronize)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSYNCHRONIZE_H__22441FA4_B225_4D19_8DC6_022DF3249FB2__INCLUDED_)
