static boolean runcmdshell (Handle hshell, Handle hcommand, HANDLE *hprocess, HANDLE *hout, HANDLE *herr) {

	/*
	2006-03-09 aradke: launch the command shell as a child process.
		we consume hshell, but caller is responsible for closing hout if we return true.
	*/
	
	Handle hcmdline = nil;
	SECURITY_ATTRIBUTES securityinfo;
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION processinfo;
	HANDLE houtread = nil;
	HANDLE houtwrite = nil;
	HANDLE herrread = nil;
	HANDLE herrwrite = nil;
	boolean fl;
	
	*hprocess = nil;
	
	/*create pipes for reading from command shell*/

	clearbytes (&securityinfo, sizeof (securityinfo));
	securityinfo.nLength				= sizeof (securityinfo);
	securityinfo.lpSecurityDescriptor	= nil;
	securityinfo.bInheritHandle			= true;
	
	if (hout) { /*caller interested in stdout*/
	
		if (!CreatePipe (&houtread, &houtwrite, &securityinfo, nil))
			goto error;
		
		if (!SetHandleInformation (houtread, HANDLE_FLAG_INHERIT, 0))
			goto error;
		}
	else
		houtwrite = GetStdHandle (STD_OUTPUT_HANDLE);

	if (herr) { /*caller interested in stderr*/

		if (!CreatePipe (&herrread, &herrwrite, &securityinfo, nil))
			goto error;
		
		if (!SetHandleInformation (herrread, HANDLE_FLAG_INHERIT, 0))
			goto error;
		}
	else
		herrwrite = GetStdHandle (STD_ERROR_HANDLE);
		
	/*init structs for creating process*/
	
	clearbytes (&startupinfo, sizeof (startupinfo));
	startupinfo.cb = sizeof (startupinfo);
	startupinfo.dwFlags		= STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startupinfo.hStdInput	= GetStdHandle (STD_INPUT_HANDLE);
	startupinfo.hStdOutput	= houtwrite;
	startupinfo.hStdError	= herrwrite;
	startupinfo.wShowWindow	= SW_HIDE;
	
	clearbytes (&processinfo, sizeof (processinfo));
	
	/*synthesize command string*/
	
	if (!inserttextinhandle (hcommand, 0, "\x04" " /c "))
		goto exit;
	
	if (!concathandles (hshell, hcommand, &hcmdline))
		goto exit;
	
	if (!pushcharhandle (CHNULL, hshell))
		goto exit;

	if (!pushcharhandle (CHNULL, hcmdline))
		goto exit;
	
	/*check whether command shell can be accessed*/
	
	if (!cmdshellexists (hshell)) {
		if (!searchcmdpath (&hshell))	/*do a search path lookup, sets error*/
			goto exit;
		}
		
	/*create command shell process*/
	
	lockhandle (hshell);
	lockhandle (hcmdline);
	
	fl = CreateProcess (
			*hshell,		/*IN LPCSTR lpApplicationName*/
			*hcmdline,		/*IN LPSTR lpCommandLine*/
			nil,			/*IN LPSECURITY_ATTRIBUTES lpProcessAttributes*/
			nil,			/*IN LPSECURITY_ATTRIBUTES lpThreadAttributes*/
			true,			/*IN BOOL bInheritHandles*/
			0,				/*IN DWORD dwCreationFlags*/
			nil,			/*IN LPVOID lpEnvironment: use parent's*/
			nil,			/*IN LPCSTR lpCurrentDirectory: use parent's*/
			&startupinfo,	/*IN LPSTARTUPINFOA lpStartupInfo*/
			&processinfo);	/*OUT LPPROCESS_INFORMATION lpProcessInformation*/
	
	unlockhandle (hshell);
	unlockhandle (hcmdline);
	
	/*handle result*/
	
	if (!fl)
		goto error;
	
	CloseHandle (houtwrite);	/*now inherited by child process*/
	CloseHandle (herrwrite);
	
	CloseHandle (processinfo.hThread);
	
	disposehandle (hcmdline);
	disposehandle (hshell);
	
	*hprocess = processinfo.hProcess;
	
	if (hout)
		*hout = houtread;
	
	if (herr)
		*herr = herrread;
	
	return (true);

error:
	winerror (); /*note fall through*/
		
exit:	/*error is already set*/
	if (hout && !houtread)
		CloseHandle (houtread);
	
	if (hout && !houtwrite)
		CloseHandle (houtwrite);
	
	if (herr && !herrread)
		CloseHandle (herrread);
	
	if (herr && !herrwrite)
		CloseHandle (herrwrite);

	disposehandle (hcmdline);
	disposehandle (hshell);
	
	return (false);	
	} /*runcmdshell*/