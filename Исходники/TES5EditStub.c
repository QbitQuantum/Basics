STATIC int ExecuteTarget(LPTSTR lpCmdLine)
{
	HWND hWnd = NULL;
	// DWORD dwExitCode = ERROR_SUCCESS;
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { sizeof(STARTUPINFO), 0 };
	
	/* Execute the process */
	if (CreateProcess(
		NULL,	/* No module name (use command line) */
		lpCmdLine,	/* Command line */
		NULL,	/* Process handle not inheritable */
		NULL,	/* Thread handle not inheritable */
		FALSE,	/* Set handle inheritance to FALSE */
		0,	/* No creation flags */
		NULL,	/* Use parent's environment block */
		NULL,	/* Use parent's starting directory */
		&si,	/* Pointer to STARTUPINFO structure */
		&pi	/* Pointer to PROCESS_INFORMATION structure */
	)) {
		DWORD dwProcessId = 0;
		
		/* Wait until target executable has finished its initialization */
		WaitForInputIdle(pi.hProcess, INFINITE);

		/* Find target executable window */
		hWnd = GetTopWindow(0);
		while(hWnd != NULL) {
			GetWindowThreadProcessId(hWnd, &dwProcessId);
			if (dwProcessId == pi.dwProcessId) {
				/* And move it to the top. */
				SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
		}

		/* Wait until target executable exits. */
		// Nah
		//WaitForSingleObject(pi.hProcess, INFINITE);
		//GetExitCodeProcess(pi.hProcess, &dwExitCode);

		/* Close process and thread handles. */
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	} else {
		FatalError(ERROR_SUCCESS, _T("Failed to execute cmdline: %s"), lpCmdLine);
		xfree(lpCmdLine);
	}
	
	return ERROR_SUCCESS;
}