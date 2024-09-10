BOOL NamedPipeInputFuzzer::Init()
{
    BOOL bResult=FALSE;

    dibf_pipe = CreateNamedPipe(_T("\\\\.\\pipe\\dibf_pipe"),
                                PIPE_ACCESS_INBOUND,
                                PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT|PIPE_REJECT_REMOTE_CLIENTS,
                                1,
                                MAX_BUFSIZE/2,
                                MAX_BUFSIZE/2,
                                0,
                                NULL);
    if(dibf_pipe!=INVALID_HANDLE_VALUE) {
        TPRINT(VERBOSITY_DEFAULT, _T("Named pipe created, waiting for connection...\n"));
        if(ConnectNamedPipe(dibf_pipe, NULL)?TRUE:(GetLastError()==ERROR_PIPE_CONNECTED)) {
            TPRINT(VERBOSITY_DEFAULT, _T("Fuzzing client connected to named pipe\n"));
            inputThread = CreateThread(NULL, 0, FuzzInputProc, this, 0, NULL);
            if(inputThread) {
                bResult = TRUE;
            }
            else {
                TPRINT(VERBOSITY_ERROR, _T("Failed to create fuzz input thread with error %#.8x\n"), GetLastError());
            }
        }
    }
    return bResult;
}