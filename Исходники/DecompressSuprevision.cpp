	bool WINAPI Supervisor::CreateDecompressInvoke(HWND hWnd,std::wstring img, LPWSTR latter)
	{
		WCHAR _7zCmd[MAX_UNC_PATH] = { 0 };
		//HWND m_hWnd = static_cast<HWND>(hWnd);
		GetModuleFileName(GetModuleHandle(nullptr), _7zCmd, MAX_UNC_PATH);
		(wcsrchr(_7zCmd, _T('\\')))[0] = 0;
		(wcsrchr(_7zCmd, _T('\\')))[0] = 0;
		wcscat_s(_7zCmd, L"\\7-zip\\7z.exe");
		if (!_waccess_s(_7zCmd, 0) == 0)
		{
			return false;
		}
		wcscat_s(_7zCmd, L" x ");
		wcscat_s(_7zCmd, img.c_str());
		wcscat_s(_7zCmd, L" -aoa -y -o");
		wcscat_s(_7zCmd, latter);
		wcscat_s(_7zCmd, L"\\");
		//_waccess_s()
		PROCESS_INFORMATION pi;
		STARTUPINFO sInfo;
		DWORD dwExitCode;
		ZeroMemory(&sInfo, sizeof(sInfo));
		sInfo.cb = sizeof(sInfo);
		sInfo.dwFlags = STARTF_USESHOWWINDOW;
		sInfo.wShowWindow = SW_HIDE;
		ZeroMemory(&pi, sizeof(pi));

		DWORD result = CreateProcess(NULL, _7zCmd, NULL, NULL, NULL, CREATE_NO_WINDOW, NULL, NULL, &sInfo, &pi);
		if (result == TRUE)
		{
			CloseHandle(pi.hThread);
			PostMessage(hWnd, Metro::METRO_MULTITHREAD_MSG, MET_POST_PID_ADD, pi.dwProcessId);
			WaitForSingleObject(pi.hProcess, INFINITE);
			PostMessage(hWnd, Metro::METRO_MULTITHREAD_MSG, MET_POST_PID_CLEAR, 0);
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			CloseHandle(pi.hProcess);
			if (dwExitCode != 0 &&dwExitCode!=1)
			{
				return false;
			}
			return true;
		}
		return false;
	}