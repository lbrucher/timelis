// $Id: Utils.h,v 1.1 2005/01/13 12:23:20 lbrucher Exp $
//
#ifndef _UTILS_H_
#define _UTILS_H_



#define TS_ERROR(msg, retval)		{ log(msg); AfxMessageBox(msg); return retval; }

extern char* g_sMonthNames[];
extern char* g_sShortMonthNames[];

typedef struct {
	int hour;
	int minute;
} TTime;

CString FormatString( const char* msg, ... );
CString GetDisplayDate( const COleDateTime& dt );
CString GetDisplayShortDate( const COleDateTime& dt );
CString GetWeekDay( const COleDateTime& dt );
CString GetDisplayTime( const COleDateTime& dt );
CString GetDisplayTime( long minutes );
CString FormatDate( const COleDateTime& dt );
CString FormatDate( int yy, int mm, int dd );
CString FormatDateMDY( const COleDateTime& dt );
COleDateTime String2Date( const CString& sDate, const CString& sTime );
int String2Minutes( const CString& sTime );
COleDateTime GetNowTime();
COleDateTime MaxMonthDate( int month, int year );

// Build a new date object by copying the given date object and replacing
// its time by the given one.
// If the given time is earlier than the startDate's, the returned date object
// is one day further.
COleDateTime Time2AdjustedDate( const CString& sTime, const COleDateTime& startDate );

// Build a new date object by copying the given date object and replacing
// its time by the given one
COleDateTime SetTimeOfDate( const COleDateTime& date, const CString& sTime );


// Save the given string in a file with the given filename
void String2File( const char* pString, const char* pFilename );


void Time2CEdit( const COleDateTime&, CEdit& );

//TTime CEdit2Time( CEdit& );

COleDateTime CEditTime2Date( CEdit&, const COleDateTime& date );
COleDateTime CEditTime2AdjustedDate( CEdit&, const COleDateTime& date );


// Lock/unlock the given window
void LockWindow( CWnd*, boolean );
CWnd* GetLockedWindow();


#endif
