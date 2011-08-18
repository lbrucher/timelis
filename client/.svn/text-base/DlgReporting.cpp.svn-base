// $Id: DlgReporting.cpp,v 1.3 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "DlgReporting.h"
#include "DlgManage.h"
#include "RecProject.h"
#include "ActivityUtils.h"
#include "Reporting.h"
#include "Options.h"
#include "Registry.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static CString* s_psTempFile = NULL;

BEGIN_MESSAGE_MAP(CDlgReporting, CDialog)
	//{{AFX_MSG_MAP(CDlgReporting)
	ON_NOTIFY(NM_SETFOCUS, IDC_PERIOD_FROM, OnSetfocusPeriodFrom)
	ON_NOTIFY(NM_SETFOCUS, IDC_PERIOD_TO, OnSetfocusPeriodTo)
	ON_BN_CLICKED(IDC_SHOWDISABLEDACTIVITIES, OnShowdisabledactivities)
	ON_BN_CLICKED(IDC_VIEW, OnView)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_CBN_SETFOCUS(IDC_MONTH_NAME, OnSetfocusMonthName)
	ON_EN_SETFOCUS(IDC_MONTH_YEAR, OnSetfocusMonthYear)
	ON_BN_CLICKED(IDC_MANAGE, OnManage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




// ////////////////////////////////////////////////////////////////////////////
//
CDlgReporting::CDlgReporting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReporting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReporting)
	m_nFilter = -1;
	m_PeriodFrom = COleDateTime::GetCurrentTime();
	m_PeriodTo = COleDateTime::GetCurrentTime();
	m_bShowDisabledActivities = FALSE;
	m_nMonthYear = 0;
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReporting)
	DDX_Control(pDX, IDC_TEMPLATES, m_Templates);
	DDX_Control(pDX, IDC_MONTH_NAME, m_MonthNames);
	DDX_Control(pDX, IDC_ACTIVITIES, m_Activities);
	DDX_Radio(pDX, IDC_FILTER_MONTH, m_nFilter);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_FROM, m_PeriodFrom);
	DDX_DateTimeCtrl(pDX, IDC_PERIOD_TO, m_PeriodTo);
	DDX_Check(pDX, IDC_SHOWDISABLEDACTIVITIES, m_bShowDisabledActivities);
	DDX_Text(pDX, IDC_MONTH_YEAR, m_nMonthYear);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CDlgReporting::OnInitDialog()
{
	CDialog::OnInitDialog();

	COleDateTime now = GetNowTime();
	m_nFilter = 0;

	// Init month data
	m_nMonthYear = now.GetYear();
	for(int i=0; i<12; i++)
		m_MonthNames.AddString( g_sMonthNames[i] );
	m_MonthNames.SetCurSel(now.GetMonth()-1);

	// Init templates
	CString templateDir = COptions::getReportTemplateDir();
	if (templateDir.IsEmpty())
	{
		AfxMessageBox("Warning, no Template Directory set! Check the Options to set the directory.");
	}
	else
	{
		CString pattern;
		pattern.Format("%s\\*.xsl", templateDir);
		CFileFind finder;
		BOOL bWorking = finder.FindFile(pattern);
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			m_Templates.AddString( (LPCTSTR) finder.GetFileName() );
		}
		m_Templates.SetCurSel(0);
	}

	UpdateData(FALSE);

	RefreshActivities();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnSetfocusMonthName() 
{
	SendDlgItemMessage(IDC_FILTER_MONTH, BM_SETCHECK, 1);
	SendDlgItemMessage(IDC_FILTER_PERIOD, BM_SETCHECK, 0);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnSetfocusMonthYear() 
{
	SendDlgItemMessage(IDC_FILTER_MONTH, BM_SETCHECK, 1);
	SendDlgItemMessage(IDC_FILTER_PERIOD, BM_SETCHECK, 0);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnSetfocusPeriodFrom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SendDlgItemMessage(IDC_FILTER_MONTH, BM_SETCHECK, 0);
	SendDlgItemMessage(IDC_FILTER_PERIOD, BM_SETCHECK, 1);
	*pResult = 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnSetfocusPeriodTo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SendDlgItemMessage(IDC_FILTER_MONTH, BM_SETCHECK, 0);
	SendDlgItemMessage(IDC_FILTER_PERIOD, BM_SETCHECK, 1);
	*pResult = 0;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::RefreshActivities() 
{
	m_Activities.ResetContent();

	// Fill in projects/activities
	if (m_bShowDisabledActivities)
		FillAllProjectsList(m_Activities, m_itemDatas);
	else
		FillEnabledProjectsList(m_Activities, m_itemDatas);
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnShowdisabledactivities() 
{
	UpdateData(TRUE);
	RefreshActivities();
}


// ////////////////////////////////////////////////////////////////////////////
//
boolean CDlgReporting::BuildReport( CReporting& report ) 
{
	// Validate reporting
	//
	while( !report.isReady() )
	{
		int ret = AfxMessageBox("Some of the days in the selected period are not ready yet.\n\nWould you like to edit them?", MB_YESNOCANCEL);

		if (ret == IDCANCEL)
			return false;

		if (ret == IDNO)
			break;

		CDlgManage dlgManage;

		dlgManage.m_bReporting = true;
		dlgManage.m_PeriodFrom = report.GetFilterFrom();
		dlgManage.m_PeriodTo   = report.GetFilterTo();


		LockWindow(&dlgManage, true);
		dlgManage.DoModal();
		LockWindow(&dlgManage, false);
	}
	
	

	// Create report
	//
	report.create();

	
	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnView() 
{
	UpdateData(TRUE);

	// Get selected period
	COleDateTime from,to;
	if ( ! GetSelectedPeriod(from, to) )
		return;

	// Get selected activities
	CDWordArray selectedActivityIDs;
	if ( ! GetSelectedActivities(selectedActivityIDs) )
		return;

	// Get selected template file
	CString templateFile;
	if ( ! GetSelectedTemplate(templateFile) )
		return;

	// Generate a TEMP filename
	if (s_psTempFile == NULL)
	{
		s_psTempFile = new CString();
		char pTempPath[MAX_PATH];
		char pTempFile[MAX_PATH];

		GetTempPath(sizeof(pTempPath), pTempPath);
		GetTempFileName(pTempPath, "timesheeter", 0, pTempFile);
		DeleteFile(pTempFile);
		s_psTempFile->Format("%s.xml", pTempFile);
	}

	// Build Report
	CReporting report;
	report.setXmlFilename(*s_psTempFile);
	report.setXslFilename(templateFile);
	report.setFilter(from, to);
	report.setActivities(selectedActivityIDs);
	report.setUseActualDayDuration(false);

	if (!BuildReport(report))
		return;


	CRegistry registry("http\\shell\\open\\command", HKEY_CLASSES_ROOT);

	CString browser = registry.GetValue("", "");
	if (browser.IsEmpty())
	{
		AfxMessageBox("Cannot find location of default web browser!");
	}
	else
	{
		CString cmd = browser;

		int index = cmd.Find("%1");
		if (index == -1)
		{
			cmd.Format("%s %s", browser, report.GetXmlFilename());
		}
		else
		{
			cmd.Replace("%1", report.GetXmlFilename());
		}

		STARTUPINFO startup;
		PROCESS_INFORMATION pinfo;
		ZeroMemory(&startup, sizeof(STARTUPINFO));
		ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
		startup.cb = sizeof(STARTUPINFO);

		if (!CreateProcess(NULL, (char*)(LPCTSTR)cmd, NULL, NULL, FALSE, 0, NULL, NULL, &startup, &pinfo))
		{
			CString msg;
			msg.Format("Could not launch:\n%s", cmd);
			AfxMessageBox(msg);
		}

		// Wait for the process to finish
		WaitForSingleObject( pinfo.hProcess, INFINITE );
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
void CDlgReporting::OnSave() 
{
	CString reportDir = COptions::getReportDir();
	if (reportDir.IsEmpty())
	{
		AfxMessageBox("Warning, Report directory is not specified! Please check the Options dialog.");
		return;
	}

	UpdateData(TRUE);

	// Get selected period
	COleDateTime from,to;
	if ( ! GetSelectedPeriod(from, to) )
		return;

	// Get selected activities
	CDWordArray selectedActivityIDs;
	if ( ! GetSelectedActivities(selectedActivityIDs) )
		return;

	// Get selected template file
	CString templateFile;
	if ( ! GetSelectedTemplate(templateFile) )
		return;

	// Build filename proposition
	CString filename;
	filename.Format("%s\\report_%02i%02i%02i-%02i%02i%02i.xml", reportDir,
						from.GetYear()-2000, from.GetMonth(), from.GetDay(),
						to.GetYear()-2000, to.GetMonth(), to.GetDay());

	CFileDialog dlg(FALSE, "xml", filename, OFN_EXPLORER|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
						"Report Files (*.xml)|*.xml||", this);
	if (dlg.DoModal() != IDOK)
		return;

	
	CReporting report;
	report.setXmlFilename(dlg.GetFileName());
	report.setXslFilename(templateFile);
	report.setFilter(from, to);
	report.setActivities(selectedActivityIDs);
	report.setUseActualDayDuration(false);

	if (!BuildReport(report))
		return;

	CString s;
	s.Format("Report created.\n\nFilename: %s", report.GetXmlFilename());
	AfxMessageBox(s);
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CDlgReporting::GetSelectedPeriod( COleDateTime& from, COleDateTime& to ) 
{
	if (m_nFilter == 0)
	{
		int month = m_MonthNames.GetCurSel();
		if (month == -1)
			month = 0;

		from = COleDateTime(m_nMonthYear, month+1, 1, 0,0,0);
		to = MaxMonthDate(month+1, m_nMonthYear);
	}
	else if (m_nFilter == 1)
	{
		from = m_PeriodFrom;
		to = m_PeriodTo;
	}

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CDlgReporting::GetSelectedActivities( CDWordArray& selectedActivityIDs ) 
{
	// Gather selected projects
	//
	int nSelItems = m_Activities.GetSelCount();
	if (nSelItems == 0)
	{
		AfxMessageBox("Please select at least one activity!");
		return false;
	}

	int *pSelectedItems = new int[nSelItems];
	m_Activities.GetSelItems( nSelItems, pSelectedItems );

	for(int i=0; i<nSelItems; i++)
	{
		long id = GetListBoxItemID(m_Activities, pSelectedItems[i], m_itemDatas);

		if ( IsListBoxActivity(m_Activities, pSelectedItems[i], m_itemDatas) )
			selectedActivityIDs.Add(id);
		else if ( IsListBoxProject(m_Activities, pSelectedItems[i], m_itemDatas) )
		{
			CDWordArray activities;
			CRecActivity::FindActivityIDs(id, activities, true);
			selectedActivityIDs.Append(activities);
		}
	}

	delete [] pSelectedItems;

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CDlgReporting::GetSelectedTemplate( CString& filename ) 
{
	int index = m_Templates.GetCurSel();
	if (index == -1)
	{
		AfxMessageBox("Please select a template!");
		return false;
	}


	CString s;
	m_Templates.GetLBText(index, s);

	filename.Format("%s\\%s", COptions::getReportTemplateDir(), s);
	return true;
}

void CDlgReporting::OnManage() 
{
	AfxGetMainWnd()->PostMessage(WM_DLG_MANAGE);
	EndDialog(IDOK);
}
