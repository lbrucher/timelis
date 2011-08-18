// $Id: RecProject.cpp,v 1.3 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "RecProject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CRecProject, CDaoRecordsetEx)

CRecProject::CRecProject() :
	CDaoRecordsetEx("[Project]")
{
	//{{AFX_FIELD_INIT(CRecProject)
	m_ID = 0;
	m_MasterID = 0;
	m_Name = _T("");
//	m_LocallyModified = FALSE;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


void CRecProject::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecProject)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Long(pFX, _T("[MasterID]"), m_MasterID);
	DFX_Text(pFX, _T("[Name]"), m_Name);
//	DFX_Bool(pFX, _T("[LocallyModified]"), m_LocallyModified);
	//}}AFX_FIELD_MAP
}

bool CRecProject::FindByID( long id )
{
	return DoFind( FormatString("select * from Project where ID=%li", id) );
}

bool CRecProject::FindByMasterID( long masterID )
{
	return DoFind( FormatString("select * from Project where MasterID=%li", masterID) );
}

bool CRecProject::FindByName( const CString& name )
{
	return DoFind( FormatString("select * from Project where Name='%s'", name) );
}


CString CRecProject::GetProjectName( long projectID )
{
	CRecProject rec;
	if ( rec.FindByID(projectID) )
		return rec.m_Name;
	return "";
}


/*
void CRecProject::FindEnabledProjects( CDWordArray& ids, CStringArray& names )
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

void CRecProject::FindAllProjects( CDWordArray& ids, CStringArray& names )
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



void CRecProject::FindAllProjects( TProjectInfoArray& projects )
{
	DoFindProjects(projects, false);
}


void CRecProject::FindEnabledProjects( TProjectInfoArray& projects )
{
	DoFindProjects(projects, true);
}


void CRecProject::DoFindProjects( TProjectInfoArray& projects, bool bEnabledOnly )
{
	CRecProject query;
	query.Open( dbOpenDynaset, "SELECT * FROM Project", 0);
	while( ! query.IsEOF() )
	{
		TActivityInfoArray activities;
		CRecActivity::FindActivityInfos(query.m_ID, activities, bEnabledOnly);

		projects.Add( CProjectInfo(query, activities) );
		query.MoveNext();
	}
	query.Close();
}



void CRecProject::FindLocallyModifiedProjects( TProjectInfoSimpleArray& projects )
{
	CRecProject query;
	query.Open( dbOpenDynaset, "SELECT * FROM Project WHERE LocallyModified=TRUE", 0);
	while( ! query.IsEOF() )
	{
		projects.Add( CProjectInfoSimple(query) );
		query.MoveNext();
	}
	query.Close();
}



void CRecProject::AddProject( CString name )
{
	CRecProject rec;
	rec.FindByID(-1);
	rec.AddNew();

	rec.m_Name    = name;
//	rec.m_Enabled = TRUE;

	rec.Update();
	rec.Close();
}


bool CRecProject::DeleteProject( long id )
{
	CString s;
	s.Format("DELETE * FROM Project WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();

	return true;
}

