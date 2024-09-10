// > 0: http error
// -1: Keine Internet-Verbindung
// -2: URL konnte nicht geöffnet werden
// -3: Zu gro?
// -4: Kein Speicher
// -5: Fehler beim Lesen
int
CIniFile::ReadWebFile( LPCTSTR url, CStr &content, int size, int cp )
{
    HINTERNET web = NULL, file = NULL;
    char  *buffer = NULL;
    char  *tmpStr = NULL;
    ULONG  blockSize, fileSize, readSize;
    ULONG  bufSize;
    BOOL   rc     = 0;

    if ( Proxy.IsEmpty() )
    {
#ifdef DESKTOP
		web  = InternetOpen( L"MortScript", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
#else
        web  = InternetOpen( L"MortScript", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0 );
#endif
    }
    else
    {
		web  = InternetOpen( L"MortScript", INTERNET_OPEN_TYPE_PROXY, (LPCTSTR)Proxy, NULL, 0 );
    }

    if ( web == NULL )
	{
        int error = GetLastError();
		rc = -1;
	}

    if ( rc == 0 )
    {
	    file = InternetOpenUrl( web, url, NULL, 0, INTERNET_FLAG_RELOAD, 0 );
	    if ( file == NULL )
	    {
            int error = GetLastError();
		    rc = -2;
	    }
    }

    if ( rc == 0 )
    {
	    if ( _tcsncmp( url, L"http", 4 ) == 0 )
	    {
		    // No http error?
		    TCHAR status[MAX_PATH];
            DWORD length=MAX_PATH;
		    if ( HttpQueryInfo( file, HTTP_QUERY_STATUS_CODE, status, &length, NULL ) )
		    {
			    if ( _ttol( status ) != 200 )
			    {
				    rc = _ttol( status );
			    }
		    }
	    }
    }

    if ( rc == 0 )
    {
		fileSize = 0;

        BOOL more = InternetQueryDataAvailable( file, &blockSize, 0, 0 );
        tmpStr = (char*)malloc(blockSize+1);

		while ( rc == 0 && more && blockSize > 0 && tmpStr != NULL )
		{
			int stat = InternetReadFile( file, (void*)(tmpStr+fileSize), blockSize, &readSize );
			if ( stat == 0 )
			{
				int error = GetLastError();
				rc = -5;
			}
			else
			{
				tmpStr[fileSize+readSize] = '\0';
				fileSize += readSize;
				more = InternetQueryDataAvailable( file, &blockSize, 0, 0 );
				if ( more && blockSize > 0 )
				{
					if ( fileSize + blockSize > 256 * 1024 )
					{
						// Too big
						rc = -3;
					}
					else
					{
						void *movedStr = realloc( tmpStr, fileSize+blockSize+1 );
						if ( movedStr == NULL )
						{
							more = FALSE;
							rc = -4;
						}
						else
							tmpStr = (char*)movedStr;
					}
				}
			}
		}
    }

    if ( rc == 0 )
    {
        bufSize  = (fileSize+1)*sizeof(TCHAR);
        buffer   = (char*)content.GetBufferSetLength( fileSize+1 );
        if ( buffer == NULL )
	    {
		    rc = -4;
        }
    }

    if ( rc == 0 )
    {
    	tmpStr[fileSize] = '\0';

        if ( cp == CP_ACP ) // Default: Device's encoding
		{
			// Copy first few lines
			char scanText[256];
			strncpy( scanText, tmpStr, 255 );
			scanText[255] = '\0';
			_strlwr( scanText );

			// Unicode?
			if (   strstr( scanText, "utf8" )
				|| strstr( scanText, "utf-8" )
			   )
			{
				cp = CP_UTF8;
			}
			if ( strstr( scanText, "iso-8835-1" ) )
			{
				cp = 1252;
			}
		}

		if ( cp != CP_UNICODE )
			MultiByteToWideChar( cp, 0, tmpStr, fileSize+1, (LPTSTR)buffer, bufSize );
		else
			strcpy( buffer, tmpStr );
    }

    if ( file   != NULL ) InternetCloseHandle( file );
    if ( web    != NULL ) InternetCloseHandle( web );
    if ( buffer != NULL ) content.ReleaseBuffer();
    if ( tmpStr != NULL ) free(tmpStr);

    return rc;
}