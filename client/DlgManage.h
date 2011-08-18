// $Id: DlgManage.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#if !defined(AFX_DLGMANAGE_H__01D13757_7305_4B14_ABC3_B258A10AA15B__INCLUDED_)
#define AFX_DLGMANAGE_H__01D13757_7305_4B14_ABC3_B258A10AA15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecTimeSheet.h"



class CDlgManage : public CDialog
{
// Construction
public:
	CDlgManage(CWnd* pParent = NULL);   // standard constructor

	bool m_bReporting;


// Dialog Data
	//{{AFX_DATA(CDlgManage)
	enum { IDD = IDD_MANAGE };
	CEdit	m_CtrlMonthYear;
	CComboBox	m_MonthNames;
	CButton			m_ButFilterActivities;
	CButton			m_ButDelDay;
	CButton			m_Pauses;
	CButton			m_CtrlFilterTypeMonth;
	CButton			m_CtrlFilterTypePeriod;
	CButton			m_ButSearch;
	CDateTimeCtrl	m_CtrlPeriodTo;
	CDateTimeCtrl	m_CtrlPeriodFrom;
	CButton			m_NewDay;
	CButton			m_EditTask;
	CButton			m_DelTask;
	CButton			m_AddTask;
	CListBox		m_Tasks;
	CListBox		m_Days;
	COleDateTime	m_PeriodFrom;
	COleDateTime	m_PeriodTo;
	int				m_nReportingDay;
	CString			m_sReportingDayCustomValue;
	CString			m_sSchedule;
	int				m_nFilterDay;
	int				m_nFilterActivities;
	int		m_nMonthYear;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManage)
	afx_msg void OnSelchangeDays();
	afx_msg void OnAddtask();
	afx_msg void OnEdittask();
	afx_msg void OnDeltask();
	afx_msg void OnSearch();
	afx_msg void OnDayset();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTasks();
	afx_msg void OnDblclkTasks();
	afx_msg void OnNewday();
	afx_msg void OnPauses();
	afx_msg void OnDelday();
	afx_msg void OnShowStats();
	afx_msg void OnSelectActivities();
	afx_msg void OnSetfocusPeriodFrom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusPeriodTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusMonth();
	afx_msg void OnSetfocusDayCustomvalue();
	afx_msg void OnSetfocusMonthNames();
	afx_msg void OnSetfocusMonthYear();
	afx_msg void OnReporting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void refreshDays( CRecTimeSheet& query );
	void refreshTasks( CRecTimeSheet* pRec );
//	void refreshStats( CRecTimeSheet& query );

	bool BuildQuery( CString& sQuery );

	void clearDay();
	void setDay( long id );
	int  addDay( CRecTimeSheet& rec );
	CString buildDayString( CRecTimeSheet& rec );

	long m_nTotalWorkTime;
	long m_nTotalTasksTime;
	long m_nTasks;
	bool m_bHasTaskWithNoTime;
	COleDateTime m_dtCurrentDay;
	CDWordArray m_selectedActivityIDs;

	CDWordArray m_savedActivityIDs;
	CDWordArray m_savedProjectIDs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANAGE_H__01D13757_7305_4B14_ABC3_B258A10AA15B__INCLUDED_)
