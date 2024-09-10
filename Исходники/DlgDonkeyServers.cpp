void CDonkeyServersDlg::OnRun()
{
	if ( m_hInternet == NULL ) return;

	HINTERNET hRequest = InternetOpenUrl( m_hInternet, m_sURL, NULL, 0,
		INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE, 0 );

	if ( hRequest == NULL )
	{
		InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
		PostMessage( WM_TIMER, FALSE );
		return;
	}

	DWORD nLength, nlLength = 4;
	DWORD nRemaining = 0;
	BYTE pBuffer[1024];
	CMemFile pFile;

	if ( HttpQueryInfo( hRequest, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER,
		&nLength, &nlLength, NULL ) )
	{
		m_wndProgress.PostMessage( PBM_SETRANGE32, 0, nLength );
	}

	nLength = 0;

	while ( InternetQueryDataAvailable( hRequest, &nRemaining, 0, 0 ) && nRemaining > 0 )
	{
		nLength += nRemaining;
		m_wndProgress.PostMessage( PBM_SETPOS, nLength );

		while ( nRemaining > 0 )
		{
			DWORD nBuffer = min( nRemaining, DWORD(1024) );
			InternetReadFile( hRequest, pBuffer, nBuffer, &nBuffer );
			pFile.Write( pBuffer, nBuffer );
			nRemaining -= nBuffer;
		}
	}

	pFile.Seek( 0, CFile::begin );

	BOOL bSuccess = HostCache.eDonkey.ImportMET( &pFile );
	if ( bSuccess ) HostCache.Save();

	InternetCloseHandle( m_hInternet );
	m_hInternet = NULL;

	PostMessage( WM_TIMER, bSuccess ? 1 : 0 );
}