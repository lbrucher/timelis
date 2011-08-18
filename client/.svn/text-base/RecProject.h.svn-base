// $Id: RecProject.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _CRECPROJECT_H_
#define _CRECPROJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DaoRecordsetEx.h"
#include "RecActivity.h"

class CProjectInfo;
class CProjectInfoSimple;
typedef CArray< CProjectInfo, CProjectInfo& > TProjectInfoArray;
typedef CArray< CProjectInfoSimple, CProjectInfoSimple& > TProjectInfoSimpleArray;

class CRecProject : public CDaoRecordsetEx
{
public:
	CRecProject();
	DECLARE_DYNAMIC(CRecProject)

	bool FindByID( long id );
	bool FindByMasterID( long masterID );
	bool FindByName( const CString& name );

	static void AddProject( CString name );
	static bool DeleteProject( long id );

//	static void FindEnabledProjects( CDWordArray& ids, CStringArray& names );
	static CString GetProjectName( long projectID );
	static void FindAllProjects( TProjectInfoArray& projects );
	static void FindEnabledProjects( TProjectInfoArray& projects );
	static void FindLocallyModifiedProjects( TProjectInfoSimpleArray& projects );


// Field/Param Data
	//{{AFX_FIELD(CRecProject, CDaoRecordset)
	long	m_ID;
	long	m_MasterID;
	CString	m_Name;
//	BOOL	m_LocallyModified;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecProject)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL


protected:
	static void DoFindProjects( TProjectInfoArray& projects, bool bEnabledOnly );

};



class CProjectInfoSimple
{
public:
	long	id;
	CString	name;

	CProjectInfoSimple() {}
	CProjectInfoSimple( long _id, const CString& _name ) :
		id(_id),
		name(_name)
	{}

	CProjectInfoSimple( const CRecProject& rec ) :
		id(rec.m_ID),
		name(rec.m_Name)
	{}

	CProjectInfoSimple& operator=( const CProjectInfoSimple& info )
	{
		id = info.id;
		name = info.name;
		return *this;
	}
};

class CProjectInfo : public CProjectInfoSimple
{
public:
	TActivityInfoArray activities;


	CProjectInfo() : CProjectInfoSimple() {}
	CProjectInfo( const CProjectInfo& info ) :
		CProjectInfoSimple(info.id, info.name)
	{
		activities.Append(info.activities);
	}

	CProjectInfo( const CRecProject& rec, const TActivityInfoArray& _activities ) :
		CProjectInfoSimple(rec)
	{
		activities.Append(_activities);
	}

	CProjectInfo& operator=( const CProjectInfo& info )
	{
		id = info.id;
		name = info.name;
		activities.RemoveAll();
		activities.Append(info.activities);
		return *this;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
