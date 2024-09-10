BOOL CBitprintsDownloader::ExecuteRequest()
{
	const DWORD tTime = GetTickCount();

	theApp.Message( MSG_DEBUG | MSG_FACILITY_OUTGOING, L"[Bitprints] Sent request: %s", (LPCTSTR)m_sURL );

	CString strHost = m_sURL;
	int nPos = strHost.Find( L"http://" );
	if ( nPos != 0 ) return FALSE;
	strHost = strHost.Mid( 7 );
	nPos = strHost.Find( L'/' );
	if ( nPos < 0 ) return FALSE;
	CString strPath = strHost.Mid( nPos );
	strHost = strHost.Left( nPos );
	nPos = strHost.Find( L':' );

	int nPort = INTERNET_DEFAULT_HTTP_PORT;

	if ( nPos > 0 )
	{
		_stscanf( strHost.Mid( nPos + 1 ), L"%i", &nPort );
		strHost = strHost.Left( nPos );
	}

	if ( m_hSession == NULL )
	{
		m_hSession = InternetConnect( m_hInternet, strHost, INTERNET_PORT( nPort ),
			NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );
		if ( m_hSession == NULL )
			return FALSE;
	}

	m_hRequest = HttpOpenRequest( m_hSession, L"GET", strPath, NULL, NULL, NULL,
		INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0 );

	if ( m_hRequest == NULL )
	{
		if ( m_hSession ) InternetCloseHandle( m_hSession );

		m_hSession = InternetConnect( m_hInternet, strHost, INTERNET_PORT( nPort ),
			NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );

		if ( m_hSession == NULL ) return FALSE;

		m_hRequest = HttpOpenRequest( m_hSession, L"GET", strPath, NULL, NULL, NULL,
			INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0 );

		if ( m_hRequest == NULL ) return FALSE;
	}

	if ( ! HttpSendRequest( m_hRequest, NULL, 0, NULL, 0 ) )
		return FALSE;

	TCHAR szStatusCode[32] = {};
	DWORD nStatusCode = 0, nStatusLen = 32;

	if ( ! HttpQueryInfo( m_hRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &nStatusLen, NULL ) )
		return FALSE;

	if ( _stscanf( szStatusCode, L"%lu", &nStatusCode ) != 1 ||
		 nStatusCode < 200 || nStatusCode > 299 )
		return FALSE;

	LPBYTE pResponse = NULL;
	DWORD nRemaining, nResponse = 0;

	while ( InternetQueryDataAvailable( m_hRequest, &nRemaining, 0, 0 ) && nRemaining > 0 )
	{
		BYTE* pNewResponse = (BYTE*)realloc( pResponse, nResponse + nRemaining );
		if ( ! pNewResponse )
		{
			free( pResponse );
			return FALSE;
		}
		pResponse = pNewResponse;
		InternetReadFile( m_hRequest, pResponse + nResponse, nRemaining, &nRemaining );
		nResponse += nRemaining;
	}

	if ( nRemaining )
	{
		free( pResponse );
		return FALSE;
	}

	m_sResponse.Empty();

	LPTSTR pszResponse = m_sResponse.GetBuffer( nResponse );
	for ( nStatusCode = 0; nStatusCode < nResponse; nStatusCode++ )
		pszResponse[ nStatusCode ] = (TCHAR)pResponse[ nStatusCode ];
	m_sResponse.ReleaseBuffer( nResponse );

	free( pResponse );

	if ( m_hRequest ) InternetCloseHandle( m_hRequest );
	m_hRequest = NULL;

	m_nDelay = ( GetTickCount() - tTime ) * 2;

	return TRUE;
}