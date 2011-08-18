// $Id: DlgSelectActivities.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGSELECTACTIVITIES_H__9CEDB2B1_C76C_4E4A_95A2_B116F2E957FA__INCLUDED_)
#define AFX_DLGSELECTACTIVITIES_H__9CEDB2B1_C76C_4E4A_95A2_B116F2E957FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectActivities dialog

class CDlgSelectActivities : public CDialog
{
// Construction
public:
	CDlgSelectActivities(CWnd* pParent = NULL);   // standard constructor

	CDWordArray m_projectIDs;
	CDWordArray m_activityIDs;


// Dialog Data
	//{{AFX_DATA(CDlgSelectActivities)
	enum { IDD = IDD_SELECTACTIVITIES };
	CButton	m_CtrlShowDisabled;
	CListBox	m_Activities;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectActivities)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectActivities)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowdisabledactivities();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void RefreshActivities();

	CStringArray m_itemDatas;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
