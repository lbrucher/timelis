// $Id: DlgDeleteProject.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgDeleteProject.h"
#include "RecProject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgDeleteProject, CDialog)
	//{{AFX_MSG_MAP(CDlgDeleteProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ////////////////////////////////////////////////////////////////////////////
//
CDlgDeleteProject::CDlgDeleteProject(CWnd* pParent /*=NULL*/) :
	CDialog(CDlgDeleteProject::IDD, pParent),
	m_nSelectedProjectID(-1)
{
	//{{AFX_DATA_INIT(CDlgDeleteProject)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgDeleteProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeleteProject)
	DDX_Control(pDX, IDC_PROJECTS, m_Projects);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgDeleteProject::OnInitDialog()
{
	CDialog::OnInitDialog();

/*
	// Fill in the project names
	CDWordArray pids;
	CStringArray pnames;
	CRecProject::FindAllProjects(pids, pnames);
	for(int i=0; i<pids.GetSize(); i++)
	{
		int index = m_Projects.AddString(pnames[i]);
		DWORD pid = pids[i];
		m_Projects.SetItemData(index, pid);
	}
*/

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgDeleteProject::OnOK()
{
	int sel = m_Projects.GetCurSel();
	if (sel == -1)
	{
		AfxMessageBox("You must specify a project!");
		m_Projects.SetFocus();
		return;
	}

	m_nSelectedProjectID = (long) m_Projects.GetItemData(sel);

	CDialog::OnOK();
}
