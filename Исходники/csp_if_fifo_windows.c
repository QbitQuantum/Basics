unsigned WINAPI pipe_listener(void *parameters) {
    while(1) {
        HANDLE pipe =  CreateNamedPipe(
                        pipeName,
                        PIPE_ACCESS_DUPLEX,
                        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                        PIPE_UNLIMITED_INSTANCES,
                        PIPE_BUFSIZE,
                        PIPE_BUFSIZE,
                        0,
                        NULL);
        BOOL clientConnected;
        if( pipe == INVALID_HANDLE_VALUE ) {
            printf("Error creating named pipe. Code %lu\n", GetLastError());
            return -1;
        }

        // True if client connects *after* server called ConnectNamedPipe 
        // or *between* CreateNamedPipe and ConnectNamedPipe
        clientConnected = 
            ConnectNamedPipe(pipe, NULL) ? TRUE : GetLastError()==ERROR_PIPE_CONNECTED;
        printf("Client connected!\n");

        if( !clientConnected ) {
            printf("Failure while listening for clients. Code %lu\n", GetLastError());
            CloseHandle(pipe);
            return -1;
        }
        printf("Create client thread\n");
        _beginthreadex(NULL, 0, fifo_rx, (PVOID)pipe, 0, 0);    
    }

    return 0;
}