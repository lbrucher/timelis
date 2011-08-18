// $Id: MainFrm.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#if !defined(AFX_MAINFRM_H__3646661B_3A42_42C1_B1E3_E4B35FF9A1E1__INCLUDED_)
#define AFX_MAINFRM_H__3646661B_3A42_42C1_B1E3_E4B35FF9A1E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWorkDay;


class CMainFrame : public CFrameWnd
{

public:
	CMainFrame();
	virtual ~CMainFrame();


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	DECLARE_DYNAMIC(CMainFrame)

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg LRESULT OnTrayNotify(WPARAM, LPARAM);
	afx_msg LRESULT OnPausesChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnDlgManage(WPARAM, LPARAM);
	afx_msg LRESULT OnDlgReporting(WPARAM, LPARAM);
	afx_msg void OnAbout();
	afx_msg void OnReporting();
	afx_msg void OnManaging();
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPopuprclickPause();
	afx_msg void OnReopenDay();
	afx_msg void OnPopuprclickStatistics();
	afx_msg void OnPopuprclickSynchronize();
	afx_msg void OnPopuprclickOptions();
	afx_msg void OnPopuprclickOptionsProjects();
	afx_msg void OnUpdatePopuprclickSynchronize(CCmdUI* pCmdUI);
	afx_msg void OnPopuprclickEvents();
	afx_msg void OnPopuprclickAddevent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void OnMain();

	bool AddToTray();
	bool RemoveFromTray();
	void UpdateTooltip();
	void scheduleNextEvent();
	void handleNextEvent();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3646661B_3A42_42C1_B1E3_E4B35FF9A1E1__INCLUDED_)
