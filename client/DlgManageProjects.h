#if !defined(AFX_DLGMANAGEPROJECTS_H__6E55514C_9DAC_4380_A9DA_C564C3071D1A__INCLUDED_)
#define AFX_DLGMANAGEPROJECTS_H__6E55514C_9DAC_4380_A9DA_C564C3071D1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManageProjects.h : header file
//

class CRecActivity;


class CDlgManageProjects : public CDialog
{
// Construction
public:
	CDlgManageProjects(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgManageProjects)
	enum { IDD = IDD_PROJECTS };
	CButton	m_ButRenActivity;
	CButton	m_ButRenProject;
	CButton	m_ButEnableActivity;
	CButton	m_ButDelProject;
	CButton	m_ButDelActivity;
	CButton	m_ButAddActivity;
	CListBox	m_Activities;
	CListBox	m_Projects;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManageProjects)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManageProjects)
	afx_msg void OnAddProject();
	afx_msg void OnDelproject();
	afx_msg void OnAddactivity();
	afx_msg void OnDelactivity();
	afx_msg void OnEnableactivity();
	afx_msg void OnSelchangeProjects();
	afx_msg void OnSelchangeActivities();
	virtual BOOL OnInitDialog();
	afx_msg void OnRenproject();
	afx_msg void OnRenactivity();
	afx_msg void OnDblclkProjects();
	afx_msg void OnDblclkActivities();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void refreshProjectsList();
	void refreshActivitiesList();
	void updateButtonsState();

	long getSelectedProjectID();
	long getSelectedActivityID();

	void buildActivityName( const CRecActivity& rec, CString& s );


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANAGEPROJECTS_H__6E55514C_9DAC_4380_A9DA_C564C3071D1A__INCLUDED_)
