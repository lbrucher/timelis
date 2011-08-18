// $Id: DlgNewDay.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgNewDay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgNewDay dialog


CDlgNewDay::CDlgNewDay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewDay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewDay)
	m_Date = COleDateTime::GetCurrentTime();
	m_sFrom = _T("9:00");
	m_sLength = _T("8");
	//}}AFX_DATA_INIT
}


void CDlgNewDay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewDay)
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_Date);
	DDX_Text(pDX, IDC_FROM, m_sFrom);
	DDX_Text(pDX, IDC_LENGTH, m_sLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewDay, CDialog)
	//{{AFX_MSG_MAP(CDlgNewDay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

