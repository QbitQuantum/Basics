BOOL CDocManager::OnDDECommand( LPTSTR lpszCommand )
/**************************************************/
{
    if( _tcsncmp( lpszCommand, _DDECmdStart,
                  sizeof( _DDECmdStart ) / sizeof( TCHAR ) - 1 ) != 0 ) {
        return( FALSE );
    }
    lpszCommand += sizeof( _DDECmdStart ) / sizeof( TCHAR ) - 1;

    LPTSTR lpszEnd = _tcsstr( lpszCommand, _DDECmdEnd );
    if( lpszEnd == NULL ) {
        return( FALSE );
    }
    *lpszEnd = _T('\0');

    CWinApp *pApp = AfxGetApp();
    ASSERT( pApp != NULL );
    CWnd *pMainWnd = pApp->m_pMainWnd;
    ASSERT( pMainWnd != NULL );
    if( !pMainWnd->IsWindowVisible() ) {
        pMainWnd->ShowWindow( SW_SHOW );
    }
    
    OpenDocumentFile( lpszCommand );
    
    return( TRUE );
}