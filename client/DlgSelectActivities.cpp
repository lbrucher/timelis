// $Id: DlgSelectActivities.cpp,v 1.1 2005/01/11 14:42:24 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgSelectActivities.h"
#include "RecProject.h"
#include "ActivityUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgSelectActivities, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectActivities)
	ON_BN_CLICKED(IDC_SHOWDISABLEDACTIVITIES, OnShowdisabledactivities)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgSelectActivities::CDlgSelectActivities(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectActivities::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectActivities)
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgSelectActivities::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectActivities)
	DDX_Control(pDX, IDC_SHOWDISABLEDACTIVITIES, m_CtrlShowDisabled);
	DDX_Control(pDX, IDC_ACTIVITIES, m_Activities);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgSelectActivities::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_CtrlShowDisabled.SetCheck(1);
	RefreshActivities();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgSelectActivities::RefreshActivities()
{
	m_Activities.ResetContent();

	// Fill in projects/activities
	if (m_CtrlShowDisabled.GetCheck() == 0)
		FillEnabledProjectsList(m_Activities, m_itemDatas);
	else
		FillAllProjectsList(m_Activities, m_itemDatas);

	// Preselect activities and projects
	for(int i=0; i<m_Activities.GetCount(); i++)
	{
		DWORD id = (DWORD) GetListBoxItemID(m_Activities, i, m_itemDatas);

		if ( IsListBoxActivity(m_Activities, i, m_itemDatas) )
		{
			for( int j=0; j<m_activityIDs.GetSize(); j++ )
			{
				if (m_activityIDs[j] == id)
				{
					m_Activities.SetSel(i, TRUE);
					break;
				}
			}
		}
		else if ( IsListBoxProject(m_Activities, i, m_itemDatas) )
		{
			for( int j=0; j<m_projectIDs.GetSize(); j++ )
			{
				if (m_projectIDs[j] == id)
				{
					m_Activities.SetSel(i, TRUE);
					break;
				}
			}
		}
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgSelectActivities::OnOK()
{
	m_projectIDs.RemoveAll();
	m_activityIDs.RemoveAll();

	// Retrieve projects
	int nSelItems = m_Activities.GetSelCount();
	if (nSelItems == 0)
	{
		AfxMessageBox("Please select at least one project or activity!");
		return;
	}

	int *pSelectedItems = new int[nSelItems];
	m_Activities.GetSelItems( nSelItems, pSelectedItems );

	for(int i=0; i<nSelItems; i++)
	{
		long id = GetListBoxItemID(m_Activities, pSelectedItems[i], m_itemDatas);

		if ( IsListBoxActivity(m_Activities, pSelectedItems[i], m_itemDatas) )
			m_activityIDs.Add(id);
		else if ( IsListBoxProject(m_Activities, pSelectedItems[i], m_itemDatas) )
			m_projectIDs.Add(id);
	}

	delete [] pSelectedItems;

	CDialog::OnOK();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgSelectActivities::OnShowdisabledactivities() 
{
	RefreshActivities();
}
