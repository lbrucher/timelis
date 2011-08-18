// $Id: ActivityUtils.cpp,v 1.2 2005/01/11 14:42:25 lbrucher Exp $
//
#include "stdafx.h"
#include "ActivityUtils.h"



// ///////////////////////////////////////////////////////////////////////////
//
static void DoFillProjectsList( CListBox& lb, CStringArray& itemDatas, bool bEnabledOnly, bool bShowEmptyProjects )
{
	TProjectInfoArray projects;

	if (bEnabledOnly)
		CRecProject::FindEnabledProjects(projects);
	else
		CRecProject::FindAllProjects(projects);


	CString sItem;
	for(int i=0; i<projects.GetSize(); i++)
	{
		CProjectInfo& project = projects[i];
		if ((bShowEmptyProjects) || ((project.activities.GetSize() > 0) && (!bShowEmptyProjects)))
		{
			// Add project
			sItem.Format("P%li", project.id);
			int index = lb.AddString(project.name);
			int item  = itemDatas.Add(sItem);
			lb.SetItemData(index, DWORD(item));

			// Add activities
			CString s;
			for(int j=0; j<project.activities.GetSize(); j++)
			{
				sItem.Format("A%li", project.activities[j].id);
				s.Format("   %s", project.activities[j].name);
				index = lb.AddString(s);
				item  = itemDatas.Add(sItem);
				lb.SetItemData(index, DWORD(item));
			}
		}
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void FillActivityList( CListBox& lb, const TProjectInfoArray& projects )
{
	CString s;
	for(int i=0; i<projects.GetSize(); i++)
	{
		CProjectInfo& project = projects[i];
		if (project.activities.GetSize() > 0)
		{
			// Add activities
			for(int j=0; j<project.activities.GetSize(); j++)
			{
				s.Format("%s - %s", project.name, project.activities[j].name);
				int index = lb.AddString(s);
				lb.SetItemData(index, DWORD(project.activities[j].id));
			}
		}
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void FillActivityList( CComboBox& cb, const TProjectInfoArray& projects )
{
	CString s;
	for(int i=0; i<projects.GetSize(); i++)
	{
		CProjectInfo& project = projects[i];
		if (project.activities.GetSize() > 0)
		{
			// Add activities
			for(int j=0; j<project.activities.GetSize(); j++)
			{
				s.Format("%s - %s", project.name, project.activities[j].name);
				int index = cb.AddString(s);
				cb.SetItemData(index, DWORD(project.activities[j].id));
			}
		}
	}
}


// ///////////////////////////////////////////////////////////////////////////
//
void FillAllProjectsList( CListBox& lb, CStringArray& itemDatas )
{
	DoFillProjectsList(lb, itemDatas, false, true);
}


// ///////////////////////////////////////////////////////////////////////////
//
void FillEnabledProjectsList( CListBox& lb, CStringArray& itemDatas )
{
	DoFillProjectsList(lb, itemDatas, true, false);
}


// ///////////////////////////////////////////////////////////////////////////
//
bool IsListBoxActivity( const CListBox& lb, int index, const CStringArray& itemDatas )
{
	int itemIndex = (int) lb.GetItemData(index);
	if ( (itemIndex >= 0) && (itemIndex < itemDatas.GetSize()) )
		return itemDatas[itemIndex][0] == 'A';
	return false;
}


// ///////////////////////////////////////////////////////////////////////////
//
bool IsListBoxProject( const CListBox& lb, int index, const CStringArray& itemDatas )
{
	int itemIndex = (int) lb.GetItemData(index);
	if ( (itemIndex >= 0) && (itemIndex < itemDatas.GetSize()) )
		return itemDatas[itemIndex][0] == 'P';
	return false;
}


// ///////////////////////////////////////////////////////////////////////////
//
long GetListBoxItemID( const CListBox& lb, int index, const CStringArray& itemDatas )
{
	int itemIndex = (int) lb.GetItemData(index);
	if ( (itemIndex >= 0) && (itemIndex < itemDatas.GetSize()) )
		return atoi( itemDatas[itemIndex].Mid(1) );
	return -1;
}
