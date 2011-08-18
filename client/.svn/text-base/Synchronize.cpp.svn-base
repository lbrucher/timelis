// $Id: Synchronize.cpp,v 1.2 2005/02/03 23:31:04 lbrucher Exp $
//
#include "stdafx.h"
#include "Synchronize.h"
#include "Timelis.h"
#include "Options.h"
#include "RecProject.h"
#include "RecTask.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
#import <msxml4.dll>
using namespace MSXML2;

#import "C:\Program Files\Common Files\MSSoap\Binaries\mssoap30.dll" named_guids \
  exclude("IStream", "IErrorInfo", "ISequentialStream", "_LARGE_INTEGER", \
  "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")

using namespace MSSOAPLib30;
*/

extern CTimelisApp theApp;
extern CDaoDatabase* g_pTimeSheetDB;


#define CHECK_HR(method,msg)	\
	{ HRESULT hr = method;	\
	  if (FAILED(hr))	\
	  { CString s; s.Format("ERROR with %s\nhr = 0x%X", msg, (int)hr); AfxMessageBox(s); return hr; }	\
	}



// ////////////////////////////////////////////////////////////////////////////
//
CSynchronize::CSynchronize() :
	m_bPlayWhatIf(false)
{
}



// ////////////////////////////////////////////////////////////////////////////
//
void CSynchronize::setPlayWhatIf( bool isPlayWhatIf )
{
	m_bPlayWhatIf = isPlayWhatIf;
}

/*
// ////////////////////////////////////////////////////////////////////////////
//
static bool loadXmlDocument( CComPtr<MSXML2::IXMLDOMDocument2>& xmlDoc, const char* pXmlSource )
{
	HRESULT hr;

	if ( FAILED(hr = xmlDoc.CoCreateInstance(_bstr_t("msxml2.domdocument"))) )
		TS_ERROR( FormatString("loadXmlDocument: CCI(msxml) failed: 0x%X",hr), false );


	CComVariant vOut = xmlDoc->loadXML(_bstr_t(pXmlSource));
	if ( !vOut.boolVal )
		TS_ERROR( "loadXmlDocument: error loading XML document!", false );

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
static HRESULT initSOAP( const CString& serviceURL, CComPtr<ISoapClient>& soapClient,
						 const char* pMethodName, DISPID& dispid )
{
	try
	{
		_bstr_t		bstrWsdlFilename(serviceURL);
		CComBSTR	wFuncName(pMethodName);

		CHECK_HR( soapClient.CoCreateInstance(__uuidof(SoapClient30)), "soapClient.CCI" );
		CHECK_HR( soapClient->MSSoapInit(bstrWsdlFilename, "", "", ""), "soapClient->MSSoapInit" );
		CHECK_HR( soapClient->GetIDsOfNames(IID_NULL, &wFuncName, 1, LOCALE_SYSTEM_DEFAULT, &dispid), "soapClient->GetIDsOfNames" );

		return S_OK;
	}
	catch ( _com_error error )
	{
		AfxMessageBox( FormatString("An exception occured: %s.\n\nDetailed message:\n%s", error.ErrorMessage(), (char*)error.Description()), MB_ICONSTOP );
		return E_FAIL;
	}
}


// ////////////////////////////////////////////////////////////////////////////
//
static bool initSoapMethod( const CString& sMethod, CComPtr<ISoapClient>& soapClient, DISPID& dispid )
{
	// Get the WSDL URL
	//
	CString serviceUrl( COptions::getSyncWsdlUrl() );
	if (serviceUrl.IsEmpty())
	{
		AfxMessageBox("Please setup the server service URL!");
		return false;
	}


	// Init SOAP
	//
	dispid = -1;

	if ( FAILED( initSOAP(serviceUrl, soapClient, sMethod, dispid) ) )
		return false;

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CSynchronize::retrieveProjects( COleDateTime* pDate, CStringArray* pReport )
{
	// Convert given date into a string
	//
	CString sDate("");
	if (pDate != NULL)
		sDate.Format("%04i%02i%02i", pDate->GetYear(), pDate->GetMonth(), pDate->GetDay());



	// Init SOAP
	//
	CComPtr<ISoapClient>	soapClient;
	DISPID					dispid = -1;
	if ( ! initSoapMethod("retrieveModifiedProjects", soapClient, dispid) )
		return false;



	// Invoke method
	//
	DISPPARAMS		dispparams;
	EXCEPINFO		excepinfo;
	CComVariant		retval;
	unsigned int	uArgErr = 0;
	CComBSTR		bstrDate(sDate);

	dispparams.rgvarg				= new VARIANTARG[1];
	dispparams.cArgs				= 1;
	dispparams.cNamedArgs			= 0;
	dispparams.rgdispidNamedArgs	= NULL;
	dispparams.rgvarg[0].vt			= VT_BYREF|VT_BSTR;
	dispparams.rgvarg[0].pbstrVal	= &bstrDate;

	excepinfo.wCode				= 0;
	excepinfo.bstrSource		= NULL;
	excepinfo.bstrDescription	= NULL;
	excepinfo.bstrHelpFile		= NULL;

	HRESULT hr = soapClient->Invoke( dispid, IID_NULL, LOCALE_USER_DEFAULT,
									 DISPATCH_METHOD,
									 &dispparams, &retval, &excepinfo, &uArgErr );

	delete [] dispparams.rgvarg;

	if ( FAILED(hr) )
	{
		AfxMessageBox( FormatString("Error calling SOAP method: hr = 0x%X", hr) );
		return false;
	}

	if (retval.vt != VT_BSTR)
	{
		AfxMessageBox( FormatString("SOAP method did not return a string. Type of data returned: %i", retval.vt) );
		return false;
	}

	return updateProjectsAfterRetrieve( (char*)_bstr_t(retval.bstrVal), pReport );
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CSynchronize::sendProjects( CStringArray* pReport )
{
	// Retrieve the list of projects and activities that have been locally modified
	//
	CString sBuffer("");
	TProjectInfoSimpleArray projects;
	TActivityInfoArray activities;

	CRecProject::FindLocallyModifiedProjects(projects);
	CRecActivity::FindLocallyModifiedActivities(activities);

	if (m_bPlayWhatIf)
	{
		if (pReport != NULL)
		{
			CString s;
			for(int ip=0; ip<projects.GetSize(); ip++)
			{
				CProjectInfoSimple& info = projects[ip];
				s.Format("Updated project <%s>", info.name);
				pReport->Add(s);
			}

			for(int ia=0; ia<activities.GetSize(); ia++)
			{
				CActivityInfo& info = activities[ia];
				s.Format("Updated activity <%s> (project <%s>)", info.name, CRecProject::GetProjectName(info.projectID));
				pReport->Add(s);
			}
		}
		return true;
	}


	sBuffer = "<?xml version='1.0'?>\n";
	sBuffer += "<modifications>\n";

	// Projects
	sBuffer += "  <projects>\n";
	for(int ip=0; ip<projects.GetSize(); ip++)
	{
		CProjectInfoSimple& info = projects[ip];

		sBuffer += "    <project>\n";
		sBuffer += "      <name><![CDATA[";
		sBuffer +=          info.name;
		sBuffer +=        "]]></name>\n";
		sBuffer += "    </project>\n";
	}
	sBuffer += "  </projects>\n";

	// Activities
	sBuffer += "  <activities>\n";
	for(int ia=0; ia<activities.GetSize(); ia++)
	{
		CActivityInfo& info = activities[ia];

		sBuffer += "    <activity>\n";
		sBuffer += "      <name><![CDATA[";
		sBuffer +=          info.name;
		sBuffer +=        "]]></name>\n";
		sBuffer += "      <projectName><![CDATA[";
		sBuffer +=          CRecProject::GetProjectName(info.projectID);
		sBuffer +=        "]]></projectName>\n";
		sBuffer += "    </activity>\n";
	}
	sBuffer += "  </activities>\n";
	sBuffer += "</modifications>\n";

return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CSynchronize::sendTimesheetData()
{
	return true;
}

 
// ////////////////////////////////////////////////////////////////////////////
//
// Process.
// For each project from the server:
// - if its masterID can be found locally, the local project name is updated with the server's
// - otherwise, if there is already a project with that name, set the masterID with the server's
// - otherwsie, add the new project locally 
//
bool CSynchronize::updateProjectsAfterRetrieve( const char* pXmlSource, CStringArray* pReport )
{
#ifdef _DEBUG
	String2File(pXmlSource, "C:\\ts-retrieve.xml");
#endif

	if (pReport != NULL)
		pReport->RemoveAll();


//Sleep(1000);
//return S_OK;

//AfxMessageBox(pXmlSource);
//return S_OK;



	// Load XML document
	CComPtr<MSXML2::IXMLDOMDocument2> xmlDoc;
	if (!loadXmlDocument(xmlDoc, pXmlSource))
		return false;


	// List all projects
	CComPtr<MSXML2::IXMLDOMNodeList> projects = xmlDoc->selectNodes( "/projects/*" );
	for( int i=0; i<projects->Getlength(); i++ )
	{
		CComPtr<MSXML2::IXMLDOMNode> project = projects->Getitem(i);

		CComPtr<MSXML2::IXMLDOMNode>     name		= project->selectSingleNode("name");
		CComPtr<MSXML2::IXMLDOMNode>     id			= project->selectSingleNode("id");
		CComPtr<MSXML2::IXMLDOMNodeList> activities	= project->selectNodes( "activities/*" );

		//
		// Note: no activities means to delete the project
		//

		if (name == NULL)
			TS_ERROR( FormatString("Missing 'name' node in project #%i",i), false )
		else if (id == NULL)
			TS_ERROR( FormatString("Missing 'id' node in project #%i",i), false )
		else
		{
			CString projectName((char*)name->Gettext());
			long    masterPID = atol( (char*)id->Gettext() );
			long    projectID = -1;

			TRACE3("project %i: name=[%s], id=[%li]\n", i, projectName, masterPID);


			CRecProject recProject;

			// See if we already have a project with such MasterID
			if ( recProject.FindByMasterID( masterPID ) )
			{
				projectID = recProject.m_ID;

				// Case sensitive compare
				if ( projectName.Compare(recProject.m_Name) != 0 )
				{
					// Update project name
					log("updateProjects: updating project name from [%s] to [%s] for masterID=%li", recProject.m_Name, projectName, masterPID);

					if (pReport != NULL)
						pReport->Add( FormatString("Updated name of project <%s> (was <%s>)", projectName, recProject.m_Name) );

					if (!m_bPlayWhatIf)
					{
						recProject.Edit();
						recProject.m_Name = projectName;
						recProject.Update();
					}
				}
			}

			// See if there is another project with the same name
			else if ( recProject.FindByName(projectName) )
			{
				projectID = recProject.m_ID;

				if ( recProject.m_MasterID != masterPID )
				{
					// Update project masterID
					log("updateProjects: updating project masterID from [%li] to [%li] for name=[%s]", recProject.m_MasterID, masterPID, projectName);

					if (pReport != NULL)
						pReport->Add( FormatString("Updated project <%s> (masterID was <%li>, now is <%li>)", projectName, recProject.m_MasterID, masterPID) );

					if (!m_bPlayWhatIf)
					{
						recProject.Edit();
						recProject.m_MasterID = masterPID;
						recProject.Update();
					}
				}
			}

			else
			{
				// Add new project
				log("updateProjects: adding new project with name=[%s], masterID=[%li]", projectName, masterPID);

				if (!m_bPlayWhatIf)
				{
					recProject.AddNew();
					recProject.m_Name     = projectName;
					recProject.m_MasterID = masterPID;
					recProject.Update();

					recProject.SetBookmark(recProject.GetLastModifiedBookmark());
					projectID = recProject.m_ID;
				}

				if (pReport != NULL)
					pReport->Add( FormatString("Adding project <%s> (masterID <%li>)", projectName, masterPID) );
			}

			if ((projectID == -1) && (!m_bPlayWhatIf))
				TS_ERROR("updateProjects: projectID == -1!", false);


			// Get the project's activities
			TActivityInfoArray projectActivities;

			if ((projectID != -1) && (!m_bPlayWhatIf))
				CRecActivity::FindActivityInfos(projectID, projectActivities, false);


			// Go over all activities from the XML file and for each one:
			// - add it if it does not exist yet
			// - update it if it does exist already
			// The existing ones that do not exist in the XML source are either:
			// - deleted if not used anymore and their masterID not null
			// - their masterID reset if they are still used
			//
			for( int k=0; k<activities->Getlength(); k++ )
			{
				CComPtr<MSXML2::IXMLDOMNode> activity = activities->Getitem(k);
				CComPtr<MSXML2::IXMLDOMNode> name     = activity->selectSingleNode("name");
				CComPtr<MSXML2::IXMLDOMNode> masterID = activity->selectSingleNode("id");

				CString activityName( (char*)name->Gettext() );
				long nMasterID = atol( (char*)masterID->Gettext() );


				// Find the corresponding activity in our local list
				bool bFound = false;
				for( int a=0; a<projectActivities.GetSize(); a++ )
				{
					CActivityInfo& info = projectActivities[a];

					// Same activity name?
					if ( activityName.Compare(info.name) == 0 )
					{
						CRecActivity recActivity;
						if ( recActivity.FindByID(info.id) )
						{
							bFound = true;

							// Update the local masterID if they are different
							if ( recActivity.m_MasterID != nMasterID )
							{
								if (pReport != NULL)
									pReport->Add( FormatString("Updated activity <%s> for project <%s> (masterID changed from <%li> to <%li>)", activityName, projectName, recActivity.m_MasterID, nMasterID) );

								if (!m_bPlayWhatIf)
								{
									recActivity.Edit();
									recActivity.m_MasterID = nMasterID;
									recActivity.m_LocallyModified = FALSE;
									recActivity.Update();
								}
							}
							else
							{
								// Reset the locally modified flag
								if (!m_bPlayWhatIf)
								{
									recActivity.Edit();
									recActivity.m_LocallyModified = FALSE;
									recActivity.Update();
								}
							}
						}

						projectActivities.RemoveAt(a);
						break;
					}

					else if ( info.masterID == nMasterID )
					{
						CRecActivity recActivity;
						if ( recActivity.FindByID(info.id) )
						{
							bFound = true;

							if ( activityName.Compare(recActivity.m_Name) != 0 )
							{
								// Woops, dont overwrite any local changes that may have been made
								if (recActivity.m_LocallyModified)
								{
									if (pReport != NULL)
										pReport->Add( FormatString("Warning! Try to update activity name <%s> (project <%s>) that was locally modified (new activity name is <%s>)!", recActivity.m_Name, projectName, activityName) );
								}
								else
								{
									if (pReport != NULL)
										pReport->Add( FormatString("Updated activity <%s> for project <%s> (name was <%s>)", activityName, projectName, recActivity.m_Name) );

									if (!m_bPlayWhatIf)
									{
										recActivity.Edit();
										recActivity.m_Name = activityName;
										recActivity.Update();
									}
								}
							}
						}

						projectActivities.RemoveAt(a);
						break;
					}
				}

				// Not in our local list -> add it then
				if (!bFound)
				{
					if (!m_bPlayWhatIf)
					{
						CRecActivity recActivity;
						recActivity.AddNew();
						recActivity.m_MasterID			= nMasterID;
						recActivity.m_Name				= activityName;
						recActivity.m_Enabled			= TRUE;
						recActivity.m_LocallyModified	= FALSE;
						recActivity.m_ProjectID			= projectID;
						recActivity.Update();
					}

					if (pReport != NULL)
						pReport->Add( FormatString("Adding activity <%s> to project <%s>", activityName, projectName) );
				}
			}

			// Whatever is still in the projectActivities array is considered
			// as removed on the server and so should be removed from our local DB as well
			// (but only if it is not used anymore!)
			//
			for( int a=0; a<projectActivities.GetSize(); a++ )
			{
				CActivityInfo& info = projectActivities[a];

				CRecActivity recActivity;
				if ( recActivity.FindByID(info.id) )
				{
					// See if the activity has been locally modified
					if (recActivity.m_LocallyModified)
					{
//						if (pReport != NULL)
//							pReport->Add( FormatString("Activity <%s> of project <%s> was modified locally", recActivity.m_Name, projectName) );
						;
					}
					
					// See if the activity is still in use
					else if (CRecTask::HasLinkToActivity(recActivity.m_ID))
					{
						if (pReport != NULL)
							pReport->Add( FormatString("Activity <%s> of project <%s> to be deleted but still in use", recActivity.m_Name, projectName) );

						if (!m_bPlayWhatIf)
						{
							recActivity.Edit();
							recActivity.m_MasterID = 0;
							recActivity.Update();
						}
					}

					// Otherwise, delete the activity
					else
					{
						if (pReport != NULL)
							pReport->Add( FormatString("Deleted activity <%s> of project <%s>", info.name, projectName) );

						// Not used -> delete it
						if (!m_bPlayWhatIf)
							CRecActivity::DeleteActivity(info.id);
					}
				}
			}

		}
	}

	return true;
}


// ////////////////////////////////////////////////////////////////////////////
//
bool CSynchronize::updateProjectsAfterSend( const char* pXmlResult, CStringArray* pReport )
{
#ifdef _DEBUG
	String2File(pXmlResult, "C:\\ts-sendresult.xml");
#endif

	if (pReport != NULL)
		pReport->RemoveAll();


AfxMessageBox(pXmlResult);
return true;



	// Load XML document
	CComPtr<MSXML2::IXMLDOMDocument2> xmlDoc;
	if (!loadXmlDocument(xmlDoc, pXmlResult))
		return false;







	return true;
}

*/


// ////////////////////////////////////////////////////////////////////////////
//
bool CSynchronize::retrieveProjects( COleDateTime* pDate, CStringArray* pReport )
{
	return true;
}
