//Imago 9/14
ZString UTL::DoHTTP(char * szHdrs, char * szHost, char * szVerb, char * szUri, char * PostData, int PostLength, bool bSecure) {
	
	// BT - 7/15 - Fixing handle leaks.
	ZString Response("Finished\n");
	
	HINTERNET hSession = InternetOpenA( "Allegiance", INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(hSession) {
		HINTERNET hConnect = InternetConnectA(hSession,szHost,(bSecure) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,NULL,NULL);
		if (!hConnect)
			debugf( "Failed to connect to %s\n", szHost);
		else
		{
			debugf("%s %s",szVerb,szUri);
			HINTERNET hRequest = HttpOpenRequestA(hConnect,szVerb,szUri,NULL,NULL,NULL,(bSecure) ? INTERNET_FLAG_SECURE|INTERNET_FLAG_NO_CACHE_WRITE : INTERNET_FLAG_NO_CACHE_WRITE,0);
			if (!hRequest)
				debugf( "Failed to open request handle\n" );
			else
			{
				DWORD dwFlags;
				DWORD dwBuffLen = sizeof(dwFlags);
				InternetQueryOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS,(LPVOID)&dwFlags, &dwBuffLen);
				dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;

				// BT - 7/15 - CSS Service integration
				dwFlags |= INTERNET_FLAG_IGNORE_CERT_CN_INVALID; // Enables usage of locally generated certs. Not very secure, but works if you are on a shoestring budget!
				dwFlags |= INTERNET_FLAG_IGNORE_CERT_DATE_INVALID; // Enables usage of locally generated certs. Not very secure, but works if you are on a shoestring budget!

				InternetSetOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS,&dwFlags,sizeof(dwFlags));
				
				if (PostLength == 0)
					PostData = NULL;

				// BT - 7/15 - Cleaned up handle leaks.
				if(HttpSendRequestA(hRequest,szHdrs,strlen(szHdrs),PostData,PostLength))
				{	
					char pcBuffer[4096];
					DWORD dwBytesRead = 0;

					debugf("\nThe following was returned by the server:\n");
		
					if(InternetReadFile(hRequest, pcBuffer, 4096-1, &dwBytesRead))
					{
						pcBuffer[dwBytesRead]=0x00; // Null-terminate buffer
						debugf("%s", pcBuffer);
						Response = ZString(pcBuffer, (int)dwBytesRead);
					}
					else
					{
						debugf("\nInternetReadFile failed\n");
					}

					debugf("\n");
				}

				if (!InternetCloseHandle(hRequest))
					debugf( "Failed to close Request handle\n" );
			}

			if(!InternetCloseHandle(hConnect))
				debugf("Failed to close Connect handle\n");
		}

		if( InternetCloseHandle( hSession ) == FALSE )
			debugf( "Failed to close Session handle\n" );

		DWORD dwError = GetLastError();
		debugf( "\nFinished: %d.\n",dwError);
		return Response;
	} 
	else 
	{
		debugf("Failed to open WinInet session\n");
		return "Failed to open WinInet session\n";
	}
}