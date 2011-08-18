// $Id: DlgMain.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGMAIN_H__F738D9D6_57B8_4406_9F3A_96D808BFE05E__INCLUDED_)
#define AFX_DLGMAIN_H__F738D9D6_57B8_4406_9F3A_96D808BFE05E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWorkDay;

class CDlgMain : public CDialog
{
public:
	CDlgMain(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CDlgMain)
	enum { IDD = IDD_MAIN };
	CButton	m_ButAddTask;
	CComboBox	m_Tasks;
	CEdit	m_TaskUntil;
	CEdit	m_TaskFrom;
	CEdit	m_PauseUntil;
	CEdit	m_PauseFrom;
	CStatic	m_DayLabel;
	CEdit	m_DayUntil;
	CEdit	m_DayFrom;
	CButton	m_ButPauses;
	CButton	m_ButManage;
	CButton	m_ButTasks;
	CButton	m_ButStartFinish;
	CButton	m_ButPauseResume;
	//}}AFX_DATA



	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMain)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnPauseResume();
	afx_msg void OnStartFinish();
	afx_msg void OnTasks();
	afx_msg void OnManage();
	afx_msg void OnButPauses();
	afx_msg void OnButAddTask();
	afx_msg LRESULT OnRefreshDayLabel( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void refreshDayLabel();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAIN_H__F738D9D6_57B8_4406_9F3A_96D808BFE05E__INCLUDED_)
