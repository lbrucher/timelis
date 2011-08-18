// $Id: DlgTasks.cpp,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgTasks.h"
#include "WorkDay.h"
#include "DlgAddEditTask.h"
#include "RecTimeSheet.h"
#include "RecTask.h"
#include "RecProject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDaoDatabase* g_pTimeSheetDB;

BEGIN_MESSAGE_MAP(CDlgTasks, CDialog)
	//{{AFX_MSG_MAP(CDlgTasks)
	ON_BN_CLICKED(IDC_ADDTASK, OnAddtask)
	ON_BN_CLICKED(IDC_DELETETASK, OnDeletetask)
	ON_BN_CLICKED(IDC_EDITTASK, OnEdittask)
	ON_LBN_SELCHANGE(IDC_TASKS, OnSelchangeTasks)
	ON_LBN_DBLCLK(IDC_TASKS, OnDblclkTasks)
	ON_EN_KILLFOCUS(IDC_FINISHED, OnKillfocusFinished)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ////////////////////////////////////////////////////////////////////////////
//
CDlgTasks::CDlgTasks( CWorkDay* pDay, const COleDateTime* pDT, CWnd* pParent ) :
	CDialog(CDlgTasks::IDD, pParent),
	m_pDay(pDay),
	m_pdtFinish(pDT),
	m_nTotalTasksTime(0),
	m_nTasks(0),
	m_bHasTaskWithNoTime(false)
{
	//{{AFX_DATA_INIT(CDlgTasks)
	m_sFinished = _T("");
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTasks)
	DDX_Control(pDX, IDC_FINISHEDTIMELABEL, m_FinishedTimeLabel);
	DDX_Control(pDX, IDCANCEL, m_ButCancel);
	DDX_Control(pDX, IDOK, m_ButOK);
	DDX_Control(pDX, IDC_TASKS, m_Tasks);
	DDX_Control(pDX, IDC_UNALLOCTIME, m_UnallocatedTaskTime);
	DDX_Control(pDX, IDC_TOTALTASKTIME, m_TotalTaskTime);
	DDX_Control(pDX, IDC_DAYSOFAR, m_DaySoFar);
	DDX_Control(pDX, IDC_DAYSTART, m_DayStarted);
	DDX_Control(pDX, IDC_FINISHED, m_Finished);
	DDX_Control(pDX, IDC_FINISHEDLABEL, m_FinishedLabel);
	DDX_Control(pDX, IDC_EDITTASK, m_EditTask);
	DDX_Control(pDX, IDC_DELETETASK, m_DeleteTask);
	DDX_Text(pDX, IDC_FINISHED, m_sFinished);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgTasks::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pDay == NULL)
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

//	if ((m_bFinishDay) && (m_pDay->isPaused()))
//	{
//		AfxMessageBox("Cannot finish a day that is currently paused!");
//		EndDialog(IDCANCEL);
//		return TRUE;
//	}


	// Formula to get values in dailog units: dialog_units = pixels / 1.5
	// See MapDialogRect() and GetDialogBaseUnits() for more info
	//
	int tabsTasks[] = { 90, 116 };
	m_Tasks.SetTabStops(2, tabsTasks);


	m_nTotalWorkTime = m_pDay->getTotalWorkTime();


	// Get the list of tasks
	RefreshTasks();


	{
		CString s;
		s.Format("%s on %s", GetDisplayTime(m_pDay->getRec()->m_StartTime), GetDisplayDate(m_pDay->getRec()->m_StartTime));
		m_DayStarted.SetWindowText(s);
		m_DaySoFar.SetWindowText( GetDisplayTime(m_nTotalWorkTime) );
	}

	m_FinishedLabel.ShowWindow( m_pdtFinish!=NULL?SW_SHOW:SW_HIDE );
	m_Finished.ShowWindow( m_pdtFinish!=NULL?SW_SHOW:SW_HIDE );
	m_FinishedTimeLabel.ShowWindow( m_pdtFinish!=NULL?SW_SHOW:SW_HIDE );

	if (m_pdtFinish == NULL)
	{
		m_ButOK.ShowWindow(SW_HIDE);
		m_ButCancel.SetWindowText("Close");
	}
	else
	{
		if (m_pDay->isPaused())
		{
			m_Finished.EnableWindow(FALSE);
			AfxMessageBox("The day is currently paused. Continuing will end the day at the time the pause started.");
		}
		else
		{
			m_Finished.SetWindowText( GetDisplayTime(*m_pdtFinish) );
			m_Finished.SetSel(0,-1);
			m_Finished.SetFocus();
		}
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::OnSelchangeTasks()
{
	int sel = m_Tasks.GetCurSel();

	m_EditTask.EnableWindow( (sel != LB_ERR) );
	m_DeleteTask.EnableWindow( (sel != LB_ERR) );
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::OnAddtask()
{
	CDlgAddEditTask dlg;

	if (m_nTotalWorkTime-m_nTotalTasksTime >= 0)
		dlg.m_nTaskTime = m_nTotalWorkTime-m_nTotalTasksTime;

	dlg.m_bAllowNoTime = !m_bHasTaskWithNoTime;

	if (dlg.DoModal() != IDOK)
		return;


	long minutes = (dlg.m_sTime.IsEmpty() ? 0 : (long) String2Minutes(dlg.m_sTime));
	CRecTask::AddTask(m_pDay->getRec()->m_ID, dlg.m_nSelectedActivityID, dlg.m_sOfficialDescription, dlg.m_sPrivateDescription, minutes);

	RefreshTasks();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::OnEdittask()
{
	int sel = m_Tasks.GetCurSel();
	if (sel == LB_ERR)
		return;

	long taskID = (long) m_Tasks.GetItemData(sel);

	CRecTask rec;
	if (!rec.FindByID(taskID))
		return;

	CDlgAddEditTask dlg;
	dlg.m_nSelectedActivityID	= rec.m_ActivityID;
	dlg.m_sOfficialDescription	= rec.m_OfficialDescription;
	dlg.m_sPrivateDescription	= rec.m_PrivateDescription;

	if (rec.m_Minutes == 0)
		dlg.m_sTime = "";
	else
		dlg.m_sTime = GetDisplayTime(rec.m_Minutes);


	dlg.m_bAllowNoTime = true;
	if ((m_bHasTaskWithNoTime) && (rec.m_Minutes > 0))
		dlg.m_bAllowNoTime = false;

	if (dlg.DoModal() != IDOK)
		return;

	rec.Edit();
	rec.m_ActivityID		  = dlg.m_nSelectedActivityID;
	rec.m_OfficialDescription = dlg.m_sOfficialDescription;
	rec.m_PrivateDescription  = dlg.m_sPrivateDescription;

	if (dlg.m_sTime.IsEmpty())
		rec.m_Minutes = 0;
	else
		rec.m_Minutes = (long) String2Minutes(dlg.m_sTime);

	rec.Update();
	rec.Close();

	RefreshTasks();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::OnDeletetask()
{
	int sel = m_Tasks.GetCurSel();
	if (sel == LB_ERR)
		return;

	if ( AfxMessageBox("Are you sure you want to delete this task?", MB_YESNO) != IDYES )
		return;

	long taskID = (long) m_Tasks.GetItemData(sel);
	CRecTask::DeleteTask(taskID);

	RefreshTasks();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::OnDblclkTasks()
{
	OnEdittask();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgTasks::RefreshTasks()
{
	m_Tasks.ResetContent();
	m_nTasks = 0;

	CString sQuery;
	sQuery.Format("SELECT * FROM Task WHERE SheeterID=%li", m_pDay->getRec()->m_ID);

	m_nTotalTasksTime = 0;
	m_bHasTaskWithNoTime = false;

	CString activityName, s, sTime;
	CRecTask query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		m_nTasks++;

		CRecActivity recActivity;
		if (recActivity.FindByID(query.m_ActivityID))
			activityName.Format("%s - %s", recActivity.GetProjectName(), recActivity.m_Name);
		else
			activityName = "?activity_name?";

		if (query.m_Minutes == 0)
		{
			sTime = "--";
			m_bHasTaskWithNoTime = true;
		}
		else
		{
			sTime = GetDisplayTime(query.m_Minutes);
			m_nTotalTasksTime += query.m_Minutes;
		}

		CString privateDescription("");
		if (!query.m_PrivateDescription.IsEmpty())
			privateDescription.Format(" [%s]", query.m_PrivateDescription);

		s.Format("%s\t%s\t%s%s", activityName, sTime, query.m_OfficialDescription, privateDescription);

		int index = m_Tasks.AddString(s);
		m_Tasks.SetItemData(index, DWORD(query.m_ID));


		query.MoveNext();
	}
	query.Close();

	if (m_bHasTaskWithNoTime)
		m_nTotalTasksTime = m_nTotalWorkTime;

	m_TotalTaskTime.SetWindowText( GetDisplayTime(m_nTotalTasksTime) );
	m_UnallocatedTaskTime.SetWindowText( GetDisplayTime(m_nTotalWorkTime-m_nTotalTasksTime) );

	m_EditTask.EnableWindow(FALSE);
	m_DeleteTask.EnableWindow(FALSE);
}



void CDlgTasks::OnOK()
{
	// If we're finishing the day, check that there is at least 1 task created
	if (m_pdtFinish != NULL)
	{
		if (m_nTasks == 0)
		{
			AfxMessageBox("You must create at least one task before finishing the day!");
			return;
		}

		if (m_nTotalWorkTime-m_nTotalTasksTime > 0)
		{
			AfxMessageBox("There is some unallocated left over time!");
			return;
		}
	}

	CDialog::OnOK();
}

void CDlgTasks::OnKillfocusFinished()
{
	UpdateData(TRUE);

	m_nTotalWorkTime = m_pDay->getTotalWorkTime( Time2AdjustedDate(m_sFinished, m_pDay->getRec()->m_StartTime) );

	if (m_bHasTaskWithNoTime)
	{
		m_nTotalTasksTime = m_nTotalWorkTime;
		m_TotalTaskTime.SetWindowText( GetDisplayTime(m_nTotalTasksTime) );
	}

	m_DaySoFar.SetWindowText( GetDisplayTime(m_nTotalWorkTime) );
	m_UnallocatedTaskTime.SetWindowText( GetDisplayTime(m_nTotalWorkTime-m_nTotalTasksTime) );
}
