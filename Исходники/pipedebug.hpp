	DWORD ___pipesentmessage(const TCHAR * szSent){
		DWORD dwReserved=PIPE_READMODE_MESSAGE;
	    if (!SetNamedPipeHandleState(hdPipe,&dwReserved,NULL,NULL))
			Func_FastPMNTS(_T("SetNamedPipeHandleState() Error! (%ld)\n"),GetLastError());
	    if (!WriteFile(hdPipe,szSent,(lstrlen(szSent)+1)*sizeof(TCHAR),&dwReserved,NULL))
			Func_FastPMNTS(_T("WriteFile() Error! (%ld)\n"),GetLastError());
	    return GetLastError();
	}