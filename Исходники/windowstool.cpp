static BOOL WINAPI initializeWTSUnRegisterSessionNotification(HWND hWnd)
{
    HMODULE hModule = GetModuleHandle(_T("wtsapi32.dll"));
    if (!hModule) {
        return FALSE;
    }
    WTSUnRegisterSessionNotification_t proc =
        reinterpret_cast<WTSUnRegisterSessionNotification_t>(
            GetProcAddress(hModule, "WTSUnRegisterSessionNotification"));
    if (proc) {
        wtsUnRegisterSessionNotification = proc;
        return wtsUnRegisterSessionNotification(hWnd);
    } else {
        return 0;
    }
}