int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

    // Get command line params
    LPCWSTR szCommandLine = GetCommandLineW();  
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(szCommandLine, &argc);

    CMainDlg dlgMain;

    if(argc==2 && wcscmp(argv[1], L"/restart")==0)
        dlgMain.m_bRestarted = TRUE;
    else
        dlgMain.m_bRestarted = FALSE;

    if(dlgMain.Create(NULL) == NULL)
    {
        ATLTRACE(_T("Main dialog creation failed!\n"));
        return 0;
    }

    dlgMain.ShowWindow(nCmdShow);

    int nRet = theLoop.Run();

    _Module.RemoveMessageLoop();
    return nRet;
}