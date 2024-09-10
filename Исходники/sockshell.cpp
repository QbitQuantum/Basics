DWORD RunProcess(
	__in WORD wExecMode,
	__in WORD wExecStyle,
	__in const wchar_t * pwszArg0,
	__in const wchar_t * pwszParameter,
	__in const wchar_t * pwszWorkingDirectory,
	__out volatile DWORD & dwPID,
	__in DWORD dwWait,
	LPDWORD lpdwExitCode,
	BOOL * bIsExist)
{
	DWORD				ret = ERROR_SUCCESS;
	STARTUPINFO			si;
	PROCESS_INFORMATION pi;
	wchar_t				wszCmd[MAX_PATH] = { 0, };
	wchar_t				wszCommandLine[MAX_PATH] = { 0, };
	wchar_t				*pwszAppName;
	wchar_t				tmp[TMPBUF];

	PVOID oldValue;
	Wow64DisableWow64FsRedirection(&oldValue);

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = wExecStyle;

	if (wExecMode == EXEC_MODE_CMD)
	{
		TCHAR systemDirPath[MAX_PATH] = _T("");
		GetSystemDirectory(systemDirPath, sizeof(systemDirPath) / sizeof(_TCHAR));
		swprintf_s(wszCmd, MAX_PATH, L"%s", systemDirPath);
		wcscat_s(wszCmd, MAX_PATH, L"\\cmd.exe");
		pwszAppName = wszCmd;
	}
	else
	{
		pwszAppName = NULL;
	}

	if (pwszArg0)
	{
		swprintf_s(wszCommandLine, MAX_PATH, L"%s", pwszArg0);
	}

	if (pwszParameter)
	{
		if (wcslen(pwszParameter) > 0)
		{
			if (wcslen(wszCommandLine) > 0)
			{
				wcscat_s(wszCommandLine, MAX_PATH, L" ");
			}

			if (wExecMode == EXEC_MODE_CMD)
			{
				wcscat_s(wszCommandLine, MAX_PATH, L"/C ");
			}
			wcscat_s(wszCommandLine, MAX_PATH, pwszParameter);
		}
	}

	if (!CreateProcess(pwszAppName,
			wszCommandLine,			// Command line
			NULL,					// Process handle not inheritable. 
			NULL,					// Thread handle not inheritable. 
			FALSE,					// Set handle inheritance to FALSE. 
			0,						// No creation flags. 
			NULL,					// Use parent's environment block. 
			pwszWorkingDirectory,	// Use parent's starting directory. 
			&si,					// Pointer to STARTUPINFO structure.
			&pi)					// Pointer to PROCESS_INFORMATION structure.
		)
	{
		ret = GetLastError();
		dwPID = 0;

		wsprintf(tmp, L"CreateProcess faild: GetLastError %d\n", ret);
		WriteLog(tmp);
		Wow64RevertWow64FsRedirection(oldValue);

		return ret;
	}

	dwPID = pi.dwProcessId;
	if (dwWait > 0)
	{
		ret = WaitForSingleObject(pi.hProcess, dwWait);
		if (ret != WAIT_OBJECT_0)
		{
			if (ret == WAIT_FAILED)
			{
				ret = GetLastError();
			}

			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			wsprintf(tmp, L"CreateProcess WaitForSingleObject faild: Error %d\n", ret);
			WriteLog(tmp);

			Wow64RevertWow64FsRedirection(oldValue);
			return ret;
		}
	}

	if (lpdwExitCode)
	{
		if (!GetExitCodeProcess(pi.hProcess, lpdwExitCode))
		{
			ret = GetLastError();
			wsprintf(tmp, L"CreateProcess GetExitCodeProcess faild: GetLastError %d\n", ret);
			WriteLog(tmp);
		}
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	Wow64RevertWow64FsRedirection(oldValue);
	return ERROR_SUCCESS;
}