// $Id: RecPauses.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _CRECPAUSES_H_
#define _CRECPAUSES_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"


class CRecPauses : public CDaoRecordsetEx
{
public:
	CRecPauses();
	DECLARE_DYNAMIC(CRecPauses)

	static DWORD ComputeTotalMinutes( long sheeterID );
	static bool CheckPaused( long sheeterID, bool* pbPaused, COleDateTime* pPauseTime );
	static void AddPause( long sheeterID, const COleDateTime& from, const COleDateTime& to );
	static void DeletePause( long id );
	static void FindPauses( long sheeterID, CDWordArray& pauseIDs );

	bool FindOpenPause( long sheeterID );



// Field/Param Data
	//{{AFX_FIELD(CRecPauses, CDaoRecordset)
	long			m_ID;
	long			m_SheeterID;
	COleDateTime	m_Begin;
	COleDateTime    m_End;
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
