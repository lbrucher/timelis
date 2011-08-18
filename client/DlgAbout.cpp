// $Id: DlgAbout.cpp,v 1.1 2005/01/13 17:50:08 lbrucher Exp $
//
#include "stdafx.h"
#include "resource.h"
#include "DlgAbout.h"
#include "VersionInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// ////////////////////////////////////////////////////////////////////////////
//
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_sCopyright = _T("");
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


// ////////////////////////////////////////////////////////////////////////////
//
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_COPYRIGHT, m_sCopyright);
	DDX_Text(pDX, IDC_NAME, m_sName);
	//}}AFX_DATA_MAP
}


// ////////////////////////////////////////////////////////////////////////////
//
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CVersionInfo ver(AfxGetInstanceHandle());

	m_sName.Format("%s version %s", ver.GetProductName(), ver.GetDottedFileVersion());
	m_sCopyright = ver.GetCopyright();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

