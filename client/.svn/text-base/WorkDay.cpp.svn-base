// $Id: WorkDay.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "WorkDay.h"
#include "RecPauses.h"


CWorkDay* CWorkDay::m_pCurrentDay = NULL;


// ///////////////////////////////////////////////////////////////////////////
//
CWorkDay::CWorkDay( const COleDateTime& startDate ) :
	m_pRec(NULL),
	m_bPaused(false),
	m_dwPauseMinutes(0)
{
	m_pRec = new CRecTimeSheet;
	if (m_pRec->FindByDate(startDate))
	{
		delete m_pRec;
		m_pRec = NULL;
	}
	else
	{
		m_pRec->AddNew();

		m_pRec->m_StartTime		= startDate;
		m_pRec->m_EndTime		= COleDateTime();

		m_pRec->Update();
		m_pRec->SetBookmark( m_pRec->GetLastModifiedBookmark() );
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
CWorkDay::CWorkDay( CRecTimeSheet* pRec ) :
	m_pRec(pRec)
{
	m_dwPauseMinutes = CRecPauses::ComputeTotalMinutes(m_pRec->m_ID);

	CRecPauses::CheckPaused(m_pRec->m_ID, &m_bPaused, &m_pausedTime);
}


// ///////////////////////////////////////////////////////////////////////////
//
CWorkDay::~CWorkDay()
{
	if (m_pRec != NULL)
	{
		m_pRec->Close();
		delete m_pRec;
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
long CWorkDay::getTotalWorkTime()
{
	return getTotalWorkTime( GetNowTime() );
}


// ///////////////////////////////////////////////////////////////////////////
//
long CWorkDay::getTotalWorkTime( const COleDateTime& dt )
{
	if (m_pRec == NULL)
		return 0;

	COleDateTime now = dt;
	if (m_bPaused)
	{
		// If currently pause, do not compute the total time from the start until now
		// but until the start of the pause.
		//
		CRecPauses rec;
		if (rec.FindOpenPause(m_pRec->m_ID))
		{
			now = rec.m_Begin;
		}
	}

	COleDateTimeSpan diff = now - m_pRec->m_StartTime;
	diff = diff - COleDateTimeSpan(0, 0, m_dwPauseMinutes, 0);

	return (long)diff.GetTotalMinutes();
}


// ///////////////////////////////////////////////////////////////////////////
//
long CWorkDay::getTotalWorkTime( const CRecTimeSheet& rec )
{
	if ( (DATE)rec.m_EndTime == (DATE)0 )
		return 0;

	COleDateTimeSpan diff = rec.m_EndTime - rec.m_StartTime;
	diff = diff - COleDateTimeSpan(0, 0, CRecPauses::ComputeTotalMinutes(rec.m_ID), 0);

	return (long)diff.GetTotalMinutes();
}

/*
// ///////////////////////////////////////////////////////////////////////////
//
CWorkDay* CWorkDay::getUnfinishedDay()
{
	CRecTimeSheet* pRec = CRecTimeSheet::FindUnfinished();
	if (pRec == NULL)
		return NULL;

	return new CWorkDay(pRec);
}
*/

// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::initCurrentDay()
{
	if (m_pCurrentDay != NULL)
	{
		AfxMessageBox("ERROR! CWorkDay::initCurrentDay() called twice!");
		return;
	}

	CRecTimeSheet* pRec = CRecTimeSheet::FindUnfinished();
	if (pRec == NULL)
		return;

	m_pCurrentDay = new CWorkDay(pRec);
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::shutdown()
{
	if (m_pCurrentDay != NULL)
	{
		delete m_pCurrentDay;
		m_pCurrentDay = NULL;
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::reopenDay( const COleDateTime& date )
{
	if (m_pCurrentDay != NULL)
		return;

	CRecTimeSheet* pRec = new CRecTimeSheet();
	if (!pRec->FindByDate(date))
	{
		delete pRec;
		return;
	}

	// Save the original end time
	COleDateTime originalEnd = pRec->m_EndTime;


	// Reset the end time to zero
	pRec->Edit();
	pRec->m_EndTime = COleDateTime();
	pRec->Update();


	// Create a new Work Day
	m_pCurrentDay = new CWorkDay(pRec);


	// Retrieve the original end time and start a pause from that time.
	if (!m_pCurrentDay->isPaused())
	{
		m_pCurrentDay->pauseOrResume(originalEnd);
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::pauseOrResume( const COleDateTime& dt )
{
	if (m_pRec == NULL)
		return;

	if (m_bPaused)
	{
		// Terminate pause
		//
		CRecPauses rec;
		if ( ! rec.FindOpenPause(m_pRec->m_ID) )
		{
			AfxMessageBox("There is currently no pause...!");
		}
		else
		{
			rec.Edit();
			rec.m_End = dt;
			rec.Update();
			rec.Close();

			m_dwPauseMinutes = CRecPauses::ComputeTotalMinutes(m_pRec->m_ID);
		}

		m_bPaused = false;
	}
	else
	{
		// Start a new pause
		//
		CRecPauses rec;
		rec.AddNew();

		rec.m_SheeterID	= m_pRec->m_ID;
		rec.m_Begin		= dt;
		rec.m_End		= COleDateTime();

		rec.Update();
		rec.Close();

		m_pausedTime     = dt;
		m_bPaused        = true;
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::pausesChanged()
{
	// This gets called when the list of pauses have been changed from the outside.
	// Refresh our internal data accordingly
	//
	m_dwPauseMinutes = CRecPauses::ComputeTotalMinutes(m_pRec->m_ID);
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::finishDay( const COleDateTime& dt )
{
	if (m_pRec == NULL)
		return;

	COleDateTime dtEnd = dt;


	// See if there is a pause going on
	//
	CRecPauses recPause;
	if ( recPause.FindOpenPause(m_pRec->m_ID) )
	{
		// Get rid of the pause and make the day finish at the pause start time
		dtEnd = recPause.m_Begin;
		long id = recPause.m_ID;
		recPause.Close();

		CRecPauses::DeletePause(id);
	}

	m_pRec->Edit();
	m_pRec->m_EndTime = dtEnd;
	m_pRec->Update();
}



// ///////////////////////////////////////////////////////////////////////////
//
CWorkDay* CWorkDay::startDay( const COleDateTime& dt )
{
	if (m_pCurrentDay != NULL)
	{
		AfxMessageBox("Please finish the current day first!");
		return NULL;
	}

	// Verify the given work day has not already been used
	CRecTimeSheet rec;
	if (rec.FindByDate(dt))
	{
		AfxMessageBox("There is already a work day on that date!");
		return NULL;
	}

	// Create a new work day
	m_pCurrentDay = new CWorkDay(dt);
	if (m_pCurrentDay->getRec() == NULL)
	{
		delete m_pCurrentDay;
		m_pCurrentDay = NULL;
		AfxMessageBox("Error creating a WorkDay object!");
		return NULL;
	}

	return m_pCurrentDay;
}


// ///////////////////////////////////////////////////////////////////////////
//
void CWorkDay::endDay( const COleDateTime& dt )
{
	if (m_pCurrentDay == NULL)
	{
		AfxMessageBox("Cannot finish a day that has not started!");
		return;
	}


	m_pCurrentDay->finishDay(dt);
	delete m_pCurrentDay;
	m_pCurrentDay = NULL;
}

