// $Id: DlgPauses.cpp,v 1.2 2005/01/13 12:23:20 lbrucher Exp $
//
#include "stdafx.h"
#include "timelis.h"
#include "DlgPauses.h"
#include "RecPauses.h"
#include "RecTimeSheet.h"
#include "DlgAddPause.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTimelisApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgPauses dialog


CDlgPauses::CDlgPauses( long sheeterID, CWnd* pParent ) :
	CDialog(CDlgPauses::IDD, pParent),
	m_nSheeterID(sheeterID),
	m_bModified(false)
{
	//{{AFX_DATA_INIT(CDlgPauses)
	m_sLabel = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPauses::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPauses)
	DDX_Control(pDX, IDC_PAUSES, m_Pauses);
	DDX_Text(pDX, IDC_LABEL, m_sLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPauses, CDialog)
	//{{AFX_MSG_MAP(CDlgPauses)
	ON_BN_CLICKED(IDADDNEW, OnAddnew)
	ON_BN_CLICKED(IDDELETE, OnDelete)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPauses message handlers

BOOL CDlgPauses::OnInitDialog()
{
	CDialog::OnInitDialog();

	refreshPauses();

	CRecTimeSheet rec;
	if (rec.FindByID(m_nSheeterID))
		m_sLabel.Format("Pauses for %s", GetDisplayShortDate(rec.m_StartTime));
	else
		m_sLabel.Format("Pauses");
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPauses::refreshPauses()
{
	m_Pauses.ResetContent();

	CString sQuery;
	sQuery.Format("SELECT * FROM Pauses WHERE SheeterID=%li", m_nSheeterID);
	CRecPauses query;
	query.Open( dbOpenDynaset, sQuery, 0);
	while( ! query.IsEOF() )
	{
		if ((DATE)query.m_End != (DATE)0)
		{
			COleDateTimeSpan diff = query.m_End - query.m_Begin;

			CString s;
			s.Format("%s - %s (%s)", GetDisplayTime(query.m_Begin), GetDisplayTime(query.m_End), GetDisplayTime((long)diff.GetTotalMinutes()));

			int index = m_Pauses.AddString(s);
			m_Pauses.SetItemData(index, DWORD(query.m_ID));
		}

		query.MoveNext();
	}
	query.Close();
}



void CDlgPauses::OnAddnew()
{
	CRecTimeSheet rec;
	if (!rec.FindByID(m_nSheeterID))
		return;

	CDlgAddPause dlg;
	if (dlg.DoModal() != IDOK)
		return;

	COleDateTime dtFrom = SetTimeOfDate(rec.m_StartTime, dlg.m_sFrom);
	COleDateTime dtTo   = SetTimeOfDate(rec.m_StartTime, dlg.m_sTo);

	CRecPauses::AddPause(rec.m_ID, dtFrom, dtTo);
/*
	CRecPauses recPause;
	recPause.AddNew();
	recPause.m_SheeterID	= rec.m_ID;
	recPause.m_Begin		= dtFrom;
	recPause.m_End			= dtTo;
	recPause.Update();
	recPause.Close();
*/
	m_bModified = true;
	refreshPauses();
}


void CDlgPauses::OnDelete()
{
	int sel = m_Pauses.GetCurSel();
	if (sel == LB_ERR)
		return;

	long pauseID = (long) m_Pauses.GetItemData(sel);
	CRecPauses::DeletePause(pauseID);
	m_bModified = true;
	refreshPauses();
}


void CDlgPauses::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_bModified)
	{
		// Notify app that pauses may have changed.
		theApp.GetMainWnd()->PostMessage(WM_PAUSESCHANGED, 0, LPARAM(m_nSheeterID));
	}
}
