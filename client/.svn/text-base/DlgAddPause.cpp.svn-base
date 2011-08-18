// $Id: DlgAddPause.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgAddPause.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPause dialog


CDlgAddPause::CDlgAddPause(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddPause::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddPause)
	m_sFrom = _T("");
	m_sTo = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddPause::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddPause)
	DDX_Text(pDX, IDC_FROM, m_sFrom);
	DDX_Text(pDX, IDC_TO, m_sTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddPause, CDialog)
	//{{AFX_MSG_MAP(CDlgAddPause)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPause message handlers
