char *WriteToTemporaryFile(const char *format,...)
{
	HANDLE temporary_file_handle;
	char temporary_filename[MAX_PATH+1];  
	char temporary_path[MAX_PATH+1];
	DWORD buffer_size=MAX_PATH+1;

	// Get the temp path.
	DWORD return_value=GetTempPathA(buffer_size,	// length of the buffer
			temporary_path); // buffer for path 
	if(return_value > buffer_size ||(return_value==0))
	{
		printf("GetTempPath failed with error %d.\n",GetLastError());
		return NULL;
	}

	temporary_filename[ sizeof(temporary_filename) - sizeof( char ) ] = NULL;
	if( _snprintf( temporary_filename, sizeof(temporary_filename) - sizeof( char ),
			"%s\\DarunGrim-%x-%x.idc", temporary_path, GetCurrentProcessId(), GetCurrentThreadId() ) > 0 )
	{
		// Create the new file to write the upper-case version to.
		temporary_file_handle=CreateFile((LPTSTR)temporary_filename,// file name 
				GENERIC_READ | GENERIC_WRITE,// open r-w 
				0,					// do not share 
				NULL,				// default security 
				CREATE_ALWAYS,		// overwrite existing
				FILE_ATTRIBUTE_NORMAL,// normal file 
				NULL);				// no template 
		if(temporary_file_handle==INVALID_HANDLE_VALUE) 
		{ 
			printf("CreateFile failed with error %d.\n",GetLastError());
			return NULL;
		} 

		va_list args;
		va_start(args,format);
		char Contents[1024]={0,};
		_vsnprintf(Contents,sizeof(Contents)/sizeof(char),format,args);
		va_end(args);

		DWORD dwBytesWritten;
		BOOL fSuccess=WriteFile(temporary_file_handle,
			Contents,
			strlen(Contents),
			&dwBytesWritten,
			NULL); 
		if(!fSuccess) 
		{
			printf("WriteFile failed with error %d.\n",GetLastError());
			return NULL;
		}
		CloseHandle(temporary_file_handle);
		return _strdup(temporary_filename);
	}
	return NULL;
}