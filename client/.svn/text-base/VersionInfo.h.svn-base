// $Id: VersionInfo.h,v 1.1 2005/01/13 17:50:08 lbrucher Exp $
//
#ifndef _VERSIONINFO_H_
#define _VERSIONINFO_H_

#if _MSC_VER > 1000
#pragma once
#endif

class CVersionInfo
{
	public:
		CVersionInfo( const CString& sFilename, const CString& sLanguageCodepage = "040904b0" );
		CVersionInfo( HINSTANCE hModuleInstance, const CString& sLanguageCodepage = "040904b0" );


		const CString&		GetProductVersion()				{ return m_sProductVersion; }
		const CString&		GetFileVersion()				{ return m_sFileVersion; }
		const CString&		GetProductName()				{ return m_sProductName; }
		const CString&		GetCopyright()					{ return m_sCopyright; }

		CString		GetDottedProductVersion();
		CString		GetDottedFileVersion();

	protected:

		void ExtractInfo( const char* pFilename, const CString& sLanguageCodepage );

		CString m_sProductName;
		CString m_sProductVersion;
		CString m_sFileVersion;
		CString m_sCopyright;
};

#endif
