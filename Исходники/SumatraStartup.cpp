static HWND FindPrevInstWindow(HANDLE *hMutex)
{
    // create a unique identifier for this executable
    // (allows independent side-by-side installations)
    ScopedMem<WCHAR> exePath(GetExePath());
    str::ToLower(exePath);
    uint32_t hash = MurmurHash2(exePath.Get(), str::Len(exePath) * sizeof(WCHAR));
    ScopedMem<WCHAR> mapId(str::Format(L"SumatraPDF-%08x", hash));

    int retriesLeft = 3;
Retry:
    // use a memory mapping containing a process id as mutex
    HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(DWORD), mapId);
    if (!hMap)
        goto Error;
    bool hasPrevInst = GetLastError() == ERROR_ALREADY_EXISTS;
    DWORD *procId = (DWORD *)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(DWORD));
    if (!procId) {
        CloseHandle(hMap);
        goto Error;
    }
    if (!hasPrevInst) {
        *procId = GetCurrentProcessId();
        UnmapViewOfFile(procId);
        *hMutex = hMap;
        return NULL;
    }

    // if the mapping already exists, find one window belonging to the original process
    DWORD prevProcId = *procId;
    UnmapViewOfFile(procId);
    CloseHandle(hMap);
    HWND hwnd = NULL;
    while ((hwnd = FindWindowEx(HWND_DESKTOP, hwnd, FRAME_CLASS_NAME, NULL)) != NULL) {
        DWORD wndProcId;
        GetWindowThreadProcessId(hwnd, &wndProcId);
        if (wndProcId == prevProcId) {
            AllowSetForegroundWindow(prevProcId);
            return hwnd;
        }
    }

    // fall through
Error:
    if (--retriesLeft < 0)
        return NULL;
    Sleep(100);
    goto Retry;
}