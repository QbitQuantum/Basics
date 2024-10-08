	bool ResolveSupervisor::FixUSBDeviceBoot(LPCWSTR DeviceLetter)
	{
		TCHAR BCDPath[MAX_UNC_PATH] = { 0 };
		PROCESS_INFORMATION pi;
		STARTUPINFO sInfo;
		DWORD dwExitCode;
		ZeroMemory(&sInfo, sizeof(sInfo));
		sInfo.cb = sizeof(sInfo);
		sInfo.dwFlags = STARTF_USESHOWWINDOW;
		sInfo.wShowWindow = SW_HIDE;
		ZeroMemory(&pi, sizeof(pi));
		GetModuleFileName(NULL, BCDPath, MAX_UNC_PATH);
		(wcsrchr(BCDPath, _T('\\')))[0] = 0;
		(wcsrchr(BCDPath, _T('\\')))[0] = 0;
		wcscat_s(BCDPath, L"\\BCDBoot\\bootsect.exe");
		if (!_waccess_s(BCDPath, 0) == 0)
		{
			return false;
		}
		wcscat_s(BCDPath, L" /NT60 ");
		wcscat_s(BCDPath, DeviceLetter);
		DWORD result = CreateProcessW(NULL, BCDPath, NULL, NULL, NULL, CREATE_NO_WINDOW, NULL, NULL, &sInfo, &pi);
		if (result == TRUE)
		{
			CloseHandle(pi.hThread);
			if (WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, INFINITE))
			{
				TerminateProcess(pi.hProcess, 11);
			}
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			CloseHandle(pi.hProcess);
			if (dwExitCode != 0)
			{
				return false;
			}
			return true;
		}
		return false;
	}