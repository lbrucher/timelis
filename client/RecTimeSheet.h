// $Id: RecTimeSheet.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _CRECTIMESHEET_H_
#define _CRECTIMESHEET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"

class CRecTimeSheet : public CDaoRecordsetEx
{
public:
	static const char* DAY_NONE;
	static const char* DAY_HALF;
	static const char* DAY_FULL;


	CRecTimeSheet();
	DECLARE_DYNAMIC(CRecTimeSheet)

	bool IsFinished();

	bool FindByDate( const COleDateTime& aDate );
	bool FindByID( long id );

	static CRecTimeSheet* FindUnfinished();
	static void DeleteTimeSheet( long id );

	bool  isReportingDaySet();
	float getReportingDayHours();
	void  setReportingDayHours( float hours );


	virtual void Update();
	void UpdateNotModified();


// Field/Param Data
	//{{AFX_FIELD(CRecTimeSheet, CDaoRecordset)
	long			m_ID;
	COleDateTime	m_StartTime;
	COleDateTime    m_EndTime;
	BOOL			m_Modified;
protected:
	float 			m_ReportingHours;

	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecTimeSheet)
public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
