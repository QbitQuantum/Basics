//DESCRIPTION:
// This function creates the completion port and the requested number of threads.
// If threads creation fails, the successfully created threads' handles are closed before returning.
//
//INPUT:
// nbOfThreads - the number of threads to create
// pWorkerThreads - the ouput pointer to the thread handle array
// pAsync_config - the config struct
//
//OUTPUT:
// TRUE for success
// FALSE for error
//
BOOL AsyncFuzzer::InitializeThreadsAndCompletionPort()
{
    BOOL bResult = FALSE;

    hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)NULL, 0);
    if(hIocp) {
        // Associate the device handle to iocp
        bResult = (NULL!=CreateIoCompletionPort(hDev, hIocp, 0, 0));
        if(bResult) {
            // Configure io completion port
            bResult = SetFileCompletionNotificationModes(hDev, FILE_SKIP_COMPLETION_PORT_ON_SUCCESS);
            if(bResult) {
                bResult = CreateThreads();
                if(!bResult){
                    TPRINT(VERBOSITY_ERROR, _T("Failed to create worker threads\n"));
                }
            }
            else {
                TPRINT(VERBOSITY_ERROR, _T("Failed to configure iocompletion port with error %#.8x\n"), GetLastError());
            }
        }
        else {
            TPRINT(VERBOSITY_ERROR, _T("Failed to associate device with iocompletion port with error %#.8x\n"), GetLastError());
        }
    }
    else {
        TPRINT(VERBOSITY_ERROR, _T("Failed to create I/O completion port with error %#.8x\n"), GetLastError());
    }
    return bResult;
}