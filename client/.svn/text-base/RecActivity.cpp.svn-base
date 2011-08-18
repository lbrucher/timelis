// $Id: RecActivity.cpp,v 1.3 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "RecActivity.h"
#include "RecTask.h"
#include "RecProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CRecActivity, CDaoRecordsetEx)

CRecActivity::CRecActivity() :
	CDaoRecordsetEx("[Activity]")
{
	//{{AFX_FIELD_INIT(CRecActivity)
	m_ID = 0;
	m_MasterID = 0;
	m_ProjectID = 0;
	m_Name = _T("");
	m_Enabled = TRUE;
//	m_LocallyModified = FALSE;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


void CRecActivity::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecActivity)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Long(pFX, _T("[MasterID]"), m_MasterID);
	DFX_Long(pFX, _T("[ProjectID]"), m_ProjectID);
	DFX_Text(pFX, _T("[Name]"), m_Name);
	DFX_Bool(pFX, _T("[Enabled]"), m_Enabled);
//	DFX_Bool(pFX, _T("[LocallyModified]"), m_LocallyModified);
	//}}AFX_FIELD_MAP
}


bool CRecActivity::FindByID( long id )
{
	return DoFind( FormatString("select * from Activity where ID=%li", id) );
}

bool CRecActivity::FindByMasterID( long id )
{
	return DoFind( FormatString("select * from Activity where MasterID=%li", id) );
}


CString CRecActivity::GetProjectName()
{
	return CRecProject::GetProjectName(m_ProjectID);
}


void CRecActivity::FindActivityInfos( long projectID, TActivityInfoArray& activities, bool bEnabledOnly )
{
	CString sQuery;
	sQuery.Format("SELECT * FROM Activity WHERE ProjectID=%li %s",
						projectID, (bEnabledOnly?"AND Enabled=TRUE":"") );

	CRecActivity query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		activities.Add( CActivityInfo(query) );
		query.MoveNext();
	}
	query.Close();
}


void CRecActivity::FindActivityIDs( long projectID, CDWordArray& ids, bool bEnabledOnly )
{
	CString sQuery;
	sQuery.Format("SELECT * FROM Activity WHERE ProjectID=%li %s",
						projectID, (bEnabledOnly?"AND Enabled=TRUE":"") );

	CRecActivity query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		ids.Add( DWORD(query.m_ID) );
		query.MoveNext();
	}
	query.Close();
}


void CRecActivity::FindActivityMasterIDs( long projectID, CDWordArray& ids, bool bEnabledOnly )
{
	CString sQuery;
	sQuery.Format("SELECT * FROM Activity WHERE ProjectID=%li %s",
						projectID, (bEnabledOnly?"AND Enabled=TRUE":"") );

	CRecActivity query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		ids.Add( DWORD(query.m_MasterID) );
		query.MoveNext();
	}
	query.Close();
}


void CRecActivity::FindLocallyModifiedActivities( TActivityInfoArray& activities )
{
	CRecActivity query;
	query.Open( dbOpenDynaset, "SELECT * FROM Activity WHERE LocallyModified=TRUE", 0);
	while( ! query.IsEOF() )
	{
		activities.Add( CActivityInfo(query) );
		query.MoveNext();
	}
	query.Close();
}


/*
void CRecActivity::FindEnabledProjects( CDWordArray& ids, CStringArray& names )
{
	CRecProject query;
	query.Open( dbOpenDynaset, "SELECT * FROM Project WHERE Enabled=TRUE", 0);
	while( ! query.IsEOF() )
	{
		ids.Add( DWORD(query.m_ID) );
		names.Add(query.m_Name);

		query.MoveNext();
	}
	query.Close();
}


void CRecActivity::FindAllProjects( CDWordArray& ids, CStringArray& names )
{
	CRecProject query;
	query.Open( dbOpenDynaset, "SELECT * FROM Project", 0);
	while( ! query.IsEOF() )
	{
		ids.Add( DWORD(query.m_ID) );
		names.Add(query.m_Name);

		query.MoveNext();
	}
	query.Close();
}
*/



void CRecActivity::AddActivity( long projectID, const CString& name )
{
	CRecActivity rec;
	rec.FindByID(-1);
	rec.AddNew();

	rec.m_ProjectID = projectID;
	rec.m_Name      = name;
	rec.m_Enabled   = TRUE;

	rec.Update();
	rec.Close();
}



bool CRecActivity::DeleteActivity( long id )
{
	// Ensure there is no link to this project
	if ( CRecTask::HasLinkToActivity(id) )
	{
		return false;
	}


	CString s;
	s.Format("DELETE * FROM Activity WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();

	return true;
}
