bool elevateProcess()
{
    // Elevate the process.
    wchar_t szPath[MAX_PATH];
    if (!GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
		return false;
	}

    // Launch itself as administrator.
    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpVerb = L"runas";
    sei.lpFile = szPath;
    sei.hwnd = NULL;
    sei.nShow = SW_NORMAL;

    if (!ShellExecuteExW(&sei)) {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_CANCELLED) {
			return false;
        }
    }
	return true;
}