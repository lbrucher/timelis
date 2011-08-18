// $Id: DlgTasks.h,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#if !defined(AFX_DLGTASKS_H__EFECA146_594C_4D18_92AA_1CBD6B7A1E98__INCLUDED_)
#define AFX_DLGTASKS_H__EFECA146_594C_4D18_92AA_1CBD6B7A1E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWorkDay;


class CDlgTasks : public CDialog
{
// Construction
public:
	CDlgTasks(CWorkDay*, const COleDateTime* pDT, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTasks)
	enum { IDD = IDD_TASKS };
	CStatic	m_FinishedTimeLabel;
	CButton	m_ButCancel;
	CButton	m_ButOK;
	CListBox	m_Tasks;
	CStatic	m_UnallocatedTaskTime;
	CStatic	m_TotalTaskTime;
	CStatic	m_DaySoFar;
	CStatic	m_DayStarted;
	CEdit	m_Finished;
	CStatic	m_FinishedLabel;
	CButton	m_EditTask;
	CButton	m_DeleteTask;
	CString	m_sFinished;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTasks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTasks)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddtask();
	afx_msg void OnDeletetask();
	afx_msg void OnEdittask();
	afx_msg void OnSelchangeTasks();
	afx_msg void OnDblclkTasks();
	virtual void OnOK();
	afx_msg void OnKillfocusFinished();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void RefreshTasks();


	CWorkDay* m_pDay;
//	bool m_bFinishDay;
	const COleDateTime* m_pdtFinish;
	long m_nTotalWorkTime;
	long m_nTotalTasksTime;
	long m_nTasks;
	bool m_bHasTaskWithNoTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTASKS_H__EFECA146_594C_4D18_92AA_1CBD6B7A1E98__INCLUDED_)
