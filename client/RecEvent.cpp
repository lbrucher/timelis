// $Id: RecEvent.cpp 15 2007-12-12 21:24:08Z lbrucher $
//
#include "stdafx.h"
#include "RecEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRecEvent, CDaoRecordsetEx)

CRecEvent::CRecEvent() :
	CDaoRecordsetEx("[Event]")
{
	//{{AFX_FIELD_INIT(CRecEvent)
	m_ID = 0;
	m_time = (DATE)0;
	m_trigger = (DATE)0;
	m_text = _T("");
	m_fired = FALSE;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


void CRecEvent::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecEvent)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[id]"), m_ID);
	DFX_DateTime(pFX, _T("[time]"), m_time);
	DFX_DateTime(pFX, _T("[trigger]"), m_trigger);
	DFX_Text(pFX, _T("[text]"), m_text);
	DFX_Bool(pFX, _T("[fired]"), m_fired);
	//}}AFX_FIELD_MAP
}


bool CRecEvent::FindByID( long id )
{
	return DoFind( FormatString("select * from Event where ID=%li", id) );
}


void CRecEvent::DeleteEvent( long id )
{
	CString s;
	s.Format("DELETE * FROM Event WHERE ID=%li", id);

	CDaoQueryDef query(g_pTimeSheetDB);
	query.Create( "", s);
	query.Execute(dbDenyWrite | dbFailOnError);
	query.Close();
}


void CRecEvent::AddEvent( const COleDateTime& when, const CString& text )
{
	CRecEvent rec;
	rec.AddNew();

	rec.m_time = when;
	rec.m_trigger = when;
	rec.m_text = text;
	rec.m_fired = FALSE;

	rec.Update();
	rec.Close();
}
