//===========================================================================
void NtInitialize () {
    // ensure initialization only occurs once
    if (s_running)
        return;
    s_running = true;

    // create a cleanup event
    s_waitEvent = CreateEvent(
                      (LPSECURITY_ATTRIBUTES) 0,
                      true,           // manual reset
                      false,          // initial state off
                      (LPCTSTR) nil   // name
                  );
    if (!s_waitEvent)
        ErrorAssert(__LINE__, __FILE__, "CreateEvent %#x", GetLastError());

    // create IO completion port
    if (0 == (s_ioPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0)))
        ErrorAssert(__LINE__, __FILE__, "CreateIoCompletionPort %#x", GetLastError());

    // calculate number of IO worker threads to create
    if (!s_pageSizeMask) {
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        s_pageSizeMask = si.dwPageSize - 1;

        // Set worker thread count
        s_ioThreadCount = si.dwNumberOfProcessors * 2;
        if (s_ioThreadCount > kMaxWorkerThreads) {
            s_ioThreadCount = kMaxWorkerThreads;
            LogMsg(kLogError, "kMaxWorkerThreads too small!");
        }
    }

    // create IO worker threads
    for (long thread = 0; thread < s_ioThreadCount; thread++) {
        s_ioThreadHandles[thread] = (HANDLE) AsyncThreadCreate(
                                        NtWorkerThreadProc,
                                        (void *) thread,
                                        L"NtWorkerThread"
                                    );
    }

    INtSocketInitialize();
}