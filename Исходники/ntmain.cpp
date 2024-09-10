HANDLE admin_connect(void)
{
    HANDLE hMsgPipe = INVALID_HANDLE_VALUE;

    // Name of the pipe the admin client creates
    const int MAX_PIPE_BUF_SIZE = 1024;
    char pipeName[MAX_PIPE_BUF_SIZE];
    sprintf(pipeName, "\\\\.\\pipe\\iWSAdmin-%s", unique_name);

    for (;;) {
        // Attempt to connect to the admin client
        hMsgPipe = CreateFile(pipeName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                              0, NULL);
        if (hMsgPipe != INVALID_HANDLE_VALUE)
            break;
        if (GetLastError() != ERROR_PIPE_BUSY)
            break;

        // Wait 20 seconds to establish a connection
        if (!WaitNamedPipe(pipeName, 20000))
            break;
    }

    if (hMsgPipe != INVALID_HANDLE_VALUE) {
        DWORD dwMode = PIPE_READMODE_MESSAGE;
        BOOL fSuccess = SetNamedPipeHandleState(hMsgPipe, &dwMode, NULL, NULL);
        if (!fSuccess) {
            CloseHandle(hMsgPipe);
            hMsgPipe = INVALID_HANDLE_VALUE;
        }
    }

    return hMsgPipe;
}