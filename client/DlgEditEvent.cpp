#include "stdafx.h"
#include "DlgEditEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDlgEditEvent, CDialog)
	//{{AFX_MSG_MAP(CDlgEditEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ////////////////////////////////////////////////////////////////////////////
//
CDlgEditEvent::CDlgEditEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditEvent)
	m_Date = 0;
	m_Text = _T("");
	m_Time = 0;
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgEditEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditEvent)
	DDX_DateTimeCtrl(pDX, IDC_EVENT_DATE, m_Date);
	DDX_Text(pDX, IDC_EVENT_TEXT, m_Text);
	DDX_DateTimeCtrl(pDX, IDC_EVENT_TIME, m_Time);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgEditEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
