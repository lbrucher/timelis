#if !defined(AFX_DLGSHOWEVENT_H__CAB39CB5_B6BA_46D0_97A9_394B3DB8AF2D__INCLUDED_)
#define AFX_DLGSHOWEVENT_H__CAB39CB5_B6BA_46D0_97A9_394B3DB8AF2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShowEvent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgShowEvent dialog

class CDlgShowEvent : public CDialog
{
// Construction
public:
	CDlgShowEvent(CWnd* pParent = NULL);   // standard constructor

	long m_eventId;

// Dialog Data
	//{{AFX_DATA(CDlgShowEvent)
	enum { IDD = IDD_SHOWEVENT };
	CEdit	m_Text;
	CComboBox	m_SnoozeTime;
	CTime	m_rescheduleDate;
	CTime	m_rescheduleTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShowEvent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShowEvent)
	afx_msg void OnDelete();
	afx_msg void OnReschedule();
	virtual BOOL OnInitDialog();
	afx_msg void OnSnooze();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AddSnoozeTime( const char* text, DWORD minutes );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHOWEVENT_H__CAB39CB5_B6BA_46D0_97A9_394B3DB8AF2D__INCLUDED_)
