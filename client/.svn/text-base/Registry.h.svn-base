// $Id: Registry.h,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#ifndef __WC_REGISTRY_H__
#define __WC_REGISTRY_H__

#if _MSC_VER > 1000
#pragma once
#endif


class CRegistry
{
	public:

		CRegistry( const CString& sKey, HKEY hBaseKey = HKEY_LOCAL_MACHINE );
		virtual ~CRegistry();


		bool SetValue( const char *pValueName, bool  bValue  );
		bool SetValue( const char *pValueName, DWORD dwValue );
		bool SetValue( const char *pValueName, double dValue );
		bool SetValue( const char *pValueName, char  *pValue );
		bool SetValue( const char *pValueName, const CString& sValue );

		bool    GetValue( const char *pValueName, bool bDefault );
		DWORD   GetValue( const char *pValueName, DWORD dwDefault );
		double  GetValue( const char *pValueName, double dDefault );
		CString GetValue( const char *pValueName, const char *pDefault );

	protected:

		HKEY m_hKey;
};


#endif
