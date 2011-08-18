// $Id: DlgManageProjects.cpp 13 2007-12-11 20:48:45Z lbrucher $
//
#include "stdafx.h"
#include "DlgManageProjects.h"
#include "RecProject.h"
#include "DlgAddProject.h"
#include "RecTask.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgManageProjects, CDialog)
	//{{AFX_MSG_MAP(CDlgManageProjects)
	ON_BN_CLICKED(IDC_ADDPROJECT, OnAddProject)
	ON_BN_CLICKED(IDC_DELPROJECT, OnDelproject)
	ON_BN_CLICKED(IDC_ADDACTIVITY, OnAddactivity)
	ON_BN_CLICKED(IDC_DELACTIVITY, OnDelactivity)
	ON_BN_CLICKED(IDC_ENABLEACTIVITY, OnEnableactivity)
	ON_LBN_SELCHANGE(IDC_PROJECTS, OnSelchangeProjects)
	ON_LBN_SELCHANGE(IDC_ACTIVITIES, OnSelchangeActivities)
	ON_BN_CLICKED(IDC_RENPROJECT, OnRenproject)
	ON_BN_CLICKED(IDC_RENACTIVITY, OnRenactivity)
	ON_LBN_DBLCLK(IDC_PROJECTS, OnDblclkProjects)
	ON_LBN_DBLCLK(IDC_ACTIVITIES, OnDblclkActivities)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ////////////////////////////////////////////////////////////////////////////
//
CDlgManageProjects::CDlgManageProjects(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManageProjects::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManageProjects)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManageProjects)
	DDX_Control(pDX, IDC_RENACTIVITY, m_ButRenActivity);
	DDX_Control(pDX, IDC_RENPROJECT, m_ButRenProject);
	DDX_Control(pDX, IDC_ENABLEACTIVITY, m_ButEnableActivity);
	DDX_Control(pDX, IDC_DELPROJECT, m_ButDelProject);
	DDX_Control(pDX, IDC_DELACTIVITY, m_ButDelActivity);
	DDX_Control(pDX, IDC_ADDACTIVITY, m_ButAddActivity);
	DDX_Control(pDX, IDC_ACTIVITIES, m_Activities);
	DDX_Control(pDX, IDC_PROJECTS, m_Projects);
	//}}AFX_DATA_MAP
}



// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgManageProjects::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	refreshProjectsList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::refreshProjectsList()
{
	// Clear listbox
	m_Projects.ResetContent();

	// Build list of projects
	CRecProject query;
	query.Open(dbOpenDynaset, "SELECT * FROM PROJECT", 0);

	if (!query.IsBOF())
		query.MoveFirst();

	while(!query.IsEOF())
	{
		int n = m_Projects.AddString( query.m_Name );
		m_Projects.SetItemData(n, DWORD(query.m_ID));

		query.MoveNext();
	}
	query.Close();


	// Clear selection
	m_Projects.SetSel(-1);
	m_Activities.ResetContent();
	m_Activities.SetSel(-1);

	updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::refreshActivitiesList()
{
	// Project ID
	long projectID = long( m_Projects.GetItemData(m_Projects.GetCurSel()) );

	// Clear listbox
	m_Activities.ResetContent();


	// Build list of activities
	CRecActivity query;
	query.Open(dbOpenDynaset, FormatString("select * from Activity where ProjectID=%li", projectID), 0);

	if (!query.IsBOF())
		query.MoveFirst();

	while(!query.IsEOF())
	{
		CString s;
		buildActivityName(query, s);
		int n = m_Activities.AddString(s);

		long itemData = query.m_Enabled ? query.m_ID : -query.m_ID;
		m_Activities.SetItemData(n, DWORD(itemData));

		query.MoveNext();
	}
	query.Close();

	m_Activities.SetSel(-1);
	updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::buildActivityName( const CRecActivity& rec, CString& s )
{
	if (rec.m_Enabled)
		s = rec.m_Name;
	else
		s.Format("--(%s)--", rec.m_Name);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::updateButtonsState()
{
	m_ButDelProject.EnableWindow( m_Projects.GetCurSel() != -1 );
	m_ButRenProject.EnableWindow( m_Projects.GetCurSel() != -1 );
	m_ButAddActivity.EnableWindow( m_Projects.GetCurSel() != -1 );
	m_ButDelActivity.EnableWindow( m_Activities.GetCurSel() != -1 );
	m_ButRenActivity.EnableWindow( m_Activities.GetCurSel() != -1 );
	m_ButEnableActivity.EnableWindow( m_Activities.GetCurSel() != -1 );

	// Update the Enable/Disable button text
	if (m_Activities.GetCurSel() != -1)
	{
		long itemData = (long) m_Activities.GetItemData(m_Activities.GetCurSel());
		m_ButEnableActivity.SetWindowText( itemData >= 0 ? "Disable":"Enable" );
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnAddProject() 
{
	CDlgAddProject dlg;
	dlg.m_sTitle = "Add Project";

	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_sName.IsEmpty())
		return;

	CRecProject::AddProject( dlg.m_sName );
	refreshProjectsList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnDelproject() 
{
	// Find project
	long pid = getSelectedProjectID();
	if (pid == -1)
		return;

	CRecProject project;
	if (!project.FindByID(pid))
		return;

	// Ensure project does not have activities
	CDWordArray ids;
	CRecActivity::FindActivityIDs(project.m_ID, ids, false);
	if (ids.GetSize() > 0)
	{
		AfxMessageBox("This project cannot be deleted because it still contains activities!");
		return;
	}

	// Confirmation
	CString s;
	s.Format("Are you sure you want to delete the project [%s]?", project.m_Name);
	if (AfxMessageBox(s, MB_YESNO) == IDNO)
		return;

	project.Close();

	// Perform the deletion
	CRecProject::DeleteProject(project.m_ID);
	refreshProjectsList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnAddactivity() 
{
	long pid = getSelectedProjectID();
	if (pid == -1)
		return;

	CDlgAddProject dlg;
	dlg.m_sTitle = "Add Activity";

	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_sName.IsEmpty())
		return;

	CRecActivity::AddActivity(pid, dlg.m_sName);
	refreshActivitiesList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnDelactivity() 
{
	// Retrieve activity
	long aid = getSelectedActivityID();
	if (aid == -1)
		return;

	CRecActivity rec;
	if (!rec.FindByID(aid))
		return;
	rec.Close();

	// Check delete possible
	if ( CRecTask::HasLinkToActivity(aid) )
	{
		AfxMessageBox("This activity cannot be deleted because there are still tasks linked to it!");
		return;
	}

	// Confirmation
	CString s;
	s.Format("Are you sure you want to delete the activity [%s]?", rec.m_Name);
	if (AfxMessageBox(s, MB_YESNO) == IDNO)
		return;

	// Delete
	CRecActivity::DeleteActivity(aid);
	refreshActivitiesList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnEnableactivity() 
{
	// Retrieve activity
	long aid = getSelectedActivityID();
	if (aid == -1)
		return;

	CRecActivity rec;
	if (!rec.FindByID(aid))
		return;

	// Enable/disable activity
	rec.Edit();
	rec.m_Enabled = ! rec.m_Enabled;
	rec.Update();


	// Refresh listbox
	long index = m_Activities.GetCurSel();
	refreshActivitiesList();
	m_Activities.SetCurSel(index);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnSelchangeProjects() 
{
	if (m_Projects.GetCurSel() != -1)
		refreshActivitiesList();
	else
		updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnSelchangeActivities() 
{
	updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnRenproject() 
{
	// Find project
	long pid = getSelectedProjectID();
	if (pid == -1)
		return;

	CRecProject project;
	if (!project.FindByID(pid))
		return;

	CDlgAddProject dlg;
	dlg.m_sTitle = "Rename Project";
	dlg.m_sName  = project.m_Name;

	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_sName.IsEmpty())
		return;

	project.Edit();
	project.m_Name = dlg.m_sName;
	project.Update();
	refreshProjectsList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnRenactivity() 
{
	// Retrieve activity
	long aid = getSelectedActivityID();
	if (aid == -1)
		return;

	CRecActivity rec;
	if (!rec.FindByID(aid))
		return;

	CDlgAddProject dlg;
	dlg.m_sTitle = "Rename Activity";
	dlg.m_sName  = rec.m_Name;

	if (dlg.DoModal() != IDOK)
		return;

	if (dlg.m_sName.IsEmpty())
		return;

	rec.Edit();
	rec.m_Name = dlg.m_sName;
	rec.Update();
	refreshActivitiesList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnDblclkProjects() 
{
	OnRenproject();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgManageProjects::OnDblclkActivities() 
{
	OnRenactivity();
}


// ////////////////////////////////////////////////////////////////////////////
//
long CDlgManageProjects::getSelectedProjectID()
{
	long index = m_Projects.GetCurSel();
	if (index == -1)
		return -1;
	return m_Projects.GetItemData(index);
}


// ////////////////////////////////////////////////////////////////////////////
//
long CDlgManageProjects::getSelectedActivityID()
{
	long index = m_Activities.GetCurSel();
	if (index == -1)
		return -1;
	return labs( (long)m_Activities.GetItemData(index) );
}

