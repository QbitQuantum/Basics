bool CSys::ReadURL_( const char *pcURL, CStr *poContent )
{
	HINTERNET hINet, hFile;
	hINet = InternetOpen( "InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
	if ( !hINet )
		return false;
	hFile = InternetOpenUrl( hINet, pcURL, NULL, 0, INTERNET_FLAG_RELOAD, 0 ); // new: INTERNET_FLAG_RELOAD
	if ( hFile )
	{
		CHAR buffer[1025];
		DWORD dwRead;
		poContent->Clear();
		while( InternetReadFile( hFile, buffer, sizeof(buffer)-1, &dwRead ) )
		{
			if( !dwRead  )
				break;
			buffer[dwRead] = 0;
			poContent->Append( buffer );
		}
		InternetCloseHandle( hFile );
	}
	InternetCloseHandle( hINet );
	return true;
}