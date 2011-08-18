// $Id: WorkDay.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#ifndef _CWORKDAY_H_
#define _CWORKDAY_H_

#include "RecTimeSheet.h"


class CWorkDay
{
	public:
		CWorkDay( const COleDateTime& startDate );
		virtual ~CWorkDay();

		CRecTimeSheet*		getRec()				{ return m_pRec; }
		bool				isPaused()				{ return m_bPaused; }
		const COleDateTime&	getPausedTime()			{ return m_pausedTime; }
		long				getTotalWorkTime();
		long				getTotalWorkTime( const COleDateTime& );

		void				pauseOrResume( const COleDateTime& dt );
		void				pausesChanged();

		static void			initCurrentDay();
		static void			shutdown();
//		static CWorkDay*	getUnfinishedDay();
		static void /*CWorkDay* */	reopenDay( const COleDateTime& date );
		static long			getTotalWorkTime( const CRecTimeSheet& rec );

		static CWorkDay*	startDay( const COleDateTime& dt );
		static void			endDay( const COleDateTime& dt );
		static CWorkDay*	getCurrentDay() { return m_pCurrentDay; }

	protected:
		CWorkDay( CRecTimeSheet* );

		void finishDay( const COleDateTime& dt );

		CRecTimeSheet*	m_pRec;
		bool			m_bPaused;			// Whether we're currently in a pause or not
		COleDateTime	m_pausedTime;		// When in pause, the pause start time
		DWORD			m_dwPauseMinutes;	// The current total number of minutes of all the completed pauses.


		static CWorkDay* m_pCurrentDay;
};


#endif
