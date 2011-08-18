// $Id: DlgAddEditTask.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgAddEditTask.h"
#include "RecProject.h"
#include "ActivityUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddEditTask dialog


CDlgAddEditTask::CDlgAddEditTask(CWnd* pParent /*=NULL*/) :
	CDialog(CDlgAddEditTask::IDD, pParent),
	m_nSelectedActivityID(-1),
	m_nTaskTime(-1),
	m_bAllowNoTime(false)
{
	//{{AFX_DATA_INIT(CDlgAddEditTask)
	m_sTime = _T("");
	m_sOfficialDescription = _T("");
	m_sPrivateDescription = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddEditTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddEditTask)
	DDX_Control(pDX, IDC_TIME_LABEL, m_TimeInfoLabel);
	DDX_Control(pDX, IDC_PROJECTS, m_Projects);
	DDX_Text(pDX, IDC_TIME, m_sTime);
	DDX_Text(pDX, IDC_OFFICIALDESCRIPTION, m_sOfficialDescription);
	DDX_Text(pDX, IDC_PRIVATEDESCRIPTION, m_sPrivateDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddEditTask, CDialog)
	//{{AFX_MSG_MAP(CDlgAddEditTask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddEditTask message handlers

BOOL CDlgAddEditTask::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Fill in the activity names
	TProjectInfoArray projects;
	CRecProject::FindEnabledProjects(projects);
	FillActivityList(m_Projects, projects);

	// Select the correct project
	m_Projects.SetCurSel(-1);
	if (m_nSelectedActivityID >= 0)
	{
		for(int i=0; i<m_Projects.GetCount(); i++)
		{
			if ( m_Projects.GetItemData(i) == DWORD(m_nSelectedActivityID) )
			{
				m_Projects.SetCurSel(i);
				break;
			}
		}
	}

	// Set the task time if specified
	if ((!m_bAllowNoTime) && (m_nTaskTime >= 0))
	{
		m_sTime = GetDisplayTime(m_nTaskTime);
	}

	if (!m_bAllowNoTime)
		m_TimeInfoLabel.ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddEditTask::OnOK()
{
	UpdateData(TRUE);

	int sel = m_Projects.GetCurSel();
	if (sel == -1)
	{
		AfxMessageBox("You must choose an activity!");
		m_Projects.SetFocus();
		return;
	}

	if ((!m_bAllowNoTime) && (m_sTime.IsEmpty()))
	{
		AfxMessageBox("You must enter a time spent for this task!");
		return;
	}

	m_nSelectedActivityID = (long) m_Projects.GetItemData(sel);
	CDialog::OnOK();
}
