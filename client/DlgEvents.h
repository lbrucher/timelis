#if !defined(AFX_DLGEVENTS_H__4328F32E_3C3F_47AB_B45D_9C8CD12AA303__INCLUDED_)
#define AFX_DLGEVENTS_H__4328F32E_3C3F_47AB_B45D_9C8CD12AA303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEvents.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEvents dialog

class CDlgEvents : public CDialog
{
// Construction
public:
	CDlgEvents(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEvents)
	enum { IDD = IDD_EVENTS };
	CButton	m_ButModify;
	CButton	m_ButDelete;
	CButton	m_ButAdd;
	CListBox	m_Events;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEvents)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEvents)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnModify();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEvents();
	afx_msg void OnDblclkEvents();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void refreshList();
	void updateButtonsState();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEVENTS_H__4328F32E_3C3F_47AB_B45D_9C8CD12AA303__INCLUDED_)
