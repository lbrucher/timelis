// $Id: TimeSheeter.cpp,v 1.1 2005/01/11 14:42:25 lbrucher Exp $
//
#include "stdafx.h"
#include "Timelis.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DB_FILENAME		_T("timelis.mdb")

CDaoWorkspace *g_pDBWorkspace = 0;
CDaoDatabase  *g_pTimeSheetDB = 0;

CTimelisApp theApp;


BEGIN_MESSAGE_MAP(CTimelisApp, CWinApp)
	//{{AFX_MSG_MAP(CTimelisApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
BOOL InitDatabase()
{
	g_pDBWorkspace = new CDaoWorkspace();
	g_pDBWorkspace->Open(NULL);
	g_pTimeSheetDB  = new CDaoDatabase(g_pDBWorkspace);

	try
	{
		g_pTimeSheetDB->Open(DB_FILENAME);
	}
	catch(...)
	{
		AfxMessageBox("Cannot find the TimeSheet Database!\n\nPress OK to quit.");
		return FALSE;
	}

	return TRUE;
}


// ////////////////////////////////////////////////////////////////////////////
//
void CloseDatabase()
{
	if (g_pTimeSheetDB)
	{
		g_pTimeSheetDB->Close();
		delete g_pTimeSheetDB;
		g_pTimeSheetDB = 0;
	}

	if (g_pDBWorkspace)
	{
		g_pDBWorkspace->Close();
		delete g_pDBWorkspace;
		g_pDBWorkspace = 0;
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
CTimelisApp::CTimelisApp()
{
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CTimelisApp::InitInstance()
{
	// Upgrade MFC to v6.01 in order to use DAO 3.6 (not 3.5 which is the default) so that Access2000 MDBs can
	// be used correctly...
	// See article Q236991 in Microsoft KnowledgeBase.
	//
	AfxGetModuleState()->m_dwVersion = 0x0601;


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Idelis"));


	// Setup database
	if (!InitDatabase())
		return FALSE;


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);




	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_HIDE);
	pFrame->UpdateWindow();

	return TRUE;
}


// ////////////////////////////////////////////////////////////////////////////
//
int CTimelisApp::ExitInstance()
{
	CloseDatabase();

	return CWinApp::ExitInstance();
}
