// $Id: RecTimeSheet.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "RecTimeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CRecTimeSheet, CDaoRecordsetEx)

CRecTimeSheet::CRecTimeSheet() :
	CDaoRecordsetEx("[TimeSheet]")
{
	//{{AFX_FIELD_INIT(CRecTimeSheet)
	m_ID = 0;
	m_StartTime = (DATE)0;
	m_EndTime = (DATE)0;
	m_ReportingHours = -1;
	m_Modified = TRUE;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

void CRecTimeSheet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecTimeSheet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long    (pFX, _T("[ID]"), m_ID);
	DFX_DateTime(pFX, _T("[StartTime]"), m_StartTime);
	DFX_DateTime(pFX, _T("[EndTime]"), m_EndTime);
	DFX_Single  (pFX, _T("[ReportingHours]"), m_ReportingHours);
	DFX_Bool    (pFX, _T("[Modified]"), m_Modified);
	//}}AFX_FIELD_MAP
}

// ///////////////////////////////////////////////////////////////////////////
//
bool CRecTimeSheet::IsFinished()
{
	return bool( (DATE)m_EndTime != (DATE)0 );
}


// ///////////////////////////////////////////////////////////////////////////
// Finder Methods
//
bool CRecTimeSheet::FindByDate( const COleDateTime& aDate )
{
	return DoFind( FormatString("select * from TimeSheet where StartTime >= #%s 0:0:0AM# AND StartTime <= #%s 23:59:59PM#",
						FormatDate(aDate), FormatDate(aDate)) );
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CRecTimeSheet::FindByID( long id )
{
	return DoFind( FormatString("select * from TimeSheet where ID=%li", id) );
}


// ///////////////////////////////////////////////////////////////////////////
//
CRecTimeSheet* CRecTimeSheet::FindUnfinished()
{
	CRecTimeSheet* pRec = NULL;
	CDaoRecordset query(g_pTimeSheetDB);
	query.Open( dbOpenDynaset, "SELECT ID FROM TimeSheet WHERE EndTime=0", 0);
	if( ! query.IsEOF() )
	{
		COleVariant vID;
		query.GetFieldValue("ID", vID);
		pRec = new CRecTimeSheet();
		if ( ! pRec->FindByID(vID.lVal) )
		{
			delete pRec;
			pRec = NULL;
		}
	}
	query.Close();

	return pRec;
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CRecTimeSheet::isReportingDaySet()
{
	return (m_ReportingHours != -1);
}


// ///////////////////////////////////////////////////////////////////////////
//
float CRecTimeSheet::getReportingDayHours()
{
	if (m_ReportingHours == -1)
		return 0;

	return m_ReportingHours;
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecTimeSheet::setReportingDayHours( float hours )
{
	m_ReportingHours = hours;
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecTimeSheet::DeleteTimeSheet( long id )
{
	CString s;
	s.Format("DELETE * FROM TimeSheet WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecTimeSheet::Update()
{
	m_Modified = TRUE;
	CDaoRecordset::Update();
}


// ///////////////////////////////////////////////////////////////////////////
//
void CRecTimeSheet::UpdateNotModified()
{
	m_Modified = FALSE;
	CDaoRecordset::Update();
}

