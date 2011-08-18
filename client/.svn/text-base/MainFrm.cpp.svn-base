// $Id: MainFrm.cpp,v 1.5 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "WorkDay.h"
#include "MainFrm.h"
#include "RecTimeSheet.h"
#include "RecProject.h"
#include "RecPauses.h"
#include "RecEvent.h"
#include "DlgAbout.h"
#include "DlgMain.h"
#include "DlgTasks.h"
#include "DlgManage.h"
#include "DlgReporting.h"
#include "DlgAddProject.h"
#include "DlgDeleteProject.h"
#include "DlgStats.h"
#include "DlgSynchronize.h"
#include "DlgOptions.h"
#include "DlgWait.h"
#include "DlgManageProjects.h"
#include "DlgEvents.h"
#include "DlgShowEvent.h"
#include "DlgEditEvent.h"
#include "Synchronize.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
	ON_MESSAGE(WM_PAUSESCHANGED, OnPausesChanged)
	ON_MESSAGE(WM_DLG_MANAGE, OnDlgManage)
	ON_MESSAGE(WM_DLG_REPORTING, OnDlgReporting)
	ON_COMMAND(ID_POPUPRCLICK_ABOUT, OnAbout)
	ON_COMMAND(ID_POPUPRCLICK_REPORTING, OnReporting)
	ON_COMMAND(ID_POPUPRCLICK_MANAGING, OnManaging)
	ON_COMMAND(ID_POPUPRCLICK_EXIT, OnExit)
	ON_WM_TIMER()
	ON_COMMAND(ID_POPUPRCLICK_REOPENDAY, OnReopenDay)
	ON_COMMAND(ID_POPUPRCLICK_STATISTICS, OnPopuprclickStatistics)
	ON_COMMAND(ID_POPUPRCLICK_SYNCHRONIZE, OnPopuprclickSynchronize)
	ON_COMMAND(ID_POPUPRCLICK_OPTIONS, OnPopuprclickOptions)
	ON_COMMAND(ID_POPUPRCLICK_OPTIONS_PROJECTS, OnPopuprclickOptionsProjects)
	ON_UPDATE_COMMAND_UI(ID_POPUPRCLICK_SYNCHRONIZE, OnUpdatePopuprclickSynchronize)
	ON_COMMAND(ID_POPUPRCLICK_EVENTS, OnPopuprclickEvents)
	ON_COMMAND(ID_POPUPRCLICK_ADDEVENT, OnPopuprclickAddevent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#define TIMER_ID_TOOLTIP		66
#define TIMER_ID_START_EVENTS	67
#define TIMER_ID_NEXT_EVENT		68


// ////////////////////////////////////////////////////////////////////////////
//
CMainFrame::CMainFrame()
{
}


// ////////////////////////////////////////////////////////////////////////////
//
CMainFrame::~CMainFrame()
{
	CWorkDay::shutdown();
}


// ////////////////////////////////////////////////////////////////////////////
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWorkDay::initCurrentDay();

	if (!AddToTray())
		return -1;

	UpdateTooltip();

	// Update tooltip info every minute
	SetTimer(TIMER_ID_TOOLTIP, 60000, NULL);

	// Delay the start of the event mechanism
	SetTimer(TIMER_ID_START_EVENTS, 2000, NULL);

	return 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnClose()
{
	KillTimer(TIMER_ID_TOOLTIP);
	KillTimer(TIMER_ID_START_EVENTS);
	KillTimer(TIMER_ID_NEXT_EVENT);

	// Remove icon from shelltray
	RemoveFromTray();

	CFrameWnd::OnClose();
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


// ////////////////////////////////////////////////////////////////////////////
//
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// ////////////////////////////////////////////////////////////////////////////
//
bool CMainFrame::AddToTray()
{
	NOTIFYICONDATA tnid;
	HICON hIcon = LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_TRAY) );
	::LoadString(AfxGetResourceHandle(), IDS_TRAYTIP, tnid.szTip, sizeof(tnid.szTip));

	tnid.cbSize				= sizeof(NOTIFYICONDATA);
	tnid.hWnd				= m_hWnd;
	tnid.uID				= 1;
	tnid.uFlags				= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnid.uCallbackMessage	= WM_TRAYNOTIFY;
	tnid.hIcon				= hIcon;

	bool bOk = bool( Shell_NotifyIcon(NIM_ADD, &tnid) == TRUE );

	if (hIcon)
		DestroyIcon(hIcon);

	return bOk;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CMainFrame::RemoveFromTray()
{
	NOTIFYICONDATA tnid;

	tnid.cbSize				= sizeof(NOTIFYICONDATA);
	tnid.hWnd				= m_hWnd;
	tnid.uID				= 1;

	return bool( Shell_NotifyIcon(NIM_DELETE, &tnid) == TRUE );
}


// ////////////////////////////////////////////////////////////////////////////
//
LRESULT CMainFrame::OnTrayNotify( WPARAM wParam, LPARAM lParam )
{
	switch(lParam)
	{
		case WM_LBUTTONDOWN:
		{
			if (GetLockedWindow() == NULL)
				OnMain();
			else if (::IsWindow(GetLockedWindow()->m_hWnd))
				GetLockedWindow()->SetForegroundWindow();
			return 0;
		}

		case WM_RBUTTONDOWN:
		{
			if (GetLockedWindow() == NULL)
			{
				HMENU hMenu = LoadMenu(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_RCLICK));
				if (hMenu)
				{
					HMENU hMenuPopup = GetSubMenu(hMenu,0);
					if (hMenuPopup)
					{
						POINT pt;
						::GetCursorPos(&pt);

						::SetForegroundWindow(m_hWnd);

						TrackPopupMenu( hMenuPopup,
										TPM_LEFTALIGN|TPM_BOTTOMALIGN|TPM_RIGHTBUTTON,
										pt.x, pt.y,
										0, m_hWnd, NULL );

						PostMessage(WM_NULL);
					}

					DestroyMenu(hMenu);
				}
			}
			else if (::IsWindow(GetLockedWindow()->m_hWnd))
				GetLockedWindow()->SetForegroundWindow();

			break;
		}
	}

	return 1;
}


// ////////////////////////////////////////////////////////////////////////////
//
LRESULT CMainFrame::OnPausesChanged( WPARAM wParam, LPARAM lParam )
{
	long sheeterID = (long) lParam;

	// See if the sheeterID is the one from the current work day,
	// in which case we should refresh the object wrt pauses
	//
	if ((CWorkDay::getCurrentDay() != NULL) && (CWorkDay::getCurrentDay()->getRec() != NULL) && (CWorkDay::getCurrentDay()->getRec()->m_ID == sheeterID))
	{
		CWorkDay::getCurrentDay()->pausesChanged();
		UpdateTooltip();
	}

	return 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
LRESULT CMainFrame::OnDlgManage( WPARAM wParam, LPARAM lParam )
{
	OnManaging();
	return 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
LRESULT CMainFrame::OnDlgReporting( WPARAM wParam, LPARAM lParam )
{
	OnReporting();
	return 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnExit()
{
	PostMessage(WM_CLOSE);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::UpdateTooltip()
{
	NOTIFYICONDATA tnid;
	CString sTip;

	if (CWorkDay::getCurrentDay() == NULL)
	{
		sTip += "Not working";
	}
	else
	{
		if (CWorkDay::getCurrentDay()->isPaused())
		{
			CString sTemp;
			sTemp.Format("Paused since %s.\n", GetDisplayTime(CWorkDay::getCurrentDay()->getPausedTime()));
			sTip += sTemp;
		}

		CString sTemp;
		sTemp.Format("Started at %s.\nSo far: %s.",
								GetDisplayTime(CWorkDay::getCurrentDay()->getRec()->m_StartTime),
								GetDisplayTime(CWorkDay::getCurrentDay()->getTotalWorkTime()) );
		sTip += sTemp;
	}

	strcpy(tnid.szTip, (LPCTSTR)sTip);

	tnid.cbSize				= sizeof(NOTIFYICONDATA);
	tnid.hWnd				= m_hWnd;
	tnid.uID				= 1;
	tnid.uFlags				= NIF_TIP;

	Shell_NotifyIcon(NIM_MODIFY, &tnid);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == TIMER_ID_TOOLTIP)
	{
		UpdateTooltip();
		CFrameWnd::OnTimer(nIDEvent);
	}
	else if (nIDEvent == TIMER_ID_START_EVENTS)
	{
		KillTimer(TIMER_ID_START_EVENTS);
		scheduleNextEvent();
	}
	else if (nIDEvent == TIMER_ID_NEXT_EVENT)
	{
		KillTimer(TIMER_ID_NEXT_EVENT);
		handleNextEvent();
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnMain()
{
	CDlgMain dlg;

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);

	UpdateTooltip();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnReporting()
{
	CDlgReporting dlg;

	LockWindow(&dlg, true);
	int ret = dlg.DoModal();
	LockWindow(&dlg, false);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnManaging()
{
	CDlgManage dlg;

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnReopenDay()
{
	if (CWorkDay::getCurrentDay() != NULL)
	{
		AfxMessageBox("There is a day going on right now!");
		return;
	}

	if (AfxMessageBox("Are you sure you want to reopen the day?", MB_YESNO) != IDYES)
		return;

	COleDateTime date = GetNowTime();
	CWorkDay::reopenDay(date);
	if (CWorkDay::getCurrentDay() == NULL)
	{
		// Try yesterday
		date = date - COleDateTimeSpan(1, 0, 0, 0);
		CWorkDay::reopenDay(date);
	}

	if (CWorkDay::getCurrentDay() == NULL)
	{
		AfxMessageBox("There is no day today to reopen!");
		return;
	}

	UpdateTooltip();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnPopuprclickStatistics()
{
	CDlgStats dlg;

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnUpdatePopuprclickSynchronize(CCmdUI* pCmdUI) 
{
	// Disable always
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnPopuprclickSynchronize()
{
/*
	CDlgSynchronize dlg;

	dlg.m_bGetProjects = TRUE;
	dlg.m_bSendTimesheet = TRUE;
	dlg.m_nSendType = 0;

	g_pWndTop = &dlg;
	dlg.DoModal();
	g_pWndTop = NULL;
*/

	if ( AfxMessageBox("Synchronize projects now?", MB_YESNO) == IDYES )
	{
		CSynchronize sync;
		CStringArray reportSend, reportRetrieve;

		CDlgWait dlg;
		dlg.m_sTitle = "Synchronize";
		dlg.m_sMessage = "Please wait while synchronizing with the server...";

		LockWindow(&dlg, true);
		dlg.Create(CDlgWait::IDD, this);
		dlg.ShowWindow(SW_SHOW);
		dlg.UpdateWindow();

		CString result("");
/*
		result += "Sending to server: ";
		if ( sync.sendProjects(&reportSend) )
		{
			if (reportSend.GetSize() == 0)
			{
				result += "no modifications were made!";
			}
			else
			{
				for( int i=0; i<reportSend.GetSize(); i++ )
				{
					result += "\n";
					result += reportSend[i];
				}
			}
		}
		else
		{
			result += "error while retrieving projects!";
		}


		result += "\n\n";
*/

		result += "Retrieving from server: ";
		if ( sync.retrieveProjects(NULL, &reportRetrieve) )
		{
			if (reportRetrieve.GetSize() == 0)
			{
				result = "no modifications were made!";
			}
			else
			{
				for( int i=0; i<reportRetrieve.GetSize(); i++ )
				{
					result += "\n";
					result += reportRetrieve[i];
				}
			}
		}
		else
		{
			result = "error while retrieving projects!";
		}

		dlg.DestroyWindow();
		LockWindow(&dlg, false);

		AfxMessageBox(result);
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnPopuprclickOptions() 
{
	CDlgOptions dlg;

	dlg.m_sReportDir		= COptions::getReportDir();
	dlg.m_sTemplateDir		= COptions::getReportTemplateDir();
//	dlg.m_sSyncUsername		= COptions::getSyncUsername();
//	dlg.m_sSyncWsdl			= COptions::getSyncWsdlUrl();

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);

	COptions::setReportTemplateDir(dlg.m_sTemplateDir);
	COptions::setReportDir(dlg.m_sReportDir);
//	COptions::setSyncUsername(dlg.m_sSyncUsername);
//	COptions::setSyncWsdlUrl(dlg.m_sSyncWsdl);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnPopuprclickOptionsProjects() 
{
	CDlgManageProjects dlg;

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnPopuprclickEvents()
{
	CDlgEvents dlg;
	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);

	// Re-evaluate the next event to fire
	scheduleNextEvent();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::scheduleNextEvent()
{
	KillTimer(TIMER_ID_NEXT_EVENT);

	CRecEvent query;
	query.Open(dbOpenDynaset, "SELECT * FROM EVENT WHERE FIRED=0 ORDER BY TRIGGER", 0);

	// No events?
	if (query.IsBOF())
		return;

	query.MoveFirst();

	COleDateTime now = COleDateTime::GetCurrentTime();
	UINT msLeft;
/*
	CString ss;
	ss.Format("%s\n%s", query.m_trigger.Format(), now.Format());
	AfxMessageBox(ss);
*/

	// See if this event is in the past
	if (query.m_trigger < now)
	{
		msLeft = 50;
	}
	else
	{
		// Compute the number of milliseconds left before the event
		COleDateTimeSpan timeSpan = query.m_trigger - now;
		msLeft = UINT(timeSpan.GetTotalSeconds()) * 1000;
	}

	SetTimer(TIMER_ID_NEXT_EVENT, msLeft, NULL);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::handleNextEvent()
{
	CRecEvent query;
	query.Open(dbOpenDynaset, "SELECT * FROM EVENT WHERE FIRED=0 ORDER BY TRIGGER", 0);

	// No events?
	if (query.IsBOF())
		return;

	query.MoveFirst();

	COleDateTime now = COleDateTime::GetCurrentTime();
	if (query.m_trigger < now)
	{

/*
		CString s;
		s.Format("%02i-%02i-%02i  %02i:%02i\n\n%s",
				query.m_when.GetDay(), query.m_when.GetMonth(), query.m_when.GetYear(),
				query.m_when.GetHour(), query.m_when.GetMinute(),
				query.m_text);

		AfxMessageBox(s);
*/
		CDlgShowEvent dlg;
		dlg.m_eventId = query.m_ID;
		query.Close();
		dlg.DoModal();
	}
	
	scheduleNextEvent();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CMainFrame::OnPopuprclickAddevent() 
{
	CDlgEditEvent dlg(this);

	// Tomorrow at 9am
	dlg.m_Date = CTime::GetCurrentTime() + CTimeSpan(1,0,0,0);
	dlg.m_Time = CTime(2000,1,1, 9,0,0);

	if ( dlg.DoModal() != IDOK )
		return;

	COleDateTime when( dlg.m_Date.GetYear(), dlg.m_Date.GetMonth(), dlg.m_Date.GetDay(),
					   dlg.m_Time.GetHour(), dlg.m_Time.GetMinute(), dlg.m_Time.GetSecond() );
	CRecEvent::AddEvent(when, dlg.m_Text);

	scheduleNextEvent();
}
