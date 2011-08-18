// $Id: DaoRecordsetEx.h,v 1.1 2005/01/13 12:23:20 lbrucher Exp $
//
#if !defined(AFX_DAORECORDSETEX_H__C5E2BB74_B5A8_4B40_93EC_1FD962ACDB4B__INCLUDED_)
#define AFX_DAORECORDSETEX_H__C5E2BB74_B5A8_4B40_93EC_1FD962ACDB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


extern CDaoDatabase* g_pTimeSheetDB;

class CDaoRecordsetEx : public CDaoRecordset
{
	public:
		CDaoRecordsetEx( const CString& sDefaultSQL );
		DECLARE_DYNAMIC(CDaoRecordsetEx)

		CString GetDefaultDBName();
		CString GetDefaultSQL();

#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif


		virtual void AddNew();

	protected:

		bool DoFind( const CString& sQuery );




		CString m_sDefaultSQL;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAORECORDSETEX_H__C5E2BB74_B5A8_4B40_93EC_1FD962ACDB4B__INCLUDED_)
