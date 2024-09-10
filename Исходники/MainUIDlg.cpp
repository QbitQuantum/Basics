BOOL CMainUIDlg::IsAppRun(CString AppName)
{
    char   pPath[_MAX_PATH];
    pPath[0]=0;
    const char *cExeName = CStrToChar(AppName);
    _searchenv(cExeName, "PATH ",pPath);
    VERIFY(pPath);
    DWORD id=GetProcessIdFromName(AppName);//这样查杀AppName
    if(id!=NULL)
    {
        HANDLE   myhandle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,id);
        DWORD   exitcode=0;
        TerminateProcess(myhandle,exitcode);
        return   TRUE;
    }
    return   FALSE;
}