// $Id: RecTask.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "RecTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRecTask, CDaoRecordsetEx)

CRecTask::CRecTask() :
	CDaoRecordsetEx("[Task]")
{
	//{{AFX_FIELD_INIT(CRecTask)
	m_ID = 0;
	m_SheeterID = -1;
	m_ActivityID = -1;
	m_OfficialDescription = _T("");
	m_PrivateDescription = _T("");
	m_Minutes = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


void CRecTask::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecTask)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Long(pFX, _T("[SheeterID]"), m_SheeterID);
	DFX_Long(pFX, _T("[ActivityID]"), m_ActivityID);
	DFX_Text(pFX, _T("[OfficialDescription]"), m_OfficialDescription);
	DFX_Text(pFX, _T("[PrivateDescription]"), m_PrivateDescription);
	DFX_Long(pFX, _T("[Minutes]"), m_Minutes);
	//}}AFX_FIELD_MAP
}


bool CRecTask::FindByID( long id )
{
	return DoFind( FormatString("select * from Task where ID=%li", id) );
}


void CRecTask::DeleteTask( long id )
{
	CString s;
	s.Format("DELETE * FROM Task WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();
}


void CRecTask::AddTask( long sheeterID, long activityID,
						const CString& officialDescription, const CString& privateDescription,
						long minutes )
{
	CRecTask rec;
	rec.AddNew();

	rec.m_SheeterID				= sheeterID;
	rec.m_ActivityID			= activityID;
	rec.m_OfficialDescription	= officialDescription;
	rec.m_PrivateDescription	= privateDescription;
	rec.m_Minutes				= minutes;

	rec.Update();
	rec.Close();
}


bool CRecTask::HasLinkToActivity( long activityID )
{
	CString sQuery;
	sQuery.Format("SELECT * FROM Task WHERE ActivityID=%li", activityID);

	CRecTask query;
	query.Open(dbOpenDynaset, sQuery, 0);
	bool bLinked = !query.IsEOF();
	query.Close();

	return bLinked;
}


void CRecTask::FindTasks( long sheeterID, CDWordArray& taskIDs )
{
	CString sQuery;
	sQuery.Format("SELECT * FROM Task WHERE SheeterID=%li", sheeterID);

	CRecTask query;
	query.Open(dbOpenDynaset, sQuery, 0);
	while(!query.IsEOF())
	{
		taskIDs.Add( DWORD(query.m_ID) );
		query.MoveNext();
	}
	query.Close();
}

