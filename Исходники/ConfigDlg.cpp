void ConfigDlg::LoadSymbols()
{
    g_StackDepth = GetDlgItemInt( IDC_EDIT1, NULL, FALSE );
    if( m_bChanged )
    {
        CString csExeName;
        GetModuleFileName( 0, csExeName.GetBuffer( MAX_PATH), MAX_PATH );
        csExeName.ReleaseBuffer();
        csExeName = csExeName.MakeLower();
        csExeName.Replace( _T(".exe"), _T("Mem.ini"));
        CStdioFile File;
        if( !File.Open( csExeName, CFile::modeCreate|CFile::modeWrite ))
        {
            goto LoadDll;
        }        
        int nCount = m_List.GetItemCount();
        m_csPath.Empty();
        for( int nId = 0;nId < nCount; nId++ )
        {
            CString csItem = m_List.GetItemText( nId ,0 );
            m_csPath += csItem + _T(";");            
            csItem += _T("\r\n");
            File.WriteString( csItem );
        }
        File.Close();
    }
    
LoadDll:

    HMODULE hModule = GetModuleHandle( _T("dbghelp.dll"));
    SymRefreshModuleListDef pSymRefreshModuleList;
    
    if( hModule )
    {
        pSymRefreshModuleList = (SymRefreshModuleListDef)GetProcAddress( hModule, _T("SymRefreshModuleList"));
        CString csLoadedDll;
        GetModuleFileName( hModule, csLoadedDll.GetBuffer(MAX_PATH), MAX_PATH );
        csLoadedDll.ReleaseBuffer();
        if( !pSymRefreshModuleList )
        {
            // old version of dbghelp :(
            MessageBox( "Your application has already loaded dbghelp.dll from " + csLoadedDll +
                "\n\nFor acqurate results, replace this dll with the latest version of dbghelp.dll"
                "coming with \"Debugging tools for windows\" or with the dll the application folder of this utility", 
                    "Error", MB_OK );
        }
        else
        {
            MessageBox( "Your application has already loaded dbghelp.dll from " + csLoadedDll +
                " Please confirm that the symsrv.dll exists in th same folder.\n"
                "Otherwise symbol server will not work", 
                "Warning", MB_OK );
        }
        
    }
    else 
    {
// 			static int nTempvariable;
// 			MEMORY_BASIC_INFORMATION MemInfo;
// 			CString csDllPath;
// 			if( !VirtualQuery( &nTempvariable, &MemInfo, sizeof(MemInfo)))
// 			{
// 				goto LoadDll;
// 			}
        CString csDllPath;
        HMODULE hHookDll = GetModuleHandle( _T("HookDll.dll"));
        if( !GetModuleFileName( hHookDll, csDllPath.GetBuffer( MAX_PATH), MAX_PATH ))
        {
            goto LoadDll;
        }
        csDllPath.ReleaseBuffer();
        int nPos = csDllPath.ReverseFind( _T('\\'));
        if( 0 >= nPos )
        {
            goto LoadDll;
        }
        csDllPath = csDllPath.Left( nPos + 1 );
        //csDllPath = "C:\\Program Files\\Debugging Tools for Windows (x86)\\";
        csDllPath += _T("dbghelp.dll");
        
        hModule = LoadLibrary( csDllPath );
        if( !hModule)
        {
            hModule = LoadLibrary(  _T("dbghelp.dll"));
            pSymRefreshModuleList = (SymRefreshModuleListDef)GetProcAddress( hModule, _T("SymRefreshModuleList"));
            if( !pSymRefreshModuleList )
            {
                MessageBox( "Failed to load the dbghelp.dll from the local directory\n\n"
                            "The application will continue with the default dbghelp.dll. But some feature may"
                            "be unavailable", "Error", MB_OK );
            }
            
        }
        else
        {
             pSymRefreshModuleList = (SymRefreshModuleListDef)GetProcAddress( hModule, _T("SymRefreshModuleList"));
        }
        
    }

    SymCleanup(GetCurrentProcess());
    CString csWholePath = m_csPath;
    csWholePath.TrimRight( ';' );
    DWORD dwOption = 0;//SymGetOptions();
    dwOption |= SYMOPT_CASE_INSENSITIVE|SYMOPT_LOAD_LINES|SYMOPT_FAIL_CRITICAL_ERRORS|
                SYMOPT_LOAD_ANYTHING|SYMOPT_UNDNAME;    
    SymSetOptions( dwOption );
    CWinThread* pThread = AfxBeginThread( ThreadEntry, this );
    HANDLE hThread = pThread->m_hThread;
    
    
    BOOL fInvadeProcess = (0 == pSymRefreshModuleList)?TRUE:FALSE;

    
    BOOL bRet = SymInitialize(GetCurrentProcess(), (LPTSTR)csWholePath.operator LPCTSTR() , fInvadeProcess );
    SymRegisterCallback64( GetCurrentProcess(),SymRegisterCallbackProc64,(ULONG64 )this );
    while( !m_ProgressDlg.m_hWnd )// wait untill the dialog is created
    {
        Sleep( 50 );
    }

    if( pSymRefreshModuleList )
    {
        pSymRefreshModuleList( GetCurrentProcess());
    }
    //SymRefreshModuleList( GetCurrentProcess());
    m_ProgressDlg.SendMessage( WM_CLOSE );
    WaitForSingleObject( hThread, 10000 );
}