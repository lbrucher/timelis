// $Id: DaoRecordsetEx.cpp,v 1.1 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "DaoRecordsetEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDaoRecordsetEx, CDaoRecordset)


// ////////////////////////////////////////////////////////////////////////////
//
CDaoRecordsetEx::CDaoRecordsetEx( const CString& sDefaultSQL ) :
	CDaoRecordset(g_pTimeSheetDB),
	m_sDefaultSQL(sDefaultSQL)
{
}


// ///////////////////////////////////////////////////////////////////////////
//
CString CDaoRecordsetEx::GetDefaultDBName()
{
	return _T("");
}

// ///////////////////////////////////////////////////////////////////////////
//
CString CDaoRecordsetEx::GetDefaultSQL()
{
	return m_sDefaultSQL;
}


// ///////////////////////////////////////////////////////////////////////////
//
#ifdef _DEBUG
void CDaoRecordsetEx::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoRecordsetEx::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG



// ///////////////////////////////////////////////////////////////////////////
//
void CDaoRecordsetEx::AddNew()
{
	Close();
	Open();
	CDaoRecordset::AddNew();
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CDaoRecordsetEx::DoFind( const CString& sQuery )
{
	Close();
	Open(dbOpenDynaset, sQuery, 0);
	if (IsEOF())
	{
		Close();
		return false;
	}
	return true;
}
