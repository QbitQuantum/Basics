/*************************************************************************
* SHCreateFromDesktop			[BROWSEUI.106]
* parameter is a FolderInfo
*/
BOOL WINAPI SHCreateFromDesktop(ExplorerCommandLineParseResults * parseResults)
{
    DbgPrint("SHCreateFromDesktop\n");

    IEThreadParamBlock * parameters = SHCreateIETHREADPARAM(0, 0, 0, 0);
    if (!parameters)
        return FALSE;

    PCWSTR strPath = NULL;
    if (parseResults->dwFlags & SH_EXPLORER_CMDLINE_FLAG_STRING)
    {
        if (parseResults->pidlPath)
        {
            WARN("strPath and pidlPath are both assigned. This shouldn't happen.\n");
        }

        strPath = parseResults->strPath;
    }

    parameters->dwFlags = parseResults->dwFlags;
    parameters->offset8 = parseResults->offsetC;

    LPITEMIDLIST pidl = parseResults->pidlPath ? ILClone(parseResults->pidlPath) : NULL;
    if (!pidl && parseResults->dwFlags & SH_EXPLORER_CMDLINE_FLAG_STRING)
    {
        if (parseResults->strPath && parseResults->strPath[0])
        {
            pidl = ILCreateFromPathW(parseResults->strPath);
        }
    }

    parameters->directoryPIDL = pidl;

    // Try to find the owner of the idlist, if we aren't running /SEPARATE
    HWND desktop = NULL;
    if (!(parseResults->dwFlags & SH_EXPLORER_CMDLINE_FLAG_SEPARATE))
        desktop = FindShellProxy(parameters->directoryPIDL);

    // If found, ask it to open the new window
    if (desktop)
    {
        DbgPrint("Found desktop hwnd=%p\n", desktop);

        DWORD dwProcessId;

        GetWindowThreadProcessId(desktop, &dwProcessId);
        AllowSetForegroundWindow(dwProcessId);

        HANDLE hShared = MakeSharedPacket(parameters, strPath, dwProcessId);
        if (hShared)
        {
            DbgPrint("Sending open message...\n");

            PostMessageW(desktop, WM_EXPLORER_OPEN_NEW_WINDOW, 0, (LPARAM) hShared);
        }

        SHDestroyIETHREADPARAM(parameters);
        return TRUE;
    }

    DbgPrint("Desktop not found or separate flag requested.\n");

    // Else, start our own message loop!
    HRESULT hr = CoInitialize(NULL);
    CProxyDesktop * proxy = CreateProxyDesktop(parameters);
    if (proxy)
    {
        LONG refCount;
        CComPtr<IUnknown> thread;
        if (SHCreateThreadRef(&refCount, &thread) >= 0)
        {
            SHSetInstanceExplorer(thread);
            if (strPath)
                parameters->directoryPIDL = ILCreateFromPath(strPath);
            SHOpenFolderWindow(parameters);
            parameters = NULL;
            thread.Release();
        }

        MSG Msg;
        while (GetMessageW(&Msg, 0, 0, 0) && refCount)
        {
            TranslateMessage(&Msg);
            DispatchMessageW(&Msg);
        }

        delete proxy;
    }

    if (SUCCEEDED(hr))
        CoUninitialize();

    SHDestroyIETHREADPARAM(parameters);

    return TRUE;
}