// Execute the requested client command
DWORD Execute( HANDLE hPipe, RemComMessage* pMsg, DWORD* pReturnCode )
{
	PROCESS_INFORMATION pi;

	STARTUPINFO si;
	::ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);

	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = true;
	saAttr.lpSecurityDescriptor = NULL;
	HANDLE hStdoutRead = INVALID_HANDLE_VALUE, hStdoutWrite = INVALID_HANDLE_VALUE;
	HANDLE hStdinRead = INVALID_HANDLE_VALUE, hStdinWrite = INVALID_HANDLE_VALUE;

	if (!CreatePipe(&hStdoutRead, &hStdoutWrite, &saAttr, 0))
		return 20000+GetLastError();

	if (!SetHandleInformation(hStdoutRead, HANDLE_FLAG_INHERIT, 0))
		return 30000+GetLastError();	// don't inherit the reader end

	if (!CreatePipe(&hStdinRead, &hStdinWrite, &saAttr, 0))
		return 40000+GetLastError();

	if (!SetHandleInformation(hStdinWrite, HANDLE_FLAG_INHERIT, 0))
		return 50000+GetLastError();	// don't inherit the reader end

	si.hStdInput = hStdinRead;
	si.hStdOutput = hStdoutWrite;
	si.hStdError = hStdoutWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;
	
	*pReturnCode = 0;

	// Initializes command
	// cmd.exe /c /q allows us to execute internal dos commands too.
	TCHAR szCommand[_MAX_PATH];
	_stprintf_s( szCommand, sizeof(szCommand), _T("cmd.exe /q /c \"%s\""), pMsg->szCommand );

	if (!::ImpersonateNamedPipeClient(hPipe))
		return 60000+GetLastError();

	HANDLE hImpersonationToken,hPrimaryToken;
	if (!::OpenThreadToken(::GetCurrentThread(),TOKEN_ALL_ACCESS,TRUE,&hImpersonationToken))
		return 70000+GetLastError();

	if (!::DuplicateTokenEx(hImpersonationToken,MAXIMUM_ALLOWED,0,
		SecurityIdentification, TokenPrimary,&hPrimaryToken))
		return 80000+GetLastError();
	CloseHandle(hImpersonationToken);
	RevertToSelf();

   // Start the requested process
	if ( CreateProcessAsUser(hPrimaryToken, 
         NULL, 
         szCommand, 
         NULL,
         NULL, 
         TRUE,
         pMsg->dwPriority | CREATE_NO_WINDOW,
         NULL, 
         pMsg->szWorkingDir[0] != _T('\0') ? pMsg->szWorkingDir : NULL, 
         &si, 
         &pi ) )
   {
		HANDLE hProcess = pi.hProcess;
		// these handles are meant only for the child process, otherwise we'll block forever
		CloseHandle(hStdinRead);
		CloseHandle(hStdoutWrite);

		// pump the stdin from the client to the child process
		// in a different thread
		CopyThreadParams* ctp = new CopyThreadParams();
		ctp->hPipe = hPipe;
		ctp->hStdin = hStdinWrite;
		_beginthread(CopyStream,0,ctp);

		// feed the output from the child process to the client
		while (true) {
			byte buf[1024];
			DWORD dwRead = 0, dwWritten;

			if (!::ReadFile(hStdoutRead,buf+4,sizeof(buf)-4,&dwRead,NULL) || dwRead==0)
				break;

			*((DWORD*)buf) = dwRead;
			::WriteFile(hPipe, buf, sizeof(DWORD)+dwRead, &dwWritten, NULL);
		}

		*pReturnCode = 0;

		// Waiting for process to terminate
        WaitForSingleObject( hProcess, INFINITE );
        GetExitCodeProcess( hProcess, pReturnCode );
		return 0;
	} else {
		// error code 1314 here means the user of this process
		// doesn't have the privilege to call CreateProcessAsUser.
		// when this is run as a service, the LOCAL_SYSTEM user
		// has a privilege to do it, but if you run this under
		// the debugger, your user account might not have that privilege.
		//
		// to fix that, go to control panel / administartive tools / local security policy
		// user rights / replace process token level
		// and make sure your user is in.
		// once the above is set, the system needs to be restarted.
		return 10000+GetLastError();
	}
}