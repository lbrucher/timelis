// $Id: DlgEvents.cpp 16 2007-12-26 09:14:10Z lbrucher $
//
#include "stdafx.h"
#include "DlgEvents.h"
#include "DlgEditEvent.h"
#include "RecEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgEvents, CDialog)
	//{{AFX_MSG_MAP(CDlgEvents)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_LBN_SELCHANGE(IDC_EVENTS, OnSelchangeEvents)
	ON_LBN_DBLCLK(IDC_EVENTS, OnDblclkEvents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CDlgEvents::CDlgEvents(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEvents::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEvents)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEvents)
	DDX_Control(pDX, IDC_MODIFY, m_ButModify);
	DDX_Control(pDX, IDC_DELETE, m_ButDelete);
	DDX_Control(pDX, IDC_ADD, m_ButAdd);
	DDX_Control(pDX, IDC_EVENTS, m_Events);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgEvents::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int tabs[] = { 54, 80 };
	m_Events.SetTabStops(2, tabs);

	refreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::refreshList() 
{
	m_Events.ResetContent();

	COleDateTime now = COleDateTime::GetCurrentTime();

	CRecEvent query;
	query.Open(dbOpenDynaset, "SELECT * FROM EVENT ORDER BY TRIGGER", 0);

	if (!query.IsBOF())
		query.MoveFirst();

	while(!query.IsEOF())
	{
		CString text;
		if (query.m_text.GetLength() > 60)
			text = query.m_text.Left(60)+"...";
		else
			text = query.m_text;

		CString s;
		s.Format("%s%02i-%3s-%02i\t%02i:%02i\t%s",
			(query.m_trigger < now ? "* ":""),
			query.m_trigger.GetDay(), g_sShortMonthNames[query.m_trigger.GetMonth()-1], query.m_trigger.GetYear(),
			query.m_trigger.GetHour(), query.m_trigger.GetMinute(),
			text);

		int n = m_Events.AddString(s);
		m_Events.SetItemData(n, DWORD(query.m_ID));

		query.MoveNext();
	}
	query.Close();


	m_Events.SetSel(-1);
	updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::updateButtonsState()
{
	m_ButDelete.EnableWindow( m_Events.GetCurSel() != -1 );
	m_ButModify.EnableWindow( m_Events.GetCurSel() != -1 );
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::OnAdd() 
{
	CDlgEditEvent dlg(this);

	// Tomorrow at 9am
	dlg.m_Date = CTime::GetCurrentTime() + CTimeSpan(1,0,0,0);
	dlg.m_Time = CTime(2000,1,1, 9,0,0);

	if ( dlg.DoModal() != IDOK )
		return;

	COleDateTime when( dlg.m_Date.GetYear(), dlg.m_Date.GetMonth(), dlg.m_Date.GetDay(),
					   dlg.m_Time.GetHour(), dlg.m_Time.GetMinute(), dlg.m_Time.GetSecond() );
	CRecEvent::AddEvent(when, dlg.m_Text);

	refreshList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::OnDelete() 
{
	int n = m_Events.GetCurSel();
	if (n == -1)
		return;

	if (AfxMessageBox("Are you sure you want to delete this event?", MB_YESNO) == IDNO)
		return;

	long id = (long) m_Events.GetItemData(n);
	CRecEvent::DeleteEvent(id);

	refreshList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::OnModify() 
{
	int n = m_Events.GetCurSel();
	if (n == -1)
		return;

	long id = (long) m_Events.GetItemData(n);

	CRecEvent rec;
	if (! rec.FindByID(id) )
		return;

	CDlgEditEvent dlg(this);

	SYSTEMTIME st;
	rec.m_trigger.GetAsSystemTime(st);
	dlg.m_Date = CTime(st);
	dlg.m_Time = CTime(st);
	dlg.m_Text = rec.m_text;

	if ( dlg.DoModal() != IDOK )
		return;

	rec.FindByID(id);
	rec.Edit();
	rec.m_time = COleDateTime( dlg.m_Date.GetYear(), dlg.m_Date.GetMonth(), dlg.m_Date.GetDay(),
							   dlg.m_Time.GetHour(), dlg.m_Time.GetMinute(), dlg.m_Time.GetSecond() );
	rec.m_trigger = rec.m_time;
	rec.m_text = dlg.m_Text;
	rec.m_fired = FALSE;
	rec.Update();

	refreshList();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::OnSelchangeEvents() 
{
	updateButtonsState();
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEvents::OnDblclkEvents() 
{
	OnModify();
}
