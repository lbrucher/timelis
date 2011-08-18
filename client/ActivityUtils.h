// $Id: ActivityUtils.h,v 1.2 2005/01/11 14:42:24 lbrucher Exp $
//
#ifndef __ACTIVITYUTILS_H__
#define __ACTIVITYUTILS_H__

#include "RecProject.h"


void FillActivityList( CListBox& lb, const TProjectInfoArray& projects );
void FillActivityList( CComboBox& cb, const TProjectInfoArray& projects );

void FillAllProjectsList( CListBox& lb, CStringArray& itemDatas );
void FillEnabledProjectsList( CListBox& lb, CStringArray& itemDatas );

bool IsListBoxActivity( const CListBox& lb, int index, const CStringArray& itemDatas );
bool IsListBoxProject( const CListBox& lb, int index, const CStringArray& itemDatas );

long GetListBoxItemID( const CListBox& lb, int index, const CStringArray& itemDatas );


#endif
