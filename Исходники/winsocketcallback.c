DWORD WINAPI WorkerThreadCallback(LPVOID lpParameter)
{
    DWORD Flags;
    LPSOCKET_INFORMATION_CALLBACK SocketInfo;
    WSAEVENT EventArray[1];
    DWORD Index;
    DWORD RecvBytes;

    // Save the accept event in the event array
    EventArray[0] = (WSAEVENT) lpParameter;
 
    while(TRUE)
    {
        // Wait for accept() to signal an event and also process WorkerRoutine() returns
        while(TRUE)
        {
            Index = WSAWaitForMultipleEvents(1, EventArray, FALSE, WSA_INFINITE, TRUE);
            if (Index == WSA_WAIT_FAILED)
            {
                printf("WSAWaitForMultipleEvents() failed with error %d\n", WSAGetLastError());
                return FALSE;
            }
            else
                printf("WSAWaitForMultipleEvents() should be OK!\n");
 
            if (Index != WAIT_IO_COMPLETION)
            {
                // An accept() call event is ready - break the wait loop
                break;
            }
        }
 
		/* The WSAResetEvent function resets the state 
		 * of the specified event object to nonsignaled. */
        WSAResetEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
        // Create a socket information structure to associate with the accepted socket
        if ((SocketInfo = (LPSOCKET_INFORMATION_CALLBACK) GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION_CALLBACK))) == NULL)
        {
            printf("GlobalAlloc() failed with error %d\n", GetLastError());
            return FALSE;
        }
        else
            printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");
 
        // Fill in the details of our accepted socket
        SocketInfo->Socket = AcceptSocketCallback;
        ZeroMemory(&(SocketInfo->Overlapped), sizeof(WSAOVERLAPPED));
        SocketInfo->BytesSEND = 0;
        SocketInfo->BytesRECV = 0;
        SocketInfo->DataBuf.len = DEFAULT_BUFLEN;
        SocketInfo->DataBuf.buf = SocketInfo->Buffer;
 

        Flags = 0;
        if (WSARecv(SocketInfo->Socket, 
			      &(SocketInfo->DataBuf), 
				  1, 
				  &RecvBytes, 
				  &Flags,
                  &(SocketInfo->Overlapped), 
				  WorkerRoutineCallback) == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSA_IO_PENDING)
            {
                printf("WSARecv() failed with error %d\n", WSAGetLastError());
                return FALSE;
            }
        }
        else
            printf("WSARecv() is OK!\n");

        printf("Socket %d got connected...\n", AcceptSocketCallback);
    }
    return TRUE;
}