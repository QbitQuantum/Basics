DWORD WINAPI CaptureThread(HANDLE hDllMainThread)
{
    bool bSuccess = false;

    //wait for dll initialization to finish before executing any initialization code
    if(hDllMainThread)
    {
        WaitForSingleObject(hDllMainThread, INFINITE);
        CloseHandle(hDllMainThread);
    }

    TCHAR lpLogPath[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, lpLogPath);
    wcscat_s(lpLogPath, MAX_PATH, TEXT("\\OBS\\pluginData\\captureHookLog.txt"));

    dummyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if(!logOutput.is_open())
        logOutput.open(lpLogPath, ios_base::in | ios_base::out | ios_base::trunc, _SH_DENYNO);

    wstringstream str;
    str << OBS_KEEPALIVE_EVENT << UINT(GetCurrentProcessId());
    strKeepAlive = str.str();

    logOutput << CurrentDateTimeString() << "we're booting up: " << endl;

    InitializeCriticalSection(&d3d9EndMutex);
    InitializeCriticalSection(&glMutex);

    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.hInstance = hinstMain;
    wc.lpszClassName = SENDER_WINDOWCLASS;
    wc.lpfnWndProc = (WNDPROC)DefWindowProc;

    DWORD procID = GetCurrentProcessId();

    wstringstream strRestartEvent, strEndEvent, strReadyEvent, strExitEvent, strInfoMemory;
    strRestartEvent << RESTART_CAPTURE_EVENT << procID;
    strEndEvent     << END_CAPTURE_EVENT     << procID;
    strReadyEvent   << CAPTURE_READY_EVENT   << procID;
    strExitEvent    << APP_EXIT_EVENT        << procID;
    strInfoMemory   << INFO_MEMORY           << procID;

    hSignalRestart  = GetEvent(strRestartEvent.str().c_str());
    hSignalEnd      = GetEvent(strEndEvent.str().c_str());
    hSignalReady    = GetEvent(strReadyEvent.str().c_str());
    hSignalExit     = GetEvent(strExitEvent.str().c_str());

    hInfoFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(CaptureInfo), strInfoMemory.str().c_str());
    if(!hInfoFileMap)
    {
        logOutput << CurrentTimeString() << "CaptureThread: could not info file mapping" << endl;
        return 0;
    }

    infoMem = (CaptureInfo*)MapViewOfFile(hInfoFileMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CaptureInfo));
    if(!infoMem)
    {
        logOutput << CurrentTimeString() << "CaptureThread: could not map view of info shared memory" << endl;
        CloseHandle(hInfoFileMap);
        hInfoFileMap = NULL;
        return 0;
    }

    hwndOBS = FindWindow(OBS_WINDOW_CLASS, NULL);
    if(!hwndOBS)
    {
        logOutput << CurrentTimeString() << "CaptureThread: could not find main application window?  wtf?  seriously?" << endl;
        return 0;
    }

    if (RegisterClass(&wc)) {
        hwndSender = CreateWindow(SENDER_WINDOWCLASS, NULL, 0, 0, 0, 0, 0, NULL, 0, hinstMain, 0);
        if (hwndSender) {
            textureMutexes[0] = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXTURE_MUTEX1);
            if (textureMutexes[0]) {
                textureMutexes[1] = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXTURE_MUTEX2);
                if (textureMutexes[1]) {
                    while(!AttemptToHookSomething())
                        Sleep(50);

                    logOutput << CurrentTimeString() << "(half life scientist) everything..  seems to be in order" << endl;

                    MSG msg;
                    while (MsgWaitForMultipleObjects(1, &dummyEvent, FALSE, 3000, QS_ALLPOSTMESSAGE) != WAIT_ABANDONED_0) {
                    //while (1) {
                        AttemptToHookSomething();

                        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }

                        //Sleep(50);
                    }

                    CloseHandle(textureMutexes[1]);
                    textureMutexes[1] = NULL;
                } else {
                    logOutput << CurrentTimeString() << "could not open texture mutex 2" << endl;
                }

                CloseHandle(textureMutexes[0]);
                textureMutexes[0] = NULL;
            } else {
                logOutput << CurrentTimeString() << "could not open texture mutex 1" << endl;
            }

            DestroyWindow(hwndSender);
        } else {
            logOutput << CurrentTimeString() << "could not create sender window" << endl;
        }
    }

    logOutput << CurrentTimeString() << "exit out of the main thread loop somehow" << endl;

    return 0;
}