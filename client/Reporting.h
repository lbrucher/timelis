// $Id: Reporting.h,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#if !defined(AFX_REPORTING_H__1FAF8AB9_6286_4D13_9DDB_1B8190A7A853__INCLUDED_)
#define AFX_REPORTING_H__1FAF8AB9_6286_4D13_9DDB_1B8190A7A853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecTimeSheet.h"
#include "RecTask.h"

class CReporting
{
	public:
		CReporting();
		virtual ~CReporting();

		const CString&      GetXmlFilename()		{ return m_sXmlFilename; }
		const CString&      GetXslFilename()		{ return m_sXslFilename; }
		const COleDateTime&	GetFilterFrom()			{ return m_FilterFrom; }
		const COleDateTime& GetFilterTo()			{ return m_FilterTo; }


		void setUseActualDayDuration( bool bEnable );
		void setXmlFilename( const CString& filename );
		void setXslFilename( const CString& filename );
		void setFilter( const COleDateTime& from , const COleDateTime& to );
		void setActivities( const CDWordArray& activityIDs );

		bool isReady();
		bool create();

	protected:

		bool executeDays( CRecTimeSheet& query, CStdioFile& file, float& numDays );
		bool executeProjectTotals( CRecTimeSheet& query, CStdioFile& file );

		bool IsTaskToReport( const CRecTask& task );
		void WriteLine( CStdioFile& file, const char* msg, ... );


		CString m_sXmlFilename;
		CString m_sXslFilename;
		bool    m_bShowActualDayDuration;

		COleDateTime m_FilterFrom;
		COleDateTime m_FilterTo;
		CDWordArray  m_FilterActivities;
};

#endif // !defined(AFX_REPORTING_H__1FAF8AB9_6286_4D13_9DDB_1B8190A7A853__INCLUDED_)
