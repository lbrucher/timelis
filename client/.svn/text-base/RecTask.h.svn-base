// $Id: RecTask.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _CRECTASK_H_
#define _CRECTASK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"


class CRecTask : public CDaoRecordsetEx
{
public:
	CRecTask();
	DECLARE_DYNAMIC(CRecTask)

	bool FindByID( long id );

	static void DeleteTask( long id );
	static void AddTask( long sheeterID, long activityID,
						 const CString& officalDescription, const CString& privateDescription,
						 long minutes );
	static void FindTasks( long sheeterID, CDWordArray& taskIDs );

	static bool HasLinkToActivity( long activityID );


// Field/Param Data
	//{{AFX_FIELD(CRecTask, CDaoRecordset)
	long		m_ID;
	long		m_SheeterID;
	long		m_ActivityID;
	CString		m_OfficialDescription;
	CString		m_PrivateDescription;
	long		m_Minutes;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecTask)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
