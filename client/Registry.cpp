// $Id: Registry.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// ////////////////////////////////////////////////////////////////////////////
//
CRegistry::CRegistry( const CString& sKey, HKEY hBaseKey ) :
	m_hKey(0)
{
	if ( RegOpenKeyEx( hBaseKey, sKey, 0, KEY_ALL_ACCESS, &m_hKey) != ERROR_SUCCESS )
	{
		// Try re-create the key
		//
		RegCreateKey(hBaseKey, sKey, &m_hKey);
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
CRegistry::~CRegistry()
{
	RegCloseKey(m_hKey);
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CRegistry::SetValue( const char *pValueName, bool bValue )
{
	DWORD dwValue = DWORD(bValue ? 1:0);
	return bool( RegSetValueEx(m_hKey, pValueName, 0, REG_DWORD, LPBYTE(&dwValue), sizeof(DWORD)) == ERROR_SUCCESS );
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CRegistry::SetValue( const char *pValueName, DWORD dwValue )
{
	return bool( RegSetValueEx(m_hKey, pValueName, 0, REG_DWORD, LPBYTE(&dwValue), sizeof(DWORD)) == ERROR_SUCCESS );
}


// ///////////////////////////////////////////////////////////////////////////
//
bool CRegistry::SetValue( const char *pValueName, double dValue )
{
	CString s;
	s.Format("%f", dValue);
	return bool( RegSetValueEx(m_hKey, pValueName, 0, REG_SZ, LPBYTE( (LPCSTR)s ), s.GetLength()+1) == ERROR_SUCCESS );
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CRegistry::SetValue( const char *pValueName, char *pValue )
{
	return bool( RegSetValueEx(m_hKey, pValueName, 0, REG_SZ, LPBYTE(pValue), lstrlen(pValue)+1) == ERROR_SUCCESS );
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CRegistry::SetValue( const char *pValueName, const CString& sValue )
{
	return bool( RegSetValueEx(m_hKey, pValueName, 0, REG_SZ, LPBYTE( (LPCSTR)sValue ), sValue.GetLength()+1) == ERROR_SUCCESS );
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CRegistry::GetValue( const char *pValueName, bool bDefault )
{
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwValue;

	if ( RegQueryValueEx(m_hKey, pValueName, 0, &dwType, LPBYTE(&dwValue), &dwSize) == ERROR_SUCCESS )
		return bool( dwValue != 0 );

	return bDefault;
}


// ////////////////////////////////////////////////////////////////////////////
//
DWORD CRegistry::GetValue( const char *pValueName, DWORD dwDefault )
{
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwValue;

	if ( RegQueryValueEx(m_hKey, pValueName, 0, &dwType, LPBYTE(&dwValue), &dwSize) == ERROR_SUCCESS )
		return dwValue;

	return dwDefault;
}


// ////////////////////////////////////////////////////////////////////////////
//
double CRegistry::GetValue( const char *pValueName, double dDefault )
{
	char  pValue[64];
	DWORD dwType = REG_SZ;
	DWORD dwSize = 64;

	if ( RegQueryValueEx(m_hKey, pValueName, 0, &dwType, LPBYTE(pValue), &dwSize) == ERROR_SUCCESS )
		return atof( pValue );

	return dDefault;
}


// ////////////////////////////////////////////////////////////////////////////
//
CString CRegistry::GetValue( const char *pValueName, const char *pDefault )
{
	char  pValue[1024];
	DWORD dwType = REG_SZ;
	DWORD dwSize = 1024;

	if ( RegQueryValueEx(m_hKey, pValueName, 0, &dwType, LPBYTE(pValue), &dwSize) == ERROR_SUCCESS )
		return CString(pValue);

	return CString(pDefault);
}
