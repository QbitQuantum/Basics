StatsServerMessage* NTServerMessage::connectStatsChannel(const char* name)
{
    HANDLE hPipe;
    int nIndex = 0;
    int nTrialCount = 5;
    for (nIndex = 0; nIndex < nTrialCount; ++nIndex)
    {
        DWORD dwAccess = GENERIC_READ | GENERIC_WRITE;
        DWORD dwShared = FILE_SHARE_READ | FILE_SHARE_WRITE;
        DWORD dwFlags = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED;
        hPipe = CreateFile(name,
                           dwAccess,
                           dwShared,
                           NULL,        // Security Attribute
                           OPEN_EXISTING,
                           dwFlags, // File Attribute
                           NULL);
        if (hPipe != INVALID_HANDLE_VALUE)
            break;              // Got Connected successfully
        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            // Unable to connect.
            return 0;
        }
        int waitTime = 2000;    // 2 seconds
        if (!WaitNamedPipe(name, waitTime))
        {
            // Instance of pipe is not available
            return 0;
        }
        // continue
    }
    if (hPipe == INVALID_HANDLE_VALUE)
        return 0;
    DWORD dwPipeMode = PIPE_READMODE_MESSAGE;
    BOOL fSuccess = SetNamedPipeHandleState(hPipe,
                                            &dwPipeMode,
                                            NULL, // lpMaxCollectionCount
                                            NULL);// lpCollectDataTimeout
    if (!fSuccess)
    {
        // Unable to setup pipe message option
        CloseHandle(hPipe);
        return 0;
    }
    StatsServerMessage* statsMsgChannel = 0;
    statsMsgChannel = new StatsServerMessage(hPipe);
    return statsMsgChannel;
}