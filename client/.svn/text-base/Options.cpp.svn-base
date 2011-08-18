// $Id: Options.cpp,v 1.1 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "Options.h"
#include "Timelis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTimelisApp theApp;


// ////////////////////////////////////////////////////////////////////////////
//
CString COptions::getReportTemplateDir()
{
	return theApp.GetProfileString("Report", "TemplateDir", "");
}

CString COptions::getReportDir()
{
	return theApp.GetProfileString("Report", "ReportDir", "");
}

CString COptions::getSyncWsdlUrl()
{
	return theApp.GetProfileString("Synchronize", "WSDLURL", "");
}

CString COptions::getSyncUsername()
{
	return theApp.GetProfileString("Synchronize", "Username", "");
}


// ////////////////////////////////////////////////////////////////////////////
//
void COptions::setReportTemplateDir( const CString& s )
{
	theApp.WriteProfileString("Report", "TemplateDir", s);
}

void COptions::setReportDir( const CString& s )
{
	theApp.WriteProfileString("Report", "ReportDir", s);
}

void COptions::setSyncWsdlUrl( const CString& s )
{
	theApp.WriteProfileString("Synchronize", "WSDLURL", s);
}

void COptions::setSyncUsername( const CString& s )
{
	theApp.WriteProfileString("Synchronize", "Username", s);
}

