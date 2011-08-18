// $Id: DlgSynchronize.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgSynchronize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSynchronize dialog


CDlgSynchronize::CDlgSynchronize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSynchronize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSynchronize)
	m_bGetProjects = FALSE;
	m_bSendTimesheet = FALSE;
	m_nSendType = -1;
	m_SendAllTo = COleDateTime::GetCurrentTime();
	m_SendAllFrom = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgSynchronize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSynchronize)
	DDX_Check(pDX, IDC_GETPROJECTS, m_bGetProjects);
	DDX_Check(pDX, IDC_SENDTIMESHEET, m_bSendTimesheet);
	DDX_Radio(pDX, IDC_SEND_NEW, m_nSendType);
	DDX_DateTimeCtrl(pDX, IDC_SENDALL_TO, m_SendAllTo);
	DDX_DateTimeCtrl(pDX, IDC_SENDALL_FROM, m_SendAllFrom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSynchronize, CDialog)
	//{{AFX_MSG_MAP(CDlgSynchronize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSynchronize message handlers

void CDlgSynchronize::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

BOOL CDlgSynchronize::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
