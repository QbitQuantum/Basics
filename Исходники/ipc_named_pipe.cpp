BOOL
IpcCreateNamedPipe(IN LPCWSTR ObjectName,
                   IN BOOL FirstInstance,
                   IN DWORD OutBufferSize,
                   IN DWORD InBufferSize,
                   IN DWORD DefaultTimeout,
                   OUT PNAMED_PIPE NamedPipe)
{
    DWORD OpenMode;
    DWORD PipeMode;
    PSID sid;
    SECURITY_DESCRIPTOR sd = { 0 };
    SECURITY_ATTRIBUTES sa = { 0 };

    IpcMakePipeName(NamedPipe->ObjectName,
                    0x100,
                    ObjectName);

    NamedPipe->EventHandle = CreateEventW(NULL,
                                          TRUE,
                                          TRUE,
                                          NULL);

    if (!NamedPipe->EventHandle)
    {
        return FALSE;
    }

    OpenMode = PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED;
    OpenMode |= FirstInstance ? FILE_FLAG_FIRST_PIPE_INSTANCE : 0;

    PipeMode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE;
    PipeMode |= PIPE_WAIT;
    PipeMode |= PIPE_REJECT_REMOTE_CLIENTS;

    if (!ScCreateSecurityAttributes(&sa, &sd, &sid))
    {
        NamedPipe->ObjectHandle = 0;
        CloseHandle(NamedPipe->EventHandle);
        NamedPipe->EventHandle = 0;
        return FALSE;
    }

    NamedPipe->ObjectHandle = CreateNamedPipeW(NamedPipe->ObjectName,
                                               OpenMode,
                                               PipeMode,
                                               PIPE_UNLIMITED_INSTANCES,
                                               OutBufferSize,
                                               InBufferSize,
                                               DefaultTimeout,
                                               &sa);

    ScDestroySecurityAttributes(sid);

    if (NamedPipe->ObjectHandle == INVALID_HANDLE_VALUE ||
        GetLastError() == ERROR_ACCESS_DENIED)
    {
        NamedPipe->ObjectHandle = 0;
        CloseHandle(NamedPipe->EventHandle);
        NamedPipe->EventHandle = 0;
        return FALSE;
    }

    return TRUE;
}