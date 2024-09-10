BOOL DoBlockingHttpGet( const char* sRequestedPage, char* pBufferOut, const unsigned int /*nBufferOutSize*/, DWORD* pBytesRead )
{
	BOOL bResults = FALSE, bSuccess = FALSE;
	HINTERNET hSession = nullptr, hConnect = nullptr, hRequest = nullptr;

	WCHAR wBuffer[1024];
	size_t nTemp;
	char* sDataDestOffset = &pBufferOut[0];
	DWORD nBytesToRead = 0;
	DWORD nBytesFetched = 0;

	char sClientName[1024];
	sprintf_s( sClientName, 1024, "Retro Achievements Client" );
	WCHAR wClientNameBuffer[1024];
	mbstowcs_s( &nTemp, wClientNameBuffer, 1024, sClientName, strlen(sClientName)+1 );

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen( wClientNameBuffer, 
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, 
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if( hSession != nullptr )
	{
		hConnect = WinHttpConnect( hSession, L"www.retroachievements.org", INTERNET_DEFAULT_HTTP_PORT, 0);

		// Create an HTTP Request handle.
		if( hConnect != nullptr )
		{
			mbstowcs_s( &nTemp, wBuffer, 1024, sRequestedPage, strlen(sRequestedPage)+1 );

			hRequest = WinHttpOpenRequest( hConnect, 
				L"GET", 
				wBuffer, 
				NULL, 
				WINHTTP_NO_REFERER, 
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				0);

			// Send a Request.
			if( hRequest != nullptr )
			{
				bResults = WinHttpSendRequest( hRequest, 
					L"Content-Type: application/x-www-form-urlencoded",
					0, 
					WINHTTP_NO_REQUEST_DATA,
					0, 
					0,
					0);

				if( WinHttpReceiveResponse( hRequest, NULL ) )
				{
					nBytesToRead = 0;
					(*pBytesRead) = 0;
					WinHttpQueryDataAvailable( hRequest, &nBytesToRead );

					while( nBytesToRead > 0 )
					{
						char sHttpReadData[8192];
						ZeroMemory( sHttpReadData, 8192*sizeof(char) );

						assert( nBytesToRead <= 8192 );
						if( nBytesToRead <= 8192 )
						{
							nBytesFetched = 0;
							if( WinHttpReadData( hRequest, &sHttpReadData, nBytesToRead, &nBytesFetched ) )
							{
								assert( nBytesToRead == nBytesFetched );

								//Read: parse buffer
								memcpy( sDataDestOffset, sHttpReadData, nBytesFetched );

								sDataDestOffset += nBytesFetched;
								(*pBytesRead) += nBytesFetched;
							}
						}

						bSuccess = TRUE;

						WinHttpQueryDataAvailable( hRequest, &nBytesToRead );
					}
				}
			}
		}
	}


	// Close open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return bSuccess;
}