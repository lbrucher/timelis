// $Id: Reporting.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "Reporting.h"
#include "RecTimeSheet.h"
#include "RecPauses.h"
#include "RecTask.h"
#include "RecProject.h"
#include "resource.h"
#include "WorkDay.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


extern CDaoDatabase* g_pTimeSheetDB;



// ////////////////////////////////////////////////////////////////////////////
//
CReporting::CReporting() :
	m_bShowActualDayDuration(false)
{
}


// ////////////////////////////////////////////////////////////////////////////
//
CReporting::~CReporting()
{
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::setUseActualDayDuration( bool bEnable )
{
	m_bShowActualDayDuration = bEnable;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::setXmlFilename( const CString& s )
{
	m_sXmlFilename = s;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::setXslFilename( const CString& s )
{
	m_sXslFilename = s;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::setFilter( const COleDateTime& from , const COleDateTime& to )
{
	m_FilterFrom = from;
	m_FilterTo   = to;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::setActivities( const CDWordArray& activityIDs )
{
	m_FilterActivities.RemoveAll();
	m_FilterActivities.Append(activityIDs);
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CReporting::isReady()
{
	CString sQuery;
	sQuery.Format( "SELECT ID FROM TimeSheet WHERE StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM# AND ReportingHours = -1",
							FormatDate(m_FilterFrom),
							FormatDate(m_FilterTo) );

	CDaoRecordset query(g_pTimeSheetDB);
	query.Open( dbOpenDynaset, sQuery, 0);

	int count = 0;
	while(!query.IsEOF())
	{
		count++;
		query.MoveNext();
	}

	return bool(count == 0);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CReporting::WriteLine( CStdioFile& file, const char* msg, ... )
{
	static char S[4096] = "";
	va_list marker;
	va_start(marker, msg);
	vsprintf(S, msg, marker);
	file.WriteString(S);
	file.WriteString("\n");
	va_end(marker);
}



// ////////////////////////////////////////////////////////////////////////////
//
bool CReporting::create()
{
	CString sQuery;
	sQuery.Format( "SELECT * FROM TimeSheet WHERE StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM# ORDER BY StartTime",
							FormatDate(m_FilterFrom),
							FormatDate(m_FilterTo) );

	CRecTimeSheet query;
	query.Open( dbOpenDynaset, sQuery, 0);

	CStdioFile file;
	if (!file.Open(m_sXmlFilename, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
		return false;

	WriteLine(file, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>");
	WriteLine(file, "<?xml-stylesheet type=\"text/xsl\" href=\"file://%s\"?>", m_sXslFilename);
	WriteLine(file, "<report>");

	// Period
	WriteLine(file, "	<period>");
	WriteLine(file, "		<from>%s</from>", GetDisplayShortDate(m_FilterFrom));
	WriteLine(file, "		<to>%s</to>", GetDisplayShortDate(m_FilterTo));
	WriteLine(file, "	</period>");

	// Days
	WriteLine(file, "	<days>");

		float totalDays;
		executeDays(query, file, totalDays);

	WriteLine(file, "	</days>");
/*
	// Project totals
	WriteLine(file, "	<projects>");
		executeProjectTotals(query, file);
	WriteLine(file, "	</projects>");
*/
	// Grand Total
	CString sTotal;
	double dummy;
	if (modf(totalDays, &dummy) == 0) 
		sTotal.Format("%i", (int)totalDays);
	else
		sTotal.Format("%.1f", totalDays);
	WriteLine(file, "	<total>%s</total>", sTotal);

	WriteLine(file, "</report>");

	file.Close();
	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CReporting::IsTaskToReport( const CRecTask& task )
{
	for( int i=0; i < m_FilterActivities.GetSize(); i++ )
	{
		if ( DWORD(task.m_ActivityID) == m_FilterActivities[i] )
			return true;
	}
	return false;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CReporting::executeDays( CRecTimeSheet& query, CStdioFile& file, float& totalDays )
{
	totalDays = 0.0;

	while( ! query.IsEOF() )
	{
/*
		if ( query.getReportingDayHours() == 0 )
		{
			query.MoveNext();
			continue;
		}
*/

		CString sQueryTasks;
		sQueryTasks.Format("SELECT * FROM Task WHERE SheeterID=%li", query.m_ID);
		CRecTask queryTask;
		queryTask.Open( dbOpenDynaset, sQueryTasks, 0);

		if (!queryTask.IsEOF())
		{
			// The number of minutes used by the tasks for which a specific time amount was given.
			// Used to compute the # minutes for the task for which no amount of time was given
			long totalTaskMinutes = 0;

			// Same, but only for the tasks for which the activity was selected
			long totalSelProjectTaskMinutes = 0;

			// Count the number of tasks that belong to the list of selected projects
			int nTasksToReport = 0;

			// Indicate whether the task with no time (if any) covers one of the selected projects or not.
			boolean bNoTimeTaskHasSelectedProject = false;



			while( ! queryTask.IsEOF() )
			{
				// Check that this task's project is one of the selected projects
				if ( IsTaskToReport(queryTask) )
				{
					nTasksToReport++;

					if (queryTask.m_Minutes > 0)
						totalSelProjectTaskMinutes += queryTask.m_Minutes;
					else
						bNoTimeTaskHasSelectedProject = true;
				}


				// Always compute total of ALL tasks in order to determine the # minutes for the
				// remaining tasks, independently of what projects are selected
				if (queryTask.m_Minutes > 0)
					totalTaskMinutes += queryTask.m_Minutes;


				queryTask.MoveNext();
			}



			// Discard this day if there are no tasks to report!
			if (nTasksToReport > 0)
			{
				// Compute the # minutes for the no-time-task
				long officialRemainingDayMinutes = (query.getReportingDayHours()==0?0:long(query.getReportingDayHours() * 60) - totalTaskMinutes);
				long actualRemainingDayMinutes = CWorkDay::getTotalWorkTime(query) - totalTaskMinutes;


				// Compute the total number of minutes used by the tasks with selected projects
				long officialDayMinutes = totalSelProjectTaskMinutes;
				if (bNoTimeTaskHasSelectedProject)
					officialDayMinutes += officialRemainingDayMinutes;


				// The number of "days" for this day
				float fDays = float(officialDayMinutes)/60/8;

				// String representation of the 'fDays' variable
				double intpart;
				CString sOfficialDay;
				if ( modf(double(fDays), &intpart) == 0 )
					sOfficialDay.Format("%.0f", fDays);
				else
					sOfficialDay.Format("%.1f", fDays);
				totalDays += fDays;



				//
				// Generate the output
				//

				WriteLine(file, "		<day>");
				WriteLine(file, "			<date>%s</date>", GetDisplayShortDate(query.m_StartTime));
				WriteLine(file, "			<tasks>");

				queryTask.MoveFirst();
				while( ! queryTask.IsEOF() )
				{
					if ( IsTaskToReport(queryTask) )
					{
						CRecActivity recActivity;
						CString activityName;
						if (recActivity.FindByID(queryTask.m_ActivityID))
							activityName = recActivity.m_Name;
						else
							activityName = "?activity_name?";


						WriteLine(file, "				<task>");
						WriteLine(file, "					<project><![CDATA[%s]]></project>", recActivity.GetProjectName());
						WriteLine(file, "					<activity><![CDATA[%s]]></activity>", activityName);
						WriteLine(file, "					<description><![CDATA[%s]]></description>", queryTask.m_OfficialDescription);
						WriteLine(file, "					<durations>");
						WriteLine(file, "						<official>%s</official>", GetDisplayTime(queryTask.m_Minutes == 0 ? officialRemainingDayMinutes:queryTask.m_Minutes));
						WriteLine(file, "						<actual>%s</actual>", GetDisplayTime(queryTask.m_Minutes == 0 ? actualRemainingDayMinutes:queryTask.m_Minutes));
						WriteLine(file, "					</durations>");
						WriteLine(file, "				</task>");

					}
					queryTask.MoveNext();
				}

				WriteLine(file, "			</tasks>");
				WriteLine(file, "			<durations>");
				WriteLine(file, "				<official>%s</official>", sOfficialDay);
				WriteLine(file, "				<actual>?</actual>");
				WriteLine(file, "			</durations>");
				WriteLine(file, "		</day>");
			}
		}
		queryTask.Close();

		query.MoveNext();
	}
	query.Close();

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CReporting::executeProjectTotals( CRecTimeSheet& query, CStdioFile& file )
{
/*
	query.MoveFirst();

	CMapWordToPtr projectMap;

	while( ! query.IsEOF() )
	{
		CString sQueryTasks;
		sQueryTasks.Format("SELECT * FROM Task WHERE SheeterID=%li", query.m_ID);
		CRecTask queryTask;
		queryTask.Open( dbOpenDynaset, sQueryTasks, 0);

		if (!queryTask.IsEOF())
		{
			long* pTaskMinutes = NULL;
			projectMap.Lookup( WORD(queryTask.m_ID), pTaskMinutes);

			if (pTaskMinutes == NULL)
			{
				pTaskMinutes = new long;
				*pTaskMinutes = 0;
				projectMap.SetAt(WORD(queryTask.m_ID), pTaskMinutes);
			}

			// The number of minutes used by the tasks for which a specific time amount was given.
			// Used to compute the # minutes for the task for which no amount of time was given
			long totalTaskMinutes = 0;

			// Count the number of tasks that belong to the list of selected projects
			int nTasksToReport = 0;

			// Indicate whether the task with no time (if any) covers one of the selected projects or not.
			boolean bNoTimeTaskHasSelectedProject = false;



			while( ! queryTask.IsEOF() )
			{
				// Check that this task's project is one of the selected projects
				if ( IsTaskToReport(queryTask) )
				{
					nTasksToReport++;

					if (queryTask.m_Minutes > 0)
						*pTaskMinutes += queryTask.m_Minutes;
					else
						bNoTimeTaskHasSelectedProject = true;
				}


				// Always compute total of ALL tasks in order to determine the # minutes for the
				// remaining tasks, independently of what projects are selected
				if (queryTask.m_Minutes > 0)
					totalTaskMinutes += queryTask.m_Minutes;


				queryTask.MoveNext();
			}



			// Add the time for the no-time task, if there is one
			if (bNoTimeTaskHasSelectedProject)
			{
				// Compute the # minutes for the no-time-task
				long officialRemainingDayMinutes = (query.getReportingDayHours()==0?0:long(query.getReportingDayHours() * 60) - totalTaskMinutes);
				long actualRemainingDayMinutes = CWorkDay::getTotalWorkTime(query) - totalTaskMinutes;





				//
				// Generate the output
				//

				WriteLine(file, "		<day>");
				WriteLine(file, "			<date>%s</date>", GetDisplayShortDate(query.m_StartTime));
				WriteLine(file, "			<tasks>");

				queryTask.MoveFirst();
				while( ! queryTask.IsEOF() )
				{
					if ( IsTaskToReport(queryTask) )
					{
						CRecActivity recActivity;
						CString activityName;
						if (recActivity.FindByID(queryTask.m_ActivityID))
							activityName = recActivity.m_Name;
						else
							activityName = "?activity_name?";


						WriteLine(file, "				<task>");
						WriteLine(file, "					<project><![CDATA[%s]]></project>", recActivity.GetProjectName());
						WriteLine(file, "					<activity><![CDATA[%s]]></activity>", activityName);
						WriteLine(file, "					<description><![CDATA[%s]]></description>", queryTask.m_OfficialDescription);
						WriteLine(file, "					<durations>");
						WriteLine(file, "						<official>%s</official>", GetDisplayTime(queryTask.m_Minutes == 0 ? officialRemainingDayMinutes:queryTask.m_Minutes));
						WriteLine(file, "						<actual>%s</actual>", GetDisplayTime(queryTask.m_Minutes == 0 ? actualRemainingDayMinutes:queryTask.m_Minutes));
						WriteLine(file, "					</durations>");
						WriteLine(file, "				</task>");

					}
					queryTask.MoveNext();
				}

				WriteLine(file, "			</tasks>");
				WriteLine(file, "			<durations>");
				WriteLine(file, "				<official>%s</official>", sOfficialDay);
				WriteLine(file, "				<actual>?</actual>");
				WriteLine(file, "			</durations>");
				WriteLine(file, "		</day>");
			}
		}
		queryTask.Close();

		query.MoveNext();
	}
	query.Close();
*/
	return true;
}
