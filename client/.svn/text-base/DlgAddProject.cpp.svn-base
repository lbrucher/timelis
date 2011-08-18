// $Id: DlgAddProject.cpp,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgAddProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddProject dialog


CDlgAddProject::CDlgAddProject(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddProject)
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddProject)
	DDX_Text(pDX, IDC_NAME, m_sName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddProject, CDialog)
	//{{AFX_MSG_MAP(CDlgAddProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddProject message handlers

BOOL CDlgAddProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_sTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
