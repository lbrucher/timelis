// $Id: DlgStats.cpp,v 1.2 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgStats.h"
#include "RecTimeSheet.h"
#include "RecPauses.h"
#include "RecTask.h"
#include "RecProject.h"
#include "WorkDay.h"
#include "ActivityUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgStats, CDialog)
	//{{AFX_MSG_MAP(CDlgStats)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgStats::CDlgStats( CWnd* pParent ) :
	CDialog(CDlgStats::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStats)
	m_nFilter = -1;
	m_sMonth = _T("");
	m_dtFrom = COleDateTime::GetCurrentTime();
	m_dtTo = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgStats::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStats)
	DDX_Control(pDX, IDC_ACTIVITIES, m_Activities);
	DDX_Radio(pDX, IDC_FILTER_MONTH, m_nFilter);
	DDX_Text(pDX, IDC_MONTH, m_sMonth);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_TO, m_dtTo);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgStats::OnInitDialog()
{
	CDialog::OnInitDialog();

	COleDateTime now = GetNowTime();
	m_nFilter = 0;
	m_sMonth.Format("%02i/%04i", now.GetMonth(), now.GetYear());

	UpdateData(FALSE);
/*
	// Fill in projects
	CDWordArray pids;
	CStringArray pnames;
	CRecProject::FindAllProjects(pids, pnames);
	for(int i=0; i<pids.GetSize(); i++)
	{
		int index = m_Projects.AddString(pnames[i]);
		DWORD pid = pids[i];
		m_Projects.SetItemData(index, pid);
	}
*/

	// Fill in projects/activities
	FillAllProjectsList(m_Activities, m_itemDatas);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgStats::OnOK()
{
	UpdateData(TRUE);

	// Retrieve projects
	//
	int nSelItems = m_Activities.GetSelCount();
	if (nSelItems == 0)
	{
		AfxMessageBox("Please select at least one project or activity!");
		return;
	}

/*
	CDWordArray activityIDs;
	CDWordArray projectIDs;
	int *pSelectedItems = new int[nSelItems];
	m_Activities.GetSelItems( nSelItems, pSelectedItems );

	for(int i=0; i<nSelItems; i++)
		projectIDs.Add( m_Projects.GetItemData(pSelectedItems[i]) );

	delete [] pSelectedItems;
*/

	CDWordArray activityIDs;
	CDWordArray projectIDs;

	int *pSelectedItems = new int[nSelItems];
	m_Activities.GetSelItems( nSelItems, pSelectedItems );

	for(int i=0; i<nSelItems; i++)
	{
		long id = GetListBoxItemID(m_Activities, pSelectedItems[i], m_itemDatas);

		if ( IsListBoxActivity(m_Activities, pSelectedItems[i], m_itemDatas) )
			activityIDs.Add(id);
		else if ( IsListBoxProject(m_Activities, pSelectedItems[i], m_itemDatas) )
		{
			projectIDs.Add(id);
//			CDWordArray activities;
//			CRecActivity::FindActivities(id, activities, true);
//			m_selectedActivityIDs.Append(activities);
		}
	}

	delete [] pSelectedItems;


	// Get period
	//
	COleDateTime dtFrom, dtTo;

	if (m_nFilter == 0)
	{
		int sep = m_sMonth.Find('/');
		if (sep != -1)
		{
			int month = atoi( m_sMonth.Left(sep) );
			int year  = atoi( m_sMonth.Mid(sep+1) );

			dtFrom = COleDateTime(year, month, 1, 0,0,0);
			dtTo   = MaxMonthDate(month, year);
		}
		else
			return;
	}
	else if (m_nFilter == 1)
	{
		dtFrom = m_dtFrom;
		dtTo   = m_dtTo;
	}
	else
		return;


	RunStats(dtFrom, dtTo, projectIDs, activityIDs);
}



// ////////////////////////////////////////////////////////////////////////////
//
class CActivityStats : public CObject
{
public:
	COleDateTime dtFirst;
	COleDateTime dtLast;
	bool bFirstFound;
	long minutes;
	long activityID;

	CActivityStats() : activityID(-1), bFirstFound(false), dtFirst(), dtLast(), minutes(0) {}
	CActivityStats( long _activityID ) : activityID(_activityID), bFirstFound(false),
										 dtFirst(), dtLast(), minutes(0) {}

	CActivityStats& operator = ( const CActivityStats& other )
	{
		dtFirst		= other.dtFirst;
		dtLast		= other.dtLast;
		bFirstFound	= other.bFirstFound;
		minutes		= other.minutes;
		activityID	= other.activityID;
		return *this;
	}
};


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgStats::RunStats( const COleDateTime& dtFrom,
						  const COleDateTime& dtTo,
						  const CDWordArray& projectIDs,
						  const CDWordArray& activityIDs )
{
	// Init the stats
	//
	CArray< CActivityStats, CActivityStats& > activityStats;
	int i;

	for(i=0; i<projectIDs.GetSize(); i++)
	{
		CDWordArray activities;
		CRecActivity::FindActivityIDs( long(projectIDs[i]), activities, false );

		for(int j=0; j<activities.GetSize(); j++)
			activityStats.Add( CActivityStats(activities[j]) );
	}

	for(i=0; i<activityIDs.GetSize(); i++)
		activityStats.Add( CActivityStats(activityIDs[i]) );



	// Iterate through all timesheets between the given period
	//
	CString sQuery;
	sQuery.Format( "SELECT * FROM TimeSheet WHERE StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM# ORDER BY StartTime",
							FormatDate(dtFrom),
							FormatDate(dtTo) );

	CRecTimeSheet query;
	query.Open( dbOpenDynaset, sQuery, 0);

	while( ! query.IsEOF() )
	{
		// The index of the project which needs to be counted in the stats but for which the task
		// did not specify a duration (that task gets the remaining duration of the day)
		int noTimeTaskToCount = -1;

		// Total time for all tasks that specify a >0 duration
		long totalTaskMinutes = 0;


		CString sQueryTasks;
		sQueryTasks.Format("SELECT * FROM Task WHERE SheeterID=%li", query.m_ID);
		CRecTask queryTask;
		queryTask.Open( dbOpenDynaset, sQueryTasks, 0);
		while( ! queryTask.IsEOF() )
		{
			// Always compute total of ALL tasks in order to determine the # minutes for the
			// remaining tasks, independently of what projects are selected
			if (queryTask.m_Minutes > 0)
				totalTaskMinutes += queryTask.m_Minutes;

			// Scan each project to see if it is one the task's one
			for( int i=0; i < activityStats.GetSize(); i++ )
			{
				if ( queryTask.m_ActivityID == activityStats[i].activityID )
				{
					if (queryTask.m_Minutes > 0)
					{
						activityStats[i].minutes += queryTask.m_Minutes;

						if (!activityStats[i].bFirstFound)
						{
							activityStats[i].dtFirst     = query.m_StartTime;
							activityStats[i].bFirstFound = true;
						}
						activityStats[i].dtLast = query.m_StartTime;
					}
					else if ( (DATE)query.m_EndTime != (DATE)0 )
					{
						noTimeTaskToCount = i;
					}
				}
			}

			queryTask.MoveNext();
		}
		queryTask.Close();


		if (noTimeTaskToCount >= 0)
		{
			// Compute the # minutes for the no-time-task
			long remainingDayMinutes = CWorkDay::getTotalWorkTime(query) - totalTaskMinutes;

			activityStats[noTimeTaskToCount].minutes += remainingDayMinutes;

			if (!activityStats[noTimeTaskToCount].bFirstFound)
			{
				activityStats[noTimeTaskToCount].dtFirst     = query.m_StartTime;
				activityStats[noTimeTaskToCount].bFirstFound = true;
			}
			activityStats[noTimeTaskToCount].dtLast = query.m_StartTime;
		}


		query.MoveNext();
	}
	query.Close();


	// Construct report
	//
	{
		CString s;
		for(int i=0; i<activityStats.GetSize(); i++)
		{
			CString tmp;
			CRecActivity recActivity;
			recActivity.FindByID( activityStats[i].activityID );
			float fHours = ((float)activityStats[i].minutes)/60;
			float fDays  = fHours / 8;

			tmp.Format("%s - %s: %s (h:m), %.1f days (first: %s, last: %s)\n",
							recActivity.GetProjectName(), recActivity.m_Name,
							GetDisplayTime(activityStats[i].minutes),
							fDays,
							GetDisplayDate(activityStats[i].dtFirst),
							GetDisplayDate(activityStats[i].dtLast));
			s += tmp;
		}

		AfxMessageBox(s);
	}
}
