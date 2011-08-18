// $Id: Log.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "log.h"
#include <stdarg.h>

#define LOG_FILE		_T("timesheeter.log")


// ///////////////////////////////////////////////////////////////////////////
//
void openLog()
{
}


// ///////////////////////////////////////////////////////////////////////////
//
void closeLog()
{
}


// ///////////////////////////////////////////////////////////////////////////
//
void log( const char* msg, ... )
{
#ifdef _DEBUG
	static char dbgBuffer[4096] = "";
#endif

	FILE* f = fopen(LOG_FILE, "a+");
	if (f != NULL)
	{
		SYSTEMTIME systime;
		GetSystemTime(&systime);

		fprintf(f, "%04i/%02i/%02i %02i:%02i:%02i ", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);

		va_list valist;
		va_start(valist, msg);
		vfprintf(f, msg, valist);

#ifdef _DEBUG
		vsprintf(dbgBuffer, msg, valist);
		TRACE1("%s\n", dbgBuffer);
#endif

		va_end(valist);

		fputs("\n", f);

		fclose(f);
	}
}
