    void InitializeExportDialogs( const CHAR* strTitle, HWND hParentWindow, HINSTANCE hInst )
    {
        g_strTitle = strTitle;
        g_hInstance = hInst;
        g_hParentWindow = hParentWindow;

        // Pull in common and rich edit controls
        INITCOMMONCONTROLSEX ICEX;
        ICEX.dwSize = sizeof( INITCOMMONCONTROLSEX );
        ICEX.dwICC = ICC_WIN95_CLASSES | ICC_COOL_CLASSES | ICC_USEREX_CLASSES;
        InitCommonControlsEx( &ICEX );
        InitCommonControls();
        g_hRichEdit = LoadLibrary( TEXT( "Riched32.dll" ) );
        assert( g_hRichEdit != nullptr );

        ExportLog::AddListener( &g_ConsoleDlg );
        g_pProgress = &g_ConsoleDlg;

        const DWORD dwStackSize = 8192;

        _beginthreadex( nullptr, dwStackSize, ExportConsoleDialog::ThreadEntry, &g_ConsoleDlg, 0, nullptr );
        _beginthreadex( nullptr, dwStackSize, ExportSettingsDialog::ThreadEntry, &g_SettingsDlg, 0, nullptr );
    }