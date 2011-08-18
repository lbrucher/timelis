# Microsoft Developer Studio Project File - Name="Timelis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Timelis - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Timelis.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Timelis.mak" CFG="Timelis - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Timelis - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Timelis - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Timelis - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Version.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Timelis - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Timelis - Win32 Release"
# Name "Timelis - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActivityUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DaoRecordsetEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddEditTask.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddPause.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddProject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteProject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMain.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManageProjects.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewDay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPauses.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReporting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectActivities.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShowEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStats.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSynchronize.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTasks.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWait.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\RecActivity.cpp
# End Source File
# Begin Source File

SOURCE=.\RecEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\RecPauses.cpp
# End Source File
# Begin Source File

SOURCE=.\RecProject.cpp
# End Source File
# Begin Source File

SOURCE=.\RecTask.cpp
# End Source File
# Begin Source File

SOURCE=.\RecTimeSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Reporting.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Synchronize.cpp
# End Source File
# Begin Source File

SOURCE=.\Timelis.cpp
# End Source File
# Begin Source File

SOURCE=.\Timelis.rc
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkDay.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActivityUtils.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\DaoRecordsetEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddEditTask.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddPause.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddProject.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeleteProject.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgEvents.h
# End Source File
# Begin Source File

SOURCE=.\DlgMain.h
# End Source File
# Begin Source File

SOURCE=.\DlgManage.h
# End Source File
# Begin Source File

SOURCE=.\DlgManageProjects.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewDay.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgPauses.h
# End Source File
# Begin Source File

SOURCE=.\DlgReporting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectActivities.h
# End Source File
# Begin Source File

SOURCE=.\DlgShowEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgStats.h
# End Source File
# Begin Source File

SOURCE=.\DlgSynchronize.h
# End Source File
# Begin Source File

SOURCE=.\DlgTasks.h
# End Source File
# Begin Source File

SOURCE=.\DlgWait.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\RecActivity.h
# End Source File
# Begin Source File

SOURCE=.\RecEvent.h
# End Source File
# Begin Source File

SOURCE=.\RecPauses.h
# End Source File
# Begin Source File

SOURCE=.\RecProject.h
# End Source File
# Begin Source File

SOURCE=.\RecTask.h
# End Source File
# Begin Source File

SOURCE=.\RecTimeSheet.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Reporting.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Synchronize.h
# End Source File
# Begin Source File

SOURCE=.\Timelis.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.h
# End Source File
# Begin Source File

SOURCE=.\WorkDay.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Timelis.ico
# End Source File
# Begin Source File

SOURCE=.\res\Timelis.rc2
# End Source File
# Begin Source File

SOURCE=.\res\tray.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\report.html
# End Source File
# End Target
# End Project
