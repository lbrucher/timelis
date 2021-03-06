// $Id: DlgShowEvent.cpp 15 2007-12-12 21:24:08Z lbrucher $
//
#include "stdafx.h"
#include "DlgShowEvent.h"
#include "RecEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgShowEvent, CDialog)
	//{{AFX_MSG_MAP(CDlgShowEvent)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_RESCHEDULE, OnReschedule)
	ON_BN_CLICKED(IDC_SNOOZE, OnSnooze)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgShowEvent::CDlgShowEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowEvent::IDD, pParent)
{
	m_eventId = -1;
	//{{AFX_DATA_INIT(CDlgShowEvent)
	m_rescheduleDate = 0;
	m_rescheduleTime = 0;
	//}}AFX_DATA_INIT
}



// ////////////////////////////////////////////////////////////////////////////
//
void CDlgShowEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowEvent)
	DDX_Control(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_SNOOZE_TIME, m_SnoozeTime);
	DDX_DateTimeCtrl(pDX, IDC_RESCHEDULE_DATE, m_rescheduleDate);
	DDX_DateTimeCtrl(pDX, IDC_RESCHEDULE_TIME, m_rescheduleTime);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgShowEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();

	AddSnoozeTime("5 minutes", 5);
	AddSnoozeTime("10 minutes", 10);
	AddSnoozeTime("15 minutes", 15);
	AddSnoozeTime("30 minutes", 30);
	AddSnoozeTime("1 hour", 60);
	AddSnoozeTime("2 hours", 120);
	AddSnoozeTime("4 hours", 240);
	AddSnoozeTime("8 hours", 480);
	AddSnoozeTime("1 day", 24*60);
	AddSnoozeTime("2 day", 48*60);
	AddSnoozeTime("3 day", 36*60);
	AddSnoozeTime("4 day", 48*60);
	m_SnoozeTime.SetCurSel(0);

	CRecEvent rec;
	if ( ! rec.FindByID(m_eventId) )
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	m_Text.SetWindowText(rec.m_text);

	SYSTEMTIME st;
	rec.m_trigger.GetAsSystemTime(st);
	m_rescheduleDate = CTime(st);
	m_rescheduleTime = CTime(st);

	UpdateData(FALSE);

	m_Text.SetSel(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgShowEvent::AddSnoozeTime( const char* text, DWORD minutes )
{
	int n = m_SnoozeTime.AddString(text);
	m_SnoozeTime.SetItemData(n, minutes);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgShowEvent::OnDelete() 
{
	CRecEvent::DeleteEvent(m_eventId);
	EndDialog(IDOK);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgShowEvent::OnReschedule() 
{
	UpdateData(TRUE);

	CRecEvent rec;
	if ( rec.FindByID(m_eventId) )
	{
		rec.Edit();
		rec.m_trigger = COleDateTime( m_rescheduleDate.GetYear(), m_rescheduleDate.GetMonth(), m_rescheduleDate.GetDay(),
									  m_rescheduleTime.GetHour(), m_rescheduleTime.GetMinute(), m_rescheduleTime.GetSecond() );
		m_Text.GetWindowText(rec.m_text);
		rec.m_fired = FALSE;
		rec.Update();
	}
	
	EndDialog(IDOK);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgShowEvent::OnSnooze() 
{
	UpdateData(TRUE);

	int nSel = m_SnoozeTime.GetCurSel();
	if (nSel == -1)
		return;

	CRecEvent rec;
	if ( rec.FindByID(m_eventId) )
	{
		int minutes = (int) m_SnoozeTime.GetItemData(nSel);

		rec.Edit();
		rec.m_trigger = COleDateTime::GetCurrentTime() + COleDateTimeSpan(0,0,minutes, 0);
		m_Text.GetWindowText(rec.m_text);
		rec.m_fired = FALSE;
		rec.Update();
	}
	
	EndDialog(IDOK);
}
