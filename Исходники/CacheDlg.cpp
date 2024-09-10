void CCacheDlg::RemoveFromCache(const CString& path)
{
	// if we use the external cache, we tell the cache directly that something
	// has changed, without the detour via the shell.
	HANDLE hPipe = CreateFile( 
		GetCacheCommandPipeName(),	// pipe name 
		GENERIC_READ |					// read and write access 
		GENERIC_WRITE, 
		0,								// no sharing 
		NULL,							// default security attributes
		OPEN_EXISTING,					// opens existing pipe 
		FILE_FLAG_OVERLAPPED,			// default attributes 
		NULL);							// no template file 


	if (hPipe != INVALID_HANDLE_VALUE) 
	{
		// The pipe connected; change to message-read mode. 
		DWORD dwMode; 

		dwMode = PIPE_READMODE_MESSAGE; 
		if(SetNamedPipeHandleState( 
			hPipe,    // pipe handle 
			&dwMode,  // new pipe mode 
			NULL,     // don't set maximum bytes 
			NULL))    // don't set maximum time 
		{
			DWORD cbWritten; 
			TGITCacheCommand cmd;
			cmd.command = TGITCACHECOMMAND_CRAWL;
			wcsncpy(cmd.path, path, MAX_PATH);
			BOOL fSuccess = WriteFile( 
				hPipe,			// handle to pipe 
				&cmd,			// buffer to write from 
				sizeof(cmd),	// number of bytes to write 
				&cbWritten,		// number of bytes written 
				NULL);			// not overlapped I/O 

			if (! fSuccess || sizeof(cmd) != cbWritten)
			{
				DisconnectNamedPipe(hPipe); 
				CloseHandle(hPipe); 
				hPipe = INVALID_HANDLE_VALUE;
			}
			if (hPipe != INVALID_HANDLE_VALUE)
			{
				// now tell the cache we don't need it's command thread anymore
				DWORD cbWritten; 
				TGITCacheCommand cmd;
				cmd.command = TGITCACHECOMMAND_END;
				WriteFile( 
					hPipe,			// handle to pipe 
					&cmd,			// buffer to write from 
					sizeof(cmd),	// number of bytes to write 
					&cbWritten,		// number of bytes written 
					NULL);			// not overlapped I/O 
				DisconnectNamedPipe(hPipe); 
				CloseHandle(hPipe); 
				hPipe = INVALID_HANDLE_VALUE;
			}
		}
		else
		{
			ATLTRACE("SetNamedPipeHandleState failed"); 
			CloseHandle(hPipe);
		}
	}
}