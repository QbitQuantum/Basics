BOOL CSnmptreeApp::InitInstance()
{
    if (!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();            // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();    // Call this when linking to MFC statically
#endif

    // Change the registry key under which our settings are stored.
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization.
    SetRegistryKey(_T("Mbuf"));

        // 6-Feb-05 ; load global variable settings
        int retcode = init_globals();
        ASSERT( retcode == 0 );

//    LoadStdProfileSettings(6);

    char *mibdir = netsnmp_get_mib_directory();

    /* Fire up the Net-SNMP library */
    if( snmpcore_init() != SNMPCORE_SUCCESS ) {
        // FIXME -- need better error message
        AfxMessageBox( "Net-SNMP failed to start" );
        return FALSE;
    }

    mibdir = netsnmp_get_mib_directory();

    // To create the main window, this code creates a new frame window
    // object and then sets it as the application's main window object.

    CMainFrame* pFrame = new CMainFrame;
    m_pMainWnd = pFrame;

    // create and load the frame with its resources

    pFrame->LoadFrame(IDR_MAINFRAME,
        WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
        NULL);
    
    // The one and only window has been initialized, so show and update it.
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    return TRUE;
}