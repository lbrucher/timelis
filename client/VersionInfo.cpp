// $Id: VersionInfo.cpp,v 1.1 2005/01/13 17:50:08 lbrucher Exp $
//
#include "stdafx.h"
#include "VersionInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ////////////////////////////////////////////////////////////////////////////
//
CVersionInfo::CVersionInfo( const CString& sFilename, const CString& sLanguageCodepage )
{
	ExtractInfo(sFilename, sLanguageCodepage);
}


// ////////////////////////////////////////////////////////////////////////////
//
CVersionInfo::CVersionInfo( HINSTANCE hModuleInstance, const CString& sLanguageCodepage )
{
	char pFilename[1024];
    if ( ::GetModuleFileName(hModuleInstance, pFilename, 1024) > 0 )
		ExtractInfo(pFilename, sLanguageCodepage);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CVersionInfo::ExtractInfo( const char* pFilename, const CString& sLanguageCodepage )
{
    DWORD dwDummy;
	DWORD dwSize = ::GetFileVersionInfoSize((char*)pFilename, &dwDummy);
	if (dwSize > 0)
	{
		char *pBuffer = new char[dwSize]; 

	    if ( ::GetFileVersionInfo((char*)pFilename, dwDummy, dwSize, (void *)pBuffer) )
        {
			// Get Version Number
			//
			char pBlock[512];
			UINT nTempSize;
			LPSTR pTempData;

			wsprintf(pBlock, "\\StringFileInfo\\%s\\FileVersion", sLanguageCodepage);
			VerQueryValue(pBuffer, pBlock, (LPVOID *) &pTempData, &nTempSize);
			m_sFileVersion = CString(pTempData);

			wsprintf(pBlock, "\\StringFileInfo\\%s\\ProductVersion", sLanguageCodepage);
			VerQueryValue(pBuffer, pBlock, (LPVOID *) &pTempData, &nTempSize);
			m_sProductVersion = CString(pTempData);

			wsprintf(pBlock, "\\StringFileInfo\\%s\\ProductName", sLanguageCodepage);
			VerQueryValue(pBuffer, pBlock, (LPVOID *) &pTempData, &nTempSize);
			m_sProductName = CString(pTempData);

			wsprintf(pBlock, "\\StringFileInfo\\%s\\LegalCopyright", sLanguageCodepage);
			VerQueryValue(pBuffer, pBlock, (LPVOID *) &pTempData, &nTempSize);
			m_sCopyright = CString(pTempData);
		}
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
CString CVersionInfo::GetDottedProductVersion()
{
	CString s(m_sProductVersion);
	s.Replace(',', '.');
	s.Replace(" ", "");
	return s;
}


// ////////////////////////////////////////////////////////////////////////////
//
CString CVersionInfo::GetDottedFileVersion()
{
	CString s(m_sFileVersion);
	s.Replace(',', '.');
	s.Replace(" ", "");
	return s;
}

