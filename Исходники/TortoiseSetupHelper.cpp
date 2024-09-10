static BOOL CALLBACK EnumWindowsCallback(HWND windowHandle, LPARAM lParam)
{
    DWORD pid;
    GetWindowThreadProcessId(windowHandle, &pid);
    if (pid == lParam)
    {
        // This window belongs to the process
        if (!windowTitle.empty())
            return TRUE;
        TCHAR text[256];
        GetWindowText(windowHandle, text, sizeof(text));
        if ((GetWindowLong(windowHandle, GWL_STYLE) & WS_VISIBLE))
        {
            windowTitle = text;
            return FALSE;
        }
    }
    return TRUE;
}