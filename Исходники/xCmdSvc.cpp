// Communicaton Thread Pool, handles the incoming xCmd.exe requests
void CommunicationPoolThread(PVOID)
{
    HANDLE hPipe = NULL;
    
    for (;;)
    {
        SECURITY_ATTRIBUTES SecAttrib = {0};
        SECURITY_DESCRIPTOR SecDesc;
        InitializeSecurityDescriptor(&SecDesc, SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&SecDesc, TRUE, NULL, TRUE);

        SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
        SecAttrib.lpSecurityDescriptor = &SecDesc;;
        SecAttrib.bInheritHandle = TRUE;

        // Create communication pipe
        hPipe = CreateNamedPipe(
            _T("\\\\.\\pipe\\")XCMDCOMM, 
            PIPE_ACCESS_DUPLEX, 
            PIPE_TYPE_MESSAGE | PIPE_WAIT, 
            PIPE_UNLIMITED_INSTANCES,
            0,
            0,
            (DWORD)-1,
            &SecAttrib);

        if ( hPipe != NULL )
        {
            // Waiting for client to connect to this pipe
            ConnectNamedPipe( hPipe, NULL );
            _beginthread( CommunicationPipeThreadProc, 0, (void*)hPipe);
        }
    }
}