// $Id: RecPauses.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "RecPauses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRecPauses, CDaoRecordsetEx)

CRecPauses::CRecPauses() :
	CDaoRecordsetEx("[Pauses]")
{
	//{{AFX_FIELD_INIT(CRecTimeSheet)
	m_ID = 0;
	m_SheeterID = 0;
	m_Begin = (DATE)0;
	m_End = (DATE)0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


void CRecPauses::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecPauses)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long    (pFX, _T("[ID]"), m_ID);
	DFX_Long    (pFX, _T("[SheeterID]"), m_SheeterID);
	DFX_DateTime(pFX, _T("[Begin]"), m_Begin);
	DFX_DateTime(pFX, _T("[End]"), m_End);
	//}}AFX_FIELD_MAP
}


// ///////////////////////////////////////////////////////////////////////////
//
DWORD CRecPauses::ComputeTotalMinutes( long sheeterID )
{
	DWORD dwMinutes = 0;
	CString sQuery;
	sQuery.Format("SELECT * FROM Pauses WHERE SheeterID=%li", sheeterID);
	CRecPauses query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		if ((DATE)query.m_End != (DATE)0)
		{
			COleDateTimeSpan diff = query.m_End - query.m_Begin;
			dwMinutes += DWORD(diff.GetTotalMinutes())+1;
		}

		query.MoveNext();
	}
	query.Close();

	return dwMinutes;
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CRecPauses::CheckPaused( long sheeterID, bool* pbPaused, COleDateTime* pPauseTime )
{
	*pbPaused = false;
	CString sQuery;
	sQuery.Format("SELECT * FROM Pauses WHERE SheeterID=%li", sheeterID);
	CRecPauses query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while(!query.IsEOF())
	{
		if ((DATE)query.m_End == (DATE)0)
		{
			*pbPaused   = true;
			*pPauseTime = query.m_Begin;
			break;
		}
		query.MoveNext();
	}
	query.Close();

	return *pbPaused;
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CRecPauses::FindOpenPause( long sheeterID )
{
	CString sSQL;
	sSQL.Format("SELECT * FROM Pauses WHERE SheeterID=%li", sheeterID);

	Open(dbOpenDynaset, sSQL, 0);
	while(!IsEOF())
	{
		if ((DATE)m_End == (DATE)0)
		{
			return true;
		}

		MoveNext();
	}

	return false;
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecPauses::FindPauses( long sheeterID, CDWordArray& pauseIDs )
{
	pauseIDs.RemoveAll();

	CString sQuery;
	sQuery.Format("SELECT * FROM Pauses WHERE SheeterID=%li", sheeterID);

	CRecPauses query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while(!query.IsEOF())
	{
		pauseIDs.Add( DWORD(query.m_ID) );
		query.MoveNext();
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecPauses::AddPause( long sheeterID, const COleDateTime& from, const COleDateTime& to )
{
	CRecPauses recPause;
	recPause.AddNew();
	recPause.m_SheeterID	= sheeterID;
	recPause.m_Begin		= from;
	recPause.m_End			= to;
	recPause.Update();
	recPause.Close();
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecPauses::DeletePause( long id )
{
	CString s;
	s.Format("DELETE * FROM Pauses WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();
}
