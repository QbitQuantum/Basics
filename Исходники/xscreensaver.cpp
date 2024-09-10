BOOL Execute(HWND hwnd, LPCTSTR program, LPCTSTR params)
{
    TCHAR szCmdLine[MAX_PATH];
    lstrcpy(szCmdLine, TEXT("\""));
    lstrcat(szCmdLine, program);
    lstrcat(szCmdLine, TEXT("\" "));
    lstrcat(szCmdLine, params);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    BOOL b = CreateProcess(NULL, szCmdLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (b)
    {
        WaitForInputIdle(pi.hProcess, 1500);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return TRUE;
    }
    return FALSE;
}