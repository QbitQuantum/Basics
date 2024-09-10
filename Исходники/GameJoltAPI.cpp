bool GameJoltAPI::SendRequest( CStdString &output, CStdString url )
{

	// The private key must be set to send a request.
	if ( m_GamePrivateKey == _T("") )
	{
		m_ErrorMessage += _T("(You must put in your game's private key before you can use any of the API functions.)");
		return false;
	}

	////////////////////////////////////
	// Let's form the URL first.

	url = GJAPI_ROOT + GJAPI_VERSION + url;
	CStdString signature( md5( CStdStringA( _T("http://") + GJAPI_SERVER + url + m_GamePrivateKey ) ) );
	url += _T("&signature=") + signature;

	// Now let's build the request.
	BOOL ret = FALSE;
	HINTERNET hSession = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;

	hSession = WinHttpOpen
	(
		L"Game Jolt API Construct/1.0", 
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, 
		WINHTTP_NO_PROXY_BYPASS, 
		0
	);

	if ( hSession )
		hConnect = WinHttpConnect
		( 
			hSession, 
			CStdStringW( GJAPI_SERVER ),
			INTERNET_DEFAULT_PORT, 
			0
		);
	else
		m_ErrorMessage += _T("(Could not open HTTP session.)");

	if ( hConnect )
		hRequest = WinHttpOpenRequest
		( 
			hConnect,
			L"GET",
			CStdStringW( url ),
			NULL,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH
		);
	else
		m_ErrorMessage += _T("(Could not connect to the HTTP session.)");

	if ( hRequest ) 
		ret = WinHttpSendRequest
		( 
			hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0,
			WINHTTP_NO_REQUEST_DATA,
			0,
			0,
			0
		);
	else
		m_ErrorMessage += _T("(Could not set up the HTTP request.)");

	if ( ret )
		ret = WinHttpReceiveResponse( hRequest, NULL );
	else
		m_ErrorMessage += _T("(Could not send the HTTP request.)");

	DWORD bufferSize = 0;
	DWORD outputDownloaded = 0;
	LPSTR outputBuffer = 0;

	// Keep checking for data until there is nothing left.
	if ( ret )
	{
		do 
		{

			// Check for available data.
			bufferSize = 0;
			WinHttpQueryDataAvailable( hRequest, &bufferSize );

			// Allocate space for the buffer.
			outputBuffer = new char[bufferSize + 1];
			if ( outputBuffer )
			{
				// Read the data.
				ZeroMemory( outputBuffer, bufferSize + 1 );

				if ( WinHttpReadData( hRequest, (LPVOID)outputBuffer, bufferSize, &outputDownloaded ) )
					output += outputBuffer;

				// Free the memory allocated to the buffer.
				delete [] outputBuffer;
			}

		} while( bufferSize > 0 );
	}
	else
		m_ErrorMessage += _T("(Did not get a response from the server.)");

	if ( hRequest ) WinHttpCloseHandle( hRequest );
    if ( hConnect ) WinHttpCloseHandle( hConnect );
    if ( hSession ) WinHttpCloseHandle( hSession );

	return true;

}