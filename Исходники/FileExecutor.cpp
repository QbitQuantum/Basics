BOOL CFileExecutor::DisplayURL(LPCTSTR pszURL)
{
	ShellExecute( AfxGetMainWnd()->GetSafeHwnd(), _T("open"), pszURL, NULL, NULL, SW_SHOWNORMAL );
	return TRUE;

#if 0
	DWORD dwFilterFlags = 0;
	BOOL bSuccess = FALSE;
	DWORD hInstance = 0;

	UINT uiResult = DdeInitialize( &hInstance, DDECallback, dwFilterFlags, 0 );
	if ( uiResult != DMLERR_NO_ERROR ) return FALSE;

	HSZ hszService	= DdeCreateStringHandle( hInstance, L"IExplore", CP_WINUNICODE );
	HSZ hszTopic	= DdeCreateStringHandle( hInstance, L"WWW_OpenURL", CP_WINUNICODE );

	if ( HCONV hConv = DdeConnect( hInstance, hszService, hszTopic, NULL ) )
	{
		CString strCommand;
		USES_CONVERSION;

		strCommand.Format( _T("\"%s\",,0"), pszURL );
		LPCSTR pszCommand = T2CA( (LPCTSTR)strCommand );

		DdeClientTransaction( (LPBYTE)pszCommand, pszCommand,
			 hConv, 0, 0, XTYP_EXECUTE, 4000, NULL );

		DdeDisconnect( hConv );
	}

	DdeFreeStringHandle( hInstance, hszTopic );
	DdeFreeStringHandle( hInstance, hszService );

	DdeUninitialize( hInstance );

	return bSuccess;
#endif
}