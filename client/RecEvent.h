// $Id: RecEvent.h 15 2007-12-12 21:24:08Z lbrucher $
//
#ifndef _CRECEVENT_H_
#define _CRECEVENT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"


class CRecEvent : public CDaoRecordsetEx
{
public:
	CRecEvent();
	DECLARE_DYNAMIC(CRecEvent)

	bool FindByID( long id );

	static void DeleteEvent( long id );
	static void AddEvent( const COleDateTime& when, const CString& text );
//	static void FindEvents( long sheeterID, CDWordArray& taskIDs );


// Field/Param Data
	//{{AFX_FIELD(CRecEvent, CDaoRecordset)
	long			m_ID;
	COleDateTime	m_time;
	COleDateTime	m_trigger;
	CString			m_text;
	BOOL			m_fired;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecEvent)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
