// $Id: Utils.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"


char* g_sMonthNames[] = { "January","February","March","April","May","June","July","August","September","October","November","December"};
char* g_sShortMonthNames[] = {"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};


// ////////////////////////////////////////////////////////////////////////////
//
CString FormatString( const char* msg, ... )
{
	static char buffer[4096] = "";

	va_list valist;
	va_start(valist, msg);
	vsprintf(buffer, msg, valist);
	va_end(valist);

	return CString(buffer);
}


// ////////////////////////////////////////////////////////////////////////////
//
COleDateTime GetNowTime()
{
	return COleDateTime::GetCurrentTime();
}


// ///////////////////////////////////////////////////////////////////////////
//
CString FormatDate( int yy, int mm, int dd )
{
	CString s;
	s.Format("%04i/%02i/%02i", yy, mm, dd);
	return s;
}

// ///////////////////////////////////////////////////////////////////////////
//
CString FormatDate( const COleDateTime& dt )
{
	return FormatDate(dt.GetYear(), dt.GetMonth(), dt.GetDay());
}


// ///////////////////////////////////////////////////////////////////////////
//
CString FormatDateMDY( const COleDateTime& dt )
{
	CString s;
	s.Format("%02i/%02i/%04i", dt.GetMonth(), dt.GetDay(), dt.GetYear());
	return s;
}

// ///////////////////////////////////////////////////////////////////////////
//
CString GetDisplayDate( const COleDateTime& dt )
{
	CString s;
	s.Format("%02i/%02i/%04i", dt.GetDay(), dt.GetMonth(), dt.GetYear());
	return s;
}


// ///////////////////////////////////////////////////////////////////////////
//
CString GetDisplayShortDate( const COleDateTime& dt )
{
	CString s;
	s.Format("%02i/%02i/%02i", dt.GetDay(), dt.GetMonth(), dt.GetYear()-2000);
	return s;
}


// ///////////////////////////////////////////////////////////////////////////
//
CString GetWeekDay( const COleDateTime& dt )
{
	static char* days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	return CString( days[dt.GetDayOfWeek()-1] );
}


// ///////////////////////////////////////////////////////////////////////////
//
CString GetDisplayTime( const COleDateTime& dt )
{
	CString s;
	s.Format("%02i:%02i", dt.GetHour(), dt.GetMinute());
	return s;
}


// ///////////////////////////////////////////////////////////////////////////
//
CString GetDisplayTime( long minutes )
{
	int hr = minutes/60;
	int mn = minutes-(hr*60);

	CString s;
	s.Format("%02i:%02i", hr, mn);
	return s;
}


// ///////////////////////////////////////////////////////////////////////////
//
static void String2HourMin( const CString& sTime, int& hr, int& min )
{
	int colon = sTime.Find(':');
	if (colon == -1)
	{
		if (sTime.GetLength() <= 2)
		{
			hr = atoi(sTime);
			min = 0;
		}
		else
		{
			hr  = atoi( sTime.Left(sTime.GetLength()-2) );
			min = atoi( sTime.Right(2) );
		}
	}
	else
	{
		hr  = atoi( sTime.Left(colon) );
		min = atoi( sTime.Mid(colon+1) );
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
COleDateTime String2Date( const CString& sDate, const CString& sTime )
{
	int hr,min;
	String2HourMin(sTime, hr, min);

	int dd,mm,yy;
	mm = atoi( sDate.Left(2) );
	dd = atoi( sDate.Mid(3,2) );
	yy = atoi( sDate.Right(4) );

	return COleDateTime(yy,mm,dd,hr,min,0);
}


// ///////////////////////////////////////////////////////////////////////////
//
int String2Minutes( const CString& sTime )
{
	int hr,min;
	String2HourMin(sTime, hr, min);
	return ((hr*60)+min);
}


// ///////////////////////////////////////////////////////////////////////////
//
COleDateTime Time2AdjustedDate( const CString& sTime, const COleDateTime& startDate )
{
	int hr,min;
	String2HourMin(sTime, hr, min);

	// If the given time is before the startDate's time, then the target date is one day further
	//
	if ((hr < startDate.GetHour()) || ((hr == startDate.GetHour()) && (min < startDate.GetMinute())))
	{
		COleDateTime dt = startDate + COleDateTimeSpan(1,0,0,0);
		return COleDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), hr, min, 0);
	}

	return COleDateTime(startDate.GetYear(), startDate.GetMonth(), startDate.GetDay(), hr, min, 0);
}


// ///////////////////////////////////////////////////////////////////////////
// Build a new date object  by copying the given date object and replacing
// its time by the given one
//
COleDateTime SetTimeOfDate( const COleDateTime& date, const CString& sTime )
{
	int hr,min;
	String2HourMin(sTime, hr, min);

	return COleDateTime(date.GetYear(), date.GetMonth(), date.GetDay(), hr, min, 0);
}


// ///////////////////////////////////////////////////////////////////////////
//
COleDateTime MaxMonthDate( int month, int year )
{
	if (++month > 12)
	{
		month = 1;
		year++;
	}

	COleDateTime date(year, month, 01, 0,0,0);
	date -= COleDateTimeSpan(0,0,1,0);

	return date;
}


// ///////////////////////////////////////////////////////////////////////////
//
void String2File( const char* pString, const char* pFilename )
{
	FILE* f = fopen(pFilename, "w+");
	fputs(pString, f);
	fclose(f);
}




#define MAX_LOCKED_WINDOWS	10
typedef CWnd* LPCWnd; 
static LPCWnd* s_pWndTop = new LPCWnd[MAX_LOCKED_WINDOWS];
static int   s_nWndTopIndex = -1;

// ///////////////////////////////////////////////////////////////////////////
//
void LockWindow( CWnd* pWnd, boolean locked )
{
	if (locked)
	{
		if (s_nWndTopIndex < MAX_LOCKED_WINDOWS-1)
			s_pWndTop[++s_nWndTopIndex] = pWnd;
	}
	else
	{
		if (s_nWndTopIndex >= 0)
		{
			if (s_pWndTop[s_nWndTopIndex] == pWnd)
				s_pWndTop[s_nWndTopIndex--] = NULL;
			else
				AfxMessageBox("Internal error while unlock window!");
		}
	}

}


// ///////////////////////////////////////////////////////////////////////////
//
CWnd* GetLockedWindow()
{
	if (s_nWndTopIndex < 0)
		return NULL;
	return s_pWndTop[s_nWndTopIndex];
}


// ///////////////////////////////////////////////////////////////////////////
//
void Time2CEdit( const COleDateTime& dt, CEdit& editCtrl )
{
	editCtrl.SetWindowText(GetDisplayTime(dt));
}


// ///////////////////////////////////////////////////////////////////////////
//
COleDateTime CEditTime2Date( CEdit& editCtrl, const COleDateTime& date )
{
	CString sTime;
	editCtrl.GetWindowText(sTime);

	return SetTimeOfDate(date, sTime);
}


// ///////////////////////////////////////////////////////////////////////////
//
COleDateTime CEditTime2AdjustedDate( CEdit& editCtrl, const COleDateTime& date )
{
	CString sTime;
	editCtrl.GetWindowText(sTime);

	return Time2AdjustedDate(sTime, date);
}
