BOOL CFileControlTool::GetNameByType( HANDLE h, WORD type,LPTSTR str, DWORD processId )   
{   
	ULONG size = 0x2000;   
	UNICODE_STRING* lpBuffer = NULL;   
	BOOL ret = FALSE;   

	HANDLE handle;   
	HANDLE hRemoteProcess = NULL;   
	BOOL remote = processId != GetCurrentProcessId();   
	DWORD dwId = 0;   
 

	if ( remote )   
	{   
		hRemoteProcess = OpenProcess(PROCESS_DUP_HANDLE,TRUE,processId);   

		if ( hRemoteProcess == NULL )   
			return FALSE;   
		DuplicateHandle(hRemoteProcess,h,GetCurrentProcess(),&handle,0,FALSE,DUPLICATE_SAME_ACCESS);   
	}   
	else   
		handle = h;   

	// let's be happy, handle is in our process space, so query the infos :)   
	switch( type )   
	{   
	case OB_TYPE_PROCESS:   
		GetProcessId( handle, dwId );   

		_stprintf(str, _T("PID: 0x%X"), dwId );   

		ret = TRUE;   
		goto cleanup;   
		break;   

	case OB_TYPE_THREAD:   
		GetProcessId( handle, dwId );   

		_stprintf(str,_T("TID: 0x%X") , dwId );   

		ret = TRUE;   
		goto cleanup;   
		break;   

	case OB_TYPE_FILE:   
		ret = GetFileName( handle, str );   

		// access denied :(   
		if ( ret && '\0' == str[0])   
			goto cleanup;   
		break;   

	};

	NtQueryObject ( handle, 1, NULL, 0, &size );   

	// let's try to use the default   
	if ( size == 0 )   
		size = 0x2000;   

	lpBuffer = (UNICODE_STRING *)new UCHAR[size];   

	if ( NtQueryObject( handle, 1, lpBuffer, size, NULL ) == 0 )   
	{  
		wcscpy(lpBuffer->Buffer,str);
		//SystemInfoUtils::Unicode2CString( (UNICODE_STRING*)lpBuffer, str );   
		ret = TRUE;   
	}   

cleanup:   

	if ( remote )   
	{   
		if ( hRemoteProcess != NULL )   
			CloseHandle( hRemoteProcess );   

		if ( handle != NULL )   
			CloseHandle( handle );   
	}   

	if ( lpBuffer != NULL )  
	{
		delete [] lpBuffer; 
		lpBuffer = NULL;
	}

	return ret;   
}   