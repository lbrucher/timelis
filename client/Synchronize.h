// $Id: Synchronize.h,v 1.1 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _SYNCHRONIZE_H_
#define _SYNCHRONIZE_H_




class CSynchronize
{
	public:
		CSynchronize();


		// Send all locally modified projects and activities
		//
		bool sendProjects( CStringArray* pReport = NULL );


		// Retrieve all projects and activities modified since
		// the given date (all projects/activities if no date is given)
		//
		bool retrieveProjects( COleDateTime* pDate = NULL, CStringArray* pReport = NULL );



		// Send the modified timesheet data to the server
		//
		bool sendTimesheetData();



		void setPlayWhatIf( bool isPlayWhatIf );


	protected:

		// Process the response of a RetrieveProjects call
		bool updateProjectsAfterRetrieve( const char* pXmlSource, CStringArray* pReport );

		// Process the response of a SendProject call
		bool updateProjectsAfterSend( const char* pXmlSource, CStringArray* pReport );


		bool m_bPlayWhatIf;
};


#endif
