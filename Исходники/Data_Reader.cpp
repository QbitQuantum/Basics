static FILE* blargg_fopen( const char path [], const char mode [] )
{
	FILE* file = NULL;
	wchar_t* wmode = NULL;
	wchar_t* wpath = NULL;
	
	wpath = blargg_to_wide( path );
	if ( wpath )
	{
		wmode = blargg_to_wide( mode );
		if ( wmode )
			file = _wfopen( wpath, wmode );
	}
	
	// Save and restore errno in case free() clears it
	int saved_errno = errno;
	free( wmode );
	free( wpath );
	errno = saved_errno;
	
	return file;
}