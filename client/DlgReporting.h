// $Id: DlgReporting.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#if !defined(AFX_DLGREPORTING_H__06A2EB8A_8B8D_4F28_94C5_FF16E1100A47__INCLUDED_)
#define AFX_DLGREPORTING_H__06A2EB8A_8B8D_4F28_94C5_FF16E1100A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CReporting;


class CDlgReporting : public CDialog
{
// Construction
public:
	CDlgReporting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgReporting)
	enum { IDD = IDD_REPORTING };
	CComboBox	m_Templates;
	CComboBox	m_MonthNames;
	CListBox		m_Activities;
	int				m_nFilter;
	COleDateTime	m_PeriodFrom;
	COleDateTime	m_PeriodTo;
	BOOL	m_bShowDisabledActivities;
	int		m_nMonthYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReporting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgReporting)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusPeriodFrom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusPeriodTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowdisabledactivities();
	afx_msg void OnView();
	afx_msg void OnSave();
	afx_msg void OnSetfocusMonthName();
	afx_msg void OnSetfocusMonthYear();
	afx_msg void OnManage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CStringArray m_itemDatas;

	void RefreshActivities();
	boolean BuildReport( CReporting& report );
	bool GetSelectedPeriod( COleDateTime& from, COleDateTime& to );
	bool GetSelectedActivities( CDWordArray& selectedActivityIDs );
	bool GetSelectedTemplate( CString& filename );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPORTING_H__06A2EB8A_8B8D_4F28_94C5_FF16E1100A47__INCLUDED_)
