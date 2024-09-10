bool CApp::InitInstance(int nCmdShow) 
{
    DbgLog((LOG_TRACE, 5, TEXT("CApp::InitInstance()"))) ;

    // Win32 will always set hPrevInstance to NULL, so check
    // things a little closer.  This is because we only want a single
    // version of this app to run at a time.
    m_hWnd = FindWindow(m_szAppName, m_szAppTitle) ;
    if(m_hWnd) {
        // We found another instance of ourself. Lets use that one:
        if(IsIconic(m_hWnd)) {
            ShowWindow(m_hWnd, SW_RESTORE);
        }
        SetForegroundWindow(m_hWnd);

        // If this app actually had any methodality, we would
        // also want to communicate any action that our 'twin'
        // should now perform based on how the user tried to
        // execute us.
        return false;
    }

    // Register the app main window class
    WNDCLASSEX  wc ;
    wc.cbSize        = sizeof(wc) ;
    wc.style         = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc   = (WNDPROC) WndProc ;
    wc.cbClsExtra    = 0 ;
    wc.cbWndExtra    = 0 ;
    wc.hInstance     = m_hInstance ;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW) ;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;
    wc.lpszMenuName  = TEXT("DvdSample_Menu");
    wc.lpszClassName = m_szAppName ;
    wc.hIconSm       = NULL ;

    if(0 == RegisterClassEx(&wc)) {
        DbgLog((LOG_ERROR, 0, 
            TEXT("ERROR: RegisterClassEx() for app class failed (Error %ld)"), 
            GetLastError())) ;
        return false ;
    }

    // Determine where to put the Application Window
    RECT rDesktop;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &rDesktop, NULL);

    // Create an instance of the window we just registered
    // locate it at the bottom of the screen (bottom of screen - height of player)
    m_hWnd = CreateWindowEx(0, m_szAppName, m_szAppTitle, WS_OVERLAPPEDWINDOW, //& ~WS_THICKFRAME,
        160, rDesktop.bottom - 150, 300, 150, 
        NULL, NULL, m_hInstance, NULL);
    if(!m_hWnd) {
        DbgLog((LOG_ERROR, 0, 
            TEXT("ERROR: CreateWindowEx() failed (Error %ld)"), 
            GetLastError())) ;
        return false ;
    }

    // We now create the toolbar
    INITCOMMONCONTROLSEX cc;
    cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    cc.dwICC = ICC_BAR_CLASSES; // register only the toolbar control
    InitCommonControlsEx(&cc);

#ifdef _WIN64
    // BYTE      bReserved[6]     // padding for alignment
#define PAD 0,0,0,0,0,0,  0,0,
#elif defined(_WIN32)
    // BYTE      bReserved[2]     // padding for alignment
#define PAD 0,0,  0,0,
#endif

        // Configure toolbar buttons    
        TBBUTTON tbb[] = 
    {
        0, ID_PLAYBACK_PREVIOUSCHAPTER, TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        1, ID_PLAYBACK_REWIND,          TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        2, ID_PLAYBACK_PAUSE,           TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        3, ID_PLAYBACK_PLAY,            TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        4, ID_PLAYBACK_STOP,            TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        5, ID_PLAYBACK_FASTFORWARD,     TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        6, ID_PLAYBACK_NEXTCHAPTER,     TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        9, 0,                           TBSTATE_ENABLED, TBSTYLE_SEP,    PAD
        7, ID_PLAYBACK_MENUROOT,        TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        8, ID_OPTIONS_FULLSCREEN,       TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
        9, ID_PLAYBACK_STEPFORWARD,     TBSTATE_ENABLED, TBSTYLE_BUTTON, PAD
    };

    m_hwndToolBar = CreateToolbarEx(m_hWnd, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_TOP
        | TBSTYLE_TOOLTIPS, 1, 10, m_hInstance, IDR_TOOLBAR1, tbb, 11, 0, 0, 0, 0,
        sizeof(TBBUTTON));
    if(!m_hwndToolBar) {
        DbgLog((LOG_ERROR, 0, 
            TEXT("ERROR: CreateToolbarEx() failed (Error %ld)"), 
            GetLastError())) ;
        return false ;
    }

    // we now set up the dvd playback class
    m_pDvdCore = new CDvdCore(m_hInstance, this);
    if(!m_pDvdCore->Init()) {
        DbgLog((LOG_ERROR, 0, TEXT("ERROR: CDvdCore::Init() failed"))) ;
        return false;
    }

    m_pDvdCore->SetVideoWindowTitle(TEXT("DvdSample Video Window"));

    // and finally, we make the window visible
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd) ;

    return true;
}