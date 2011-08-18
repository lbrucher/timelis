// $Id: DlgMain.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgMain.h"
#include "DlgPauses.h"
#include "DlgTasks.h"
#include "WorkDay.h"
#include "RecTimeSheet.h"
#include "RecPauses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_REFRESHDAYLABEL		(WM_USER+1)


BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
	//{{AFX_MSG_MAP(CDlgMain)
	ON_BN_CLICKED(IDC_BUTPAUSERESUME, OnPauseResume)
	ON_BN_CLICKED(IDC_BUTSTARTFINISH, OnStartFinish)
	ON_BN_CLICKED(IDC_BUTTASKS, OnTasks)
	ON_BN_CLICKED(IDC_BUTMANAGE, OnManage)
	ON_BN_CLICKED(IDC_BUTPAUSES, OnButPauses)
	ON_BN_CLICKED(IDC_BUTADDTASK, OnButAddTask)
	ON_MESSAGE(WM_REFRESHDAYLABEL, OnRefreshDayLabel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgMain::CDlgMain(CWnd* pParent ) :
	CDialog(CDlgMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMain)
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain)
	DDX_Control(pDX, IDC_BUTADDTASK, m_ButAddTask);
	DDX_Control(pDX, IDC_TASKS, m_Tasks);
	DDX_Control(pDX, IDC_TASK_UNTIL, m_TaskUntil);
	DDX_Control(pDX, IDC_TASK_FROM, m_TaskFrom);
	DDX_Control(pDX, IDC_PAUSE_UNTIL, m_PauseUntil);
	DDX_Control(pDX, IDC_PAUSE_FROM, m_PauseFrom);
	DDX_Control(pDX, IDC_DAY_LABEL, m_DayLabel);
	DDX_Control(pDX, IDC_DAY_UNTIL, m_DayUntil);
	DDX_Control(pDX, IDC_DAY_FROM, m_DayFrom);
	DDX_Control(pDX, IDC_BUTPAUSES, m_ButPauses);
	DDX_Control(pDX, IDC_BUTMANAGE, m_ButManage);
	DDX_Control(pDX, IDC_BUTTASKS, m_ButTasks);
	DDX_Control(pDX, IDC_BUTSTARTFINISH, m_ButStartFinish);
	DDX_Control(pDX, IDC_BUTPAUSERESUME, m_ButPauseResume);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWorkDay* pDay = CWorkDay::getCurrentDay();

	if (pDay == NULL)
	{
		// DAY
		m_ButStartFinish.EnableWindow(TRUE);
		m_ButStartFinish.SetWindowText("Start Day");
		m_DayFrom.EnableWindow(TRUE);
		m_DayUntil.EnableWindow(FALSE);
		Time2CEdit(GetNowTime(), m_DayFrom);

		// PAUSES
		m_ButPauseResume.EnableWindow(FALSE);
		m_ButPauseResume.SetWindowText("Pause");
		m_ButPauses.EnableWindow(FALSE);
		m_PauseFrom.EnableWindow(FALSE);
		m_PauseUntil.EnableWindow(FALSE);

		// TASKS
		m_ButTasks.EnableWindow(FALSE);
		m_ButAddTask.EnableWindow(FALSE);
		m_Tasks.EnableWindow(FALSE);
		m_TaskFrom.EnableWindow(FALSE);
		m_TaskUntil.EnableWindow(FALSE);
	}
	else
	{
		// DAY
		m_ButStartFinish.EnableWindow(TRUE);
		m_ButStartFinish.SetWindowText("Finish Day");
		m_DayFrom.EnableWindow(FALSE);
		Time2CEdit(pDay->getRec()->m_StartTime, m_DayFrom);
		m_DayUntil.EnableWindow(TRUE);
		Time2CEdit(GetNowTime(), m_DayUntil);


		// PAUSES
		m_ButPauseResume.EnableWindow(TRUE);
		m_ButPauses.EnableWindow(TRUE);
		if (pDay->isPaused())
		{
			m_ButPauseResume.SetWindowText("Resume");
			m_PauseFrom.EnableWindow(FALSE);
			Time2CEdit(pDay->getPausedTime(), m_PauseFrom);
			m_PauseUntil.EnableWindow(TRUE);
			Time2CEdit(GetNowTime(), m_PauseUntil);
		}
		else
		{
			m_ButPauseResume.SetWindowText("Pause");
			m_PauseFrom.EnableWindow(TRUE);
			Time2CEdit(GetNowTime(), m_PauseFrom);
			m_PauseUntil.EnableWindow(TRUE);
			m_PauseUntil.SetWindowText("");
		}


		// TASKS
		m_ButTasks.EnableWindow(TRUE);
		m_ButAddTask.EnableWindow(FALSE);
		m_Tasks.EnableWindow(FALSE);
		m_TaskFrom.EnableWindow(FALSE);
		m_TaskUntil.EnableWindow(FALSE);
	}

	refreshDayLabel();
	UpdateData(FALSE);
	SetForegroundWindow();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::refreshDayLabel()
{
	if (CWorkDay::getCurrentDay() == NULL)
	{
		m_DayLabel.SetWindowText("Day not started yet.");
	}
	else
	{
		CString sTemp;
		sTemp.Format("%s, so far: %s.",
							GetDisplayDate(CWorkDay::getCurrentDay()->getRec()->m_StartTime),
							GetDisplayTime(CWorkDay::getCurrentDay()->getTotalWorkTime()));
		m_DayLabel.SetWindowText(sTemp);
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnStartFinish()
{
	if ( CWorkDay::getCurrentDay() == NULL )
	{
		COleDateTime startDate = CEditTime2Date(m_DayFrom, GetNowTime());

		if ( CWorkDay::startDay(startDate) == NULL )
			return;
	}
	else
	{
		COleDateTime finishDate = CEditTime2AdjustedDate(m_DayUntil, CWorkDay::getCurrentDay()->getRec()->m_StartTime);


		CDlgTasks dlg(CWorkDay::getCurrentDay(), &finishDate);

		LockWindow(&dlg, true);
		int ret = dlg.DoModal();
		LockWindow(&dlg, false);

		if (ret != IDOK)
			return;

		CWorkDay::endDay( Time2AdjustedDate(dlg.m_sFinished, CWorkDay::getCurrentDay()->getRec()->m_StartTime) );
	}

	EndDialog(IDOK);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnPauseResume()
{
	if (CWorkDay::getCurrentDay() == NULL)
	{
		AfxMessageBox("ERROR, day not started");
		return;
	}

	if ( CWorkDay::getCurrentDay()->isPaused() )
	{
		CWorkDay::getCurrentDay()->pauseOrResume( CEditTime2AdjustedDate(m_PauseUntil, CWorkDay::getCurrentDay()->getRec()->m_StartTime) );
	}
	else
	{
		CString sPauseEnd;
		m_PauseUntil.GetWindowText(sPauseEnd);
		if (sPauseEnd.IsEmpty())
		{
			CWorkDay::getCurrentDay()->pauseOrResume( CEditTime2AdjustedDate(m_PauseFrom, CWorkDay::getCurrentDay()->getRec()->m_StartTime) );
		}
		else
		{
			COleDateTime dtFrom = CEditTime2AdjustedDate(m_PauseFrom,  CWorkDay::getCurrentDay()->getRec()->m_StartTime);
			COleDateTime dtTo   = CEditTime2AdjustedDate(m_PauseUntil, CWorkDay::getCurrentDay()->getRec()->m_StartTime);
			long sheeterID = CWorkDay::getCurrentDay()->getRec()->m_ID;
			CRecPauses::AddPause(sheeterID, dtFrom, dtTo);

			// Notify app that pauses may have changed.
//			theApp.GetMainWnd()->PostMessage(WM_PAUSESCHANGED, 0, LPARAM(sheeterID));
			AfxGetMainWnd()->PostMessage(WM_PAUSESCHANGED, 0, LPARAM(sheeterID));
		}
	}

	EndDialog(IDOK);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnTasks()
{
	CDlgTasks dlg(CWorkDay::getCurrentDay(), NULL);

	LockWindow(&dlg, true);
	dlg.DoModal();
	LockWindow(&dlg, false);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnManage()
{
	AfxGetMainWnd()->PostMessage(WM_DLG_MANAGE);
	EndDialog(IDOK);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnButPauses() 
{
	if (CWorkDay::getCurrentDay() == NULL)
		return;

	CDlgPauses dlg(CWorkDay::getCurrentDay()->getRec()->m_ID, this);
	dlg.DoModal();
	//refreshDayLabel();
	PostMessage(WM_REFRESHDAYLABEL);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgMain::OnButAddTask() 
{
}


// ////////////////////////////////////////////////////////////////////////////
//
LRESULT CDlgMain::OnRefreshDayLabel( WPARAM wParam, LPARAM lParam )
{
	refreshDayLabel();
	return 0;
}

