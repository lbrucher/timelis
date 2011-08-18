// $Id: DlgStats.h,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#if !defined(AFX_DLGSTATS_H__AC797DFD_C184_4AB5_8A58_3EA5DB573C30__INCLUDED_)
#define AFX_DLGSTATS_H__AC797DFD_C184_4AB5_8A58_3EA5DB573C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStats.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStats dialog

class CDlgStats : public CDialog
{
// Construction
public:
	CDlgStats(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStats)
	enum { IDD = IDD_STATS };
	CListBox		m_Activities;
	int				m_nFilter;
	CString			m_sMonth;
	COleDateTime	m_dtFrom;
	COleDateTime	m_dtTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStats)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void RunStats( const COleDateTime& dtFrom,
					const COleDateTime& dtTo,
					const CDWordArray& projectIDs, const CDWordArray& activityIDs );

	// Generated message map functions
	//{{AFX_MSG(CDlgStats)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CStringArray m_itemDatas;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTATS_H__AC797DFD_C184_4AB5_8A58_3EA5DB573C30__INCLUDED_)
