// $Id: DlgPauses.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGPAUSES_H__9BA41861_5B49_41B2_A7E0_6AB0397CBEFB__INCLUDED_)
#define AFX_DLGPAUSES_H__9BA41861_5B49_41B2_A7E0_6AB0397CBEFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgPauses : public CDialog
{
// Construction
public:
	CDlgPauses(long sheeterID, CWnd* pParent = NULL);   // standard constructor

	bool wasModified()		{ return m_bModified; }

// Dialog Data
	//{{AFX_DATA(CDlgPauses)
	enum { IDD = IDD_PAUSES };
	CListBox	m_Pauses;
	CString	m_sLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPauses)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPauses)
	afx_msg void OnAddnew();
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void refreshPauses();

	long m_nSheeterID;
	bool m_bModified;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAUSES_H__9BA41861_5B49_41B2_A7E0_6AB0397CBEFB__INCLUDED_)
