// $Id: DlgManage.cpp,v 1.3 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "timelis.h"
#include "DlgManage.h"
#include "WorkDay.h"
#include "RecTask.h"
#include "RecProject.h"
#include "RecPauses.h"
#include "DlgAddEditTask.h"
#include "DlgPauses.h"
#include "DlgNewDay.h"
#include "DlgSelectActivities.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTimelisApp theApp;


BEGIN_MESSAGE_MAP(CDlgManage, CDialog)
	//{{AFX_MSG_MAP(CDlgManage)
	ON_LBN_SELCHANGE(IDC_DAYS, OnSelchangeDays)
	ON_BN_CLICKED(IDC_ADDTASK, OnAddtask)
	ON_BN_CLICKED(IDC_EDITTASK, OnEdittask)
	ON_BN_CLICKED(IDC_DELTASK, OnDeltask)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_DAYSET, OnDayset)
	ON_LBN_SELCHANGE(IDC_TASKS, OnSelchangeTasks)
	ON_LBN_DBLCLK(IDC_TASKS, OnDblclkTasks)
	ON_BN_CLICKED(IDC_NEWDAY, OnNewday)
	ON_BN_CLICKED(IDC_PAUSES, OnPauses)
	ON_BN_CLICKED(IDC_DELDAY, OnDelday)
	ON_BN_CLICKED(IDC_SHOWSTATS, OnShowStats)
	ON_BN_CLICKED(IDC_SELECTACTIVITIES, OnSelectActivities)
	ON_NOTIFY(NM_SETFOCUS, IDC_PERIOD_FROM, OnSetfocusPeriodFrom)
	ON_NOTIFY(NM_SETFOCUS, IDC_PERIOD_TO, OnSetfocusPeriodTo)
	ON_EN_SETFOCUS(IDC_DAY_CUSTOMVALUE, OnSetfocusDayCustomvalue)
	ON_CBN_SETFOCUS(IDC_MONTH_NAMES, OnSetfocusMonthNames)
	ON_EN_SETFOCUS(IDC_MONTH_YEAR, OnSetfocusMonthYear)
	ON_BN_CLICKED(IDC_REPORTING, OnReporting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgManage::CDlgManage(CWnd* pParent /*=NULL*/) :
	CDialog(CDlgManage::IDD, pParent),
	m_bReporting(false)
{
	//{{AFX_DATA_INIT(CDlgManage)
	m_PeriodFrom = COleDateTime::GetCurrentTime();
	m_PeriodTo = COleDateTime::GetCurrentTime();
	m_nReportingDay = -1;
	m_sReportingDayCustomValue = "";
	m_sSchedule = _T("");
	m_nFilterDay = -1;
	m_nFilterActivities = -1;
	m_nMonthYear = 0;
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManage)
	DDX_Control(pDX, IDC_MONTH_YEAR, m_CtrlMonthYear);
	DDX_Control(pDX, IDC_MONTH_NAMES, m_MonthNames);
	DDX_Control(pDX, IDC_SELECTACTIVITIES, m_ButFilterActivities);
	DDX_Control(pDX, IDC_DELDAY, m_ButDelDay);
	DDX_Control(pDX, IDC_PAUSES, m_Pauses);
	DDX_Control(pDX, IDC_FILTER_MONTH, m_CtrlFilterTypeMonth);
	DDX_Control(pDX, IDC_FILTER_PERIOD, m_CtrlFilterTypePeriod);
	DDX_Control(pDX, IDC_SEARCH, m_ButSearch);
	DDX_Control(pDX, IDC_PERIOD_TO, m_CtrlPeriodTo);
	DDX_Control(pDX, IDC_PERIOD_FROM, m_CtrlPeriodFrom);
	DDX_Control(pDX, IDC_NEWDAY, m_NewDay);
	DDX_Control(pDX, IDC_EDITTASK, m_EditTask);
	DDX_Control(pDX, IDC_DELTASK, m_DelTask);
	DDX_Control(pDX, IDC_ADDTASK, m_AddTask);
	DDX_Control(pDX, IDC_TASKS, m_Tasks);
	DDX_Control(pDX, IDC_DAYS, m_Days);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_FROM, m_PeriodFrom);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_TO, m_PeriodTo);
	DDX_Radio(pDX, IDC_DAY_NOTSET, m_nReportingDay);
	DDX_Text(pDX, IDC_DAY_CUSTOMVALUE, m_sReportingDayCustomValue);
	DDX_Text(pDX, IDC_SCHEDULE, m_sSchedule);
	DDX_Radio(pDX, IDC_FILTER_MONTH, m_nFilterDay);
	DDX_Radio(pDX, IDC_FILTER_ALLACTIVITIES, m_nFilterActivities);
	DDX_Text(pDX, IDC_MONTH_YEAR, m_nMonthYear);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	COleDateTime now = GetNowTime();

	// Formula to get values in dailog units: dialog_units = pixels / 1.5
	// See MapDialogRect() and GetDialogBaseUnits() for more info
	//
	int tabsDays[] = { 20, 65, 90, 122 };
	m_Days.SetTabStops(4, tabsDays);

//	int tabsTasks[] = { 70, 96 };
	int tabsTasks[] = { 130, 160 };
	m_Tasks.SetTabStops(2, tabsTasks);

	if (m_bReporting)
	{
		m_nFilterDay = 1;

		m_CtrlMonthYear.EnableWindow(FALSE);
		m_MonthNames.EnableWindow(FALSE);
		m_CtrlPeriodFrom.EnableWindow(FALSE);
		m_CtrlPeriodTo.EnableWindow(FALSE);
		m_ButSearch.EnableWindow(FALSE);
		m_CtrlFilterTypeMonth.EnableWindow(FALSE);
		m_CtrlFilterTypePeriod.EnableWindow(FALSE);
	}
	else
	{
		m_nFilterDay = 0;
		m_nMonthYear = now.GetYear();
		for(int i=0; i<12; i++)
			m_MonthNames.AddString( g_sMonthNames[i] );
		m_MonthNames.SetCurSel(now.GetMonth()-1);
	}

	m_nFilterActivities = 0;

	UpdateData(FALSE);


	OnSearch();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnSelchangeDays()
{
	int sel = m_Days.GetCurSel();
	if (sel != LB_ERR)
	{
		long sheeterID = (long) m_Days.GetItemData(sel);
		setDay(sheeterID);
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CDlgManage::BuildQuery( CString& sQuery )
{
	UpdateData(TRUE);

	CString sFilteredActivities, sFilteredPeriod;


	// Activities filtering
	//
	if (m_nFilterActivities == 0)
	{
		sFilteredActivities = "";
	}
	else if (m_nFilterActivities == 1)
	{
		if (m_selectedActivityIDs.GetSize() > 0)
		{
			char buf[4096] = "";
			char num[64];
			for(int i=0; i<m_selectedActivityIDs.GetSize(); i++)
			{
				wsprintf(num, "%s%i", (i == 0 ? "":","), m_selectedActivityIDs[i]);
				lstrcat(buf, num);
			}

			sFilteredActivities.Format("AND ID IN (select SheeterID from Task where ActivityID in (%s))", buf);
		}
		else
		{
			sFilteredActivities = "";
		}
	}
	else
		return false;



	// Day/period filtering
	//
	if (m_nFilterDay == 0)
	{
		int month = m_MonthNames.GetCurSel();
		if (month == -1)
			month = 0;

		sFilteredPeriod.Format( "StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM#",
									FormatDate(m_nMonthYear, month+1, 01),
									FormatDate(MaxMonthDate(month+1, m_nMonthYear)) );
	}
	else if (m_nFilterDay == 1)
	{
		sFilteredPeriod.Format( "StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM#",
									FormatDate(m_PeriodFrom),
									FormatDate(m_PeriodTo) );
	}
	else
		return false;



	sQuery.Format("SELECT * FROM TimeSheet WHERE %s %s ORDER BY StartTime", sFilteredPeriod, sFilteredActivities);
	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnSearch()
{
	CString sQuery;
	if ( BuildQuery(sQuery) )
	{
		CRecTimeSheet query;
		query.Open(dbOpenDynaset, sQuery, 0);
		refreshDays(query);
		query.Close();
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::refreshDays( CRecTimeSheet& query )
{
	m_Days.ResetContent();
	clearDay();

	if (!query.IsBOF())
		query.MoveFirst();

	while(!query.IsEOF())
	{
		addDay(query);
		query.MoveNext();
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
CString CDlgManage::buildDayString( CRecTimeSheet& rec )
{
	CString s, sDay;

	if (rec.isReportingDaySet())
	{
		int hours = int(rec.getReportingDayHours());
		int minutes = int(rec.getReportingDayHours()*60)-(hours*60);
		if (minutes == 0)
			sDay.Format("%i hrs", hours);
		else
			sDay.Format("%i:%i hrs", hours, minutes);
	}
	else
	{
		sDay = "day not set";
	}

	s.Format("%s\t%s\t%s\t%s\t(%s)",
		GetWeekDay(rec.m_StartTime),
		GetDisplayDate(rec.m_StartTime),
		GetDisplayTime(rec.m_StartTime),
		GetDisplayTime(CWorkDay::getTotalWorkTime(rec)), sDay );

	return s;
}


// ////////////////////////////////////////////////////////////////////////////
//
int CDlgManage::addDay( CRecTimeSheet& rec )
{
	int n = m_Days.AddString( buildDayString(rec) );
	m_Days.SetItemData(n, DWORD(rec.m_ID));
	return n;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::clearDay()
{
	m_Tasks.ResetContent();
	m_AddTask.EnableWindow(FALSE);
	m_EditTask.EnableWindow(FALSE);
	m_DelTask.EnableWindow(FALSE);
	m_Pauses.EnableWindow(FALSE);
	m_ButDelDay.EnableWindow(FALSE);

	m_sSchedule = "";
	m_nReportingDay = 0;
	m_dtCurrentDay = COleDateTime();

	UpdateData(FALSE);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::setDay( long id )
{
	CRecTimeSheet rec;
	if (!rec.FindByID(id))
		return;

	m_dtCurrentDay = rec.m_StartTime;

	m_sSchedule.Format("%s %s\n%s %s\n(%s)",
							GetDisplayDate(rec.m_StartTime), GetDisplayTime(rec.m_StartTime),
							GetDisplayDate(rec.m_EndTime), GetDisplayTime(rec.m_EndTime),
							GetDisplayTime(CWorkDay::getTotalWorkTime(rec)));

	if (!rec.isReportingDaySet())
	{
		m_nReportingDay = 0;
		m_sReportingDayCustomValue = "";
	}
	else
	{
		m_sReportingDayCustomValue = GetDisplayTime( long(rec.getReportingDayHours() * 60) );

		if (rec.getReportingDayHours() == 0)
			m_nReportingDay = 1;
		else if (rec.getReportingDayHours() == 4)
			m_nReportingDay = 2;
		else if (rec.getReportingDayHours() == 8)
			m_nReportingDay = 3;
		else
			m_nReportingDay = 4;
	}


	UpdateData(FALSE);
	refreshTasks(&rec);

	m_AddTask.EnableWindow(TRUE);
	m_EditTask.EnableWindow(FALSE);
	m_DelTask.EnableWindow(FALSE);
	m_Pauses.EnableWindow(TRUE);
	m_ButDelDay.EnableWindow(TRUE);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::refreshTasks( CRecTimeSheet* pRec )
{
	CRecTimeSheet sheetRec;
	if (pRec == NULL)
	{
		int sel = m_Days.GetCurSel();
		if (sel != LB_ERR)
		{
			if (sheetRec.FindByID( (long) m_Days.GetItemData(sel) ))
				pRec = &sheetRec;
		}
	}

	if (pRec == NULL)
		return;

	m_Tasks.ResetContent();

	m_nTasks             = 0;
	m_nTotalTasksTime    = 0;
	m_nTotalWorkTime	 = CWorkDay::getTotalWorkTime(*pRec);
	m_bHasTaskWithNoTime = false;

	CString sQuery;
	sQuery.Format("SELECT * FROM Task WHERE SheeterID=%li", pRec->m_ID);
	CRecTask task;
	task.Open( dbOpenDynaset, sQuery, 0);
	if (!task.IsEOF())
	{
		// Find the remaining time
		while( ! task.IsEOF() )
		{
			if (task.m_Minutes == 0)
				m_bHasTaskWithNoTime = true;
			else
				m_nTotalTasksTime += task.m_Minutes;
			task.MoveNext();
		}

		CString activityName, s, sTime;
		task.MoveFirst();
		while(!task.IsEOF())
		{
			CRecActivity recActivity;
			if (recActivity.FindByID(task.m_ActivityID))
				activityName = recActivity.m_Name;
			else
				activityName = "?activity_name?";

			if (task.m_Minutes == 0)
				sTime = GetDisplayTime(m_nTotalWorkTime-m_nTotalTasksTime)+"*";
			else
				sTime = GetDisplayTime(task.m_Minutes);

			CString privateDescription("");
			if (!task.m_PrivateDescription.IsEmpty())
				privateDescription.Format(" [%s]", task.m_PrivateDescription);

			s.Format("%s - %s\t%s\t%s%s",
							recActivity.GetProjectName(), activityName,
							sTime, task.m_OfficialDescription, privateDescription);

			int index = m_Tasks.AddString(s);
			m_Tasks.SetItemData(index, DWORD(task.m_ID));

			task.MoveNext();
		}
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnSelchangeTasks()
{
	int sel = m_Tasks.GetCurSel();
	m_AddTask.EnableWindow(TRUE);
	m_EditTask.EnableWindow( sel != LB_ERR );
	m_DelTask.EnableWindow( sel != LB_ERR );
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnDblclkTasks()
{
	OnEdittask();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnAddtask()
{
	int sel = m_Days.GetCurSel();
	if (sel == LB_ERR)
		return;

	long sheeterID = (long) m_Days.GetItemData(sel);

	CDlgAddEditTask dlg;

	if (m_nTotalWorkTime-m_nTotalTasksTime >= 0)
		dlg.m_nTaskTime = m_nTotalWorkTime-m_nTotalTasksTime;

	dlg.m_bAllowNoTime = !m_bHasTaskWithNoTime;

	if (dlg.DoModal() != IDOK)
		return;

	long minutes = (dlg.m_sTime.IsEmpty() ? 0 : (long) String2Minutes(dlg.m_sTime));
	CRecTask::AddTask(sheeterID, dlg.m_nSelectedActivityID, dlg.m_sOfficialDescription, dlg.m_sPrivateDescription, minutes);

	refreshTasks(NULL);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnEdittask()
{
	int sel = m_Tasks.GetCurSel();
	if (sel == LB_ERR)
		return;

	CRecTask rec;
	if (!rec.FindByID( (long)m_Tasks.GetItemData(sel) ))
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

	refreshTasks(NULL);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnDeltask()
{
	int sel = m_Tasks.GetCurSel();
	if (sel == LB_ERR)
		return;

	if ( AfxMessageBox("Are you sure you want to delete this task?", MB_YESNO) != IDYES )
		return;

	long taskID = (long) m_Tasks.GetItemData(sel);
	CRecTask::DeleteTask(taskID);

	refreshTasks(NULL);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnNewday()
{
//	clearDay();

	CDlgNewDay dlg;
	dlg.m_Date    = GetNowTime();
	dlg.m_sFrom   = theApp.GetProfileString("NewDay", "StartTime", "");
	dlg.m_sLength = theApp.GetProfileString("NewDay", "Duration", "");

	if (dlg.DoModal() != IDOK)
		return;

	float dayLength = (float)atof(dlg.m_sLength);
	if ((dayLength == 0) || (dayLength > 23.9))
	{
		AfxMessageBox("Invalid day length!");
		return;
	}

	theApp.WriteProfileString("NewDay", "StartTime", GetDisplayTime(String2Minutes(dlg.m_sFrom)));
	theApp.WriteProfileString("NewDay", "Duration", dlg.m_sLength);


	// Add the new day
	//
	// Verify the given work day has not already been used
	CRecTimeSheet rec;
	if (rec.FindByDate(dlg.m_Date))
	{
		AfxMessageBox("There is already a work day on that date!");
		return;
	}


	int hours = int(rec.getReportingDayHours());
	int minutes = int(rec.getReportingDayHours()*60) - (hours*60);

	rec.AddNew();

	rec.setReportingDayHours(dayLength);
	rec.m_StartTime = SetTimeOfDate(dlg.m_Date, dlg.m_sFrom);
	rec.m_EndTime   = rec.m_StartTime + COleDateTimeSpan(0, hours, minutes, 0);

	rec.Update();
	rec.SetBookmark(rec.GetLastModifiedBookmark());

	int index = addDay(rec);
	m_Days.SetCurSel(index);

	OnSelchangeDays();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnDayset()
{
	UpdateData(TRUE);

	// Verify the given work day has not already been used
	CRecTimeSheet rec;
	if (rec.FindByDate(m_dtCurrentDay))
	{
		rec.Edit();

		if (m_nReportingDay == 0)			rec.setReportingDayHours(-1);
		else if (m_nReportingDay == 1)		rec.setReportingDayHours(0);
		else if (m_nReportingDay == 2)		rec.setReportingDayHours(4);
		else if (m_nReportingDay == 3)		rec.setReportingDayHours(8);
		else if (m_nReportingDay == 4)		rec.setReportingDayHours( float(String2Minutes(m_sReportingDayCustomValue))/60 );

		rec.Update();


		// Replace the entry in the Days listbox
		for( int i=0; i<m_Days.GetCount(); i++)
		{
			if (rec.m_ID == (long) m_Days.GetItemData(i))
			{
				m_Days.DeleteString(i);
				int n = m_Days.InsertString(i, buildDayString(rec) );
				m_Days.SetItemData(n, DWORD(rec.m_ID));
				m_Days.SetCurSel(n);
				break;
			}
		}
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnPauses()
{
	int sel = m_Days.GetCurSel();
	if (sel != LB_ERR)
	{
		long sheeterID = (long) m_Days.GetItemData(sel);
		CDlgPauses dlg(sheeterID, this);
		dlg.DoModal();

		// Refresh
		if (dlg.wasModified())
			OnSearch();
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnDelday()
{
	int sel = m_Days.GetCurSel();
	if (sel != LB_ERR)
	{
		if ( AfxMessageBox("Are you sure you want to completely delete this day and all its tasks?", MB_YESNO) != IDYES )
			return;

		long sheeterID = (long) m_Days.GetItemData(sel);

		CDWordArray pauseIDs;
		CDWordArray taskIDs;

		// Gather pauses and tasks
		CRecPauses::FindPauses(sheeterID, pauseIDs);
		CRecTask::FindTasks(sheeterID, taskIDs);

		// Delete pauses
		{
			for( int i=0; i < pauseIDs.GetSize(); i++ )
				CRecPauses::DeletePause( (long) pauseIDs.GetAt(i) );
		}

		// Delete tasks
		{
			for( int i=0; i < taskIDs.GetSize(); i++ )
				CRecTask::DeleteTask( (long) taskIDs.GetAt(i) );
		}

		// Delete TimeSheet
		CRecTimeSheet::DeleteTimeSheet(sheeterID);

		clearDay();
		m_Days.SetCurSel(-1);
		m_Days.DeleteString(sel);
		OnSelchangeDays();
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnShowStats()
{
	CString sQuery;
	if (!BuildQuery(sQuery) )
		return;

	CRecTimeSheet query;
	query.Open(dbOpenDynaset, sQuery, 0);

	if (!query.IsBOF())
		query.MoveFirst();

	int   numActualDays = 0;
	float numActualHours = 0;
	float numOfficialHours = 0;
	int   numOfficialDays = 0;

	while(!query.IsEOF())
	{
		if (query.IsFinished())
		{
			numActualDays++;
			numActualHours += float(CWorkDay::getTotalWorkTime(query))/60;

			if (query.isReportingDaySet())
			{
				numOfficialDays++;
				numOfficialHours += query.getReportingDayHours();
			}
		}
		query.MoveNext();
	}

	query.Close();


	int minRequiredHours = numActualDays*8;
	float delta = numActualHours - ((float)minRequiredHours);

	CString s, stats;

	s.Format("Actual days:\t\t%i\t\n",   numActualDays); stats += s;
	s.Format("Actual hours:\t\t%.1f\t\n", numActualHours); stats += s;
	s.Format("Minimum required hours:\t%i\n",   minRequiredHours); stats += s;
	if (delta > 0)
	{
		s.Format("  -> positive hours quota:\t%.1f\n", delta); stats += s;
	}
	else
	{
		s.Format("  -> negative hours quota:\t%.1f\n", -delta); stats += s;
	}
	s.Format("Actual average hours/day:\t%.1f\n", float(numActualHours)/numActualDays); stats += s;
	s.Format("\n"); stats += s;
	s.Format("Official days:\t\t%i\n", numOfficialDays); stats += s;
	s.Format("Official hours:\t\t%.1f\n", numOfficialHours); stats += s;
	
	AfxMessageBox(stats);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManage::OnSelectActivities()
{
	UpdateData(TRUE);

	SendDlgItemMessage(IDC_FILTER_ALLACTIVITIES, BM_SETCHECK, 0);
	SendDlgItemMessage(IDC_FILTER_SELACTIVITIES, BM_SETCHECK, 1);

	CDlgSelectActivities dlg(this);

	if (m_nFilterActivities == 1)
	{
		dlg.m_activityIDs.Append(m_savedActivityIDs);
		dlg.m_projectIDs.Append(m_savedProjectIDs);
	}

	if (dlg.DoModal() != IDOK)
		return;

	// Ensure that selected activities are not already in the selected projects
	//
	m_savedActivityIDs.RemoveAll();
	m_savedProjectIDs.RemoveAll();
	m_savedActivityIDs.Append(dlg.m_activityIDs);
	m_savedProjectIDs.Append(dlg.m_projectIDs);

	if ((m_savedActivityIDs.GetSize() > 0) || (m_savedProjectIDs.GetSize() > 0))
	{
		m_selectedActivityIDs.RemoveAll();
		m_selectedActivityIDs.Append(m_savedActivityIDs);

		for(int i=0; i<m_savedProjectIDs.GetSize(); i++)
		{
			CRecProject rec;
			if ( rec.FindByID( m_savedProjectIDs[i] ) )
			{
				CDWordArray activities;
				CRecActivity::FindActivityIDs(rec.m_ID, activities, false);
				m_selectedActivityIDs.Append(activities);
			}
		}

		m_nFilterActivities = 1;
		UpdateData(FALSE);
	}
}

void CDlgManage::OnSetfocusPeriodFrom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_CtrlFilterTypeMonth.SetCheck(0);
	m_CtrlFilterTypePeriod.SetCheck(1);
	*pResult = 0;
}

void CDlgManage::OnSetfocusPeriodTo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_CtrlFilterTypeMonth.SetCheck(0);
	m_CtrlFilterTypePeriod.SetCheck(1);
	*pResult = 0;
}

void CDlgManage::OnSetfocusDayCustomvalue() 
{
	m_nReportingDay = 4;
	UpdateData(FALSE);
}

void CDlgManage::OnSetfocusMonthNames() 
{
	m_CtrlFilterTypeMonth.SetCheck(1);
	m_CtrlFilterTypePeriod.SetCheck(0);
}

void CDlgManage::OnSetfocusMonthYear() 
{
	m_CtrlFilterTypeMonth.SetCheck(1);
	m_CtrlFilterTypePeriod.SetCheck(0);
}

void CDlgManage::OnReporting() 
{
	AfxGetMainWnd()->PostMessage(WM_DLG_REPORTING);
	EndDialog(IDOK);
}
