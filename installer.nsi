!define VERSION "1.0.1"
!include "FileFunc.nsh"
!include x64.nsh

Name "EdgeKiller"

OutFile "install.exe"

InstallDir $PROGRAMFILES64\EdgeKiller
RequestExecutionLevel admin
 
Section
    
    SetOutPath $INSTDIR
    
    File build\Release\EdgeKiller.exe
    File build\Release\config.json

    # Add the IFEO Debugger key
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\msedge.exe" "Debugger" "$\"$INSTDIR\EdgeKiller.exe$\""

    WriteUninstaller $INSTDIR\uninstall.exe

    # Add Uninstaller Data
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "DisplayName" "EdgeKiller"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "DisplayVersion" "${VERSION}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "Publisher" "pochwix2"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "URLInfoAbout" "https://github.com/janek515/edgekiller"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "NoModify" 0x00000001
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "NoRepair" 0x00000001
    ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
    IntFmt $0 "0x%08X" $0
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller" "EstimatedSize" $0


SectionEnd
 

Section "Uninstall"
 
    Delete $INSTDIR\uninstall.exe
    Delete $INSTDIR\EdgeKiller.exe
    Delete $INSTDIR\config.json

    RMDir $INSTDIR

    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\EdgeKiller"

    # Remove the IFEO Debugger key
    DeleteRegValue HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\msedge.exe" "Debugger"
    DeleteRegKey /ifempty HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\msedge.exe"

SectionEnd