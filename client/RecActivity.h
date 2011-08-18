// $Id: RecActivity.h,v 1.3 2005/02/03 23:31:04 lbrucher Exp $
//
#ifndef _CRECACTIVITY_H_
#define _CRECACTIVITY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"


class CActivityInfo;
typedef CArray< CActivityInfo, CActivityInfo& > TActivityInfoArray;


class CRecActivity : public CDaoRecordsetEx
{
public:
	CRecActivity();
	DECLARE_DYNAMIC(CRecActivity)

	bool FindByID( long id );
	bool FindByMasterID( long id );
	CString GetProjectName();

	static void FindActivityInfos( long projectID, TActivityInfoArray& activities, bool bEnabledOnly );
	static void FindActivityIDs( long projectID, CDWordArray& ids, bool bEnabledOnly );
	static void FindActivityMasterIDs( long projectID, CDWordArray& masterIDs, bool bEnabledOnly );
	static void FindLocallyModifiedActivities( TActivityInfoArray& activities );

	static void AddActivity( long projectID, const CString& name );
	static bool DeleteActivity( long id );

//	static void FindEnabledActivities( CDWordArray& ids, CStringArray& names );
//	static void FindAllActivities( CDWordArray& ids, CStringArray& names );


// Field/Param Data
	//{{AFX_FIELD(CRecActivity, CDaoRecordset)
	long	m_ID;
	long	m_MasterID;
	long	m_ProjectID;
	CString	m_Name;
	BOOL	m_Enabled;
	//}}AFX_FIELD
	BOOL	m_LocallyModified;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecActivity)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

};


class CActivityInfo
{
public:
	long    id;
	long    masterID;
	CString name;
	long    projectID;

	CActivityInfo() {}
	CActivityInfo( const CRecActivity& rec ) :
		id(rec.m_ID),
		masterID(rec.m_MasterID),
		name(rec.m_Name),
		projectID(rec.m_ProjectID)
	{}

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
