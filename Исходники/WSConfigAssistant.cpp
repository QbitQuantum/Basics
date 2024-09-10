BOOL CWSConfigAssistantApp::InitInstance()
{
    CLimitSingleInstance lsi(SINGLE_INSTANCE_MUTEX_NAME);
    if ( lsi.IsAnotherInstanceRunning() )
    {
        MessageBox(NULL, _T("An instance of Workshare Configuration Assistant is already running. Please close that to run another instance."), _T("Workshare"), MB_OK | MB_ICONWARNING);
        return FALSE;
    }

    if( m_pInstallAgent )
    {
        m_pInstallAgent->Initialize();

        // workaround for imanage f*****g up our current path
        // stores path internally.
        m_pInstallAgent->GetInstallDir();
    }

    // Ensure Windows Message box displayed when can not load Workshare Message component has correct title
    free((void*)m_pszAppName);
    m_pszAppName =_tcsdup(_T("Workshare Configuration Assistant"));

    CStdString sCmdLine(GetCommandLine());
    sCmdLine.MakeLower();

    bool bRunTests(sCmdLine.Find(_T("runtests")) != -1);
    bool bAutoRunTests(sCmdLine.Find(_T("autoruntests")) != -1);
    bool bRunFunctionalTests(sCmdLine.Find(_T("functionaltests")) != -1);

    if(bRunTests)
    {
        m_iRetCode = RunAppTestsEx(bAutoRunTests, bRunFunctionalTests, false, _T(""), false);
        CoFreeUnusedLibraries();
        return FALSE;
    }

    if( m_pInstallAgent && !m_pInstallAgent->WasCommandLineValid())
    {
        AfxMessageBox(m_pInstallAgent->GetCommandLineHelp(),MB_OK);
        return FALSE;
    }

    if(m_pInstallAgent && m_pInstallAgent->IsQuiet())
    {
        if(GetInstallAgent())
            GetInstallAgent()->LogEvent(_T("CWSConfigAssistantApp::OnInitDialog - Quiet Silent version of the application."));

        SafeDeleteSingleItem(m_pInstallAgent);
        m_pInstallAgent = NULL;

        CQuietProgressDlg dlg;
        dlg.DoModal();
        m_iRetCode = dlg.GetResult();
    }
    else if (!IsSilent())
    {
        if(GetInstallAgent())
            GetInstallAgent()->LogEvent(_T("CWSConfigAssistantApp::OnInitDialog - Running UI version of the application."));

        CWSConfigAssistantDlg dlg(_T("Workshare"));
        dlg.SetWizardMode();
        m_pMainWnd = &dlg;

        if( ::IsWindow(dlg.m_hWnd) )
            dlg.SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

        INT_PTR ret = dlg.DoModal();
        if (ret == IDCANCEL)
        {
            m_iRetCode = 1602;
        }
    }
    else
    {
        if(GetInstallAgent())
            GetInstallAgent()->LogEvent(_T("CWSConfigAssistantApp::OnInitDialog - Running Silent version of the application."));

        SafeDeleteSingleItem(m_pInstallAgent);
        m_pInstallAgent = NULL;

        CStdString sResult;
        m_iRetCode = InstallAgent::Run(GetCommandLine(), sResult);
    }

    return FALSE;
}