BOOL WINAPI OnCreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	//typedef BOOL (WINAPI* OnCreateProcessW_t)(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
	ORIGINAL_KRNL(CreateProcessW);
	BOOL lbRc = FALSE;
	DWORD dwErr = 0;
	DWORD ldwCreationFlags = dwCreationFlags;

	if (ph && ph->PreCallBack)
	{
		SETARGS10(&lbRc, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, ldwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

		// Если функция возвращает FALSE - реальное чтение не будет вызвано
		if (!ph->PreCallBack(&args))
			return lbRc;
	}

	CShellProc* sp = new CShellProc();
	if (!sp || !sp->OnCreateProcessW(&lpApplicationName, (LPCWSTR*)&lpCommandLine, &lpCurrentDirectory, &ldwCreationFlags, lpStartupInfo))
	{
		delete sp;
		SetLastError(ERROR_FILE_NOT_FOUND);
		return FALSE;
	}

	if ((ldwCreationFlags & CREATE_SUSPENDED) == 0)
	{
		DebugString(L"CreateProcessW without CREATE_SUSPENDED Flag!\n");
	}

	#ifdef _DEBUG
	SetLastError(0);
	#endif

	#ifdef SHOWCREATEPROCESSTICK
	prepare_timings;
	force_print_timings(L"CreateProcessW");
	#endif

	#if 0
	// This is disabled for now. Command will create new visible console window,
	// but excpected behavior will be "reuse" of existing console window
	if (!sp->GetArgs()->bNewConsole && sp->GetArgs()->pszUserName)
	{
		LPCWSTR pszName = sp->GetArgs()->pszUserName;
		LPCWSTR pszDomain = sp->GetArgs()->pszDomain;
		LPCWSTR pszPassword = sp->GetArgs()->szUserPassword;
		STARTUPINFOW si = {sizeof(si)};
		PROCESS_INFORMATION pi = {};
		DWORD dwOurFlags = (ldwCreationFlags & ~EXTENDED_STARTUPINFO_PRESENT);
		lbRc = CreateProcessWithLogonW(pszName, pszDomain, (pszPassword && *pszPassword) ? pszPassword : NULL, LOGON_WITH_PROFILE,
			lpApplicationName, lpCommandLine, dwOurFlags, lpEnvironment, lpCurrentDirectory,
			&si, &pi);
		if (lbRc)
			*lpProcessInformation = pi;
	}
	else
	#endif
	{
		lbRc = F(CreateProcessW)(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, ldwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	}
	dwErr = GetLastError();

	#ifdef SHOWCREATEPROCESSTICK
	force_print_timings(L"CreateProcessW - done");
	#endif

	// Если lbParamsChanged == TRUE - об инжектах позаботится ConEmuC.exe
	sp->OnCreateProcessFinished(lbRc, lpProcessInformation);
	delete sp;

	#ifdef SHOWCREATEPROCESSTICK
	force_print_timings(L"OnCreateProcessFinished - done");
	#endif


	if (ph && ph->PostCallBack)
	{
		SETARGS10(&lbRc, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, ldwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
		ph->PostCallBack(&args);
	}

	SetLastError(dwErr);
	return lbRc;
}