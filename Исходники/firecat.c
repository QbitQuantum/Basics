BOOL
doexec(
    SOCKET  ClientSocket
    )
{
    PSESSION_DATA   Session = CreateSession();
    SECURITY_ATTRIBUTES SecurityAttributes;
    DWORD ThreadId;
    HANDLE HandleArray[3];
	int i;

    SecurityAttributes.nLength = sizeof(SecurityAttributes);
    SecurityAttributes.lpSecurityDescriptor = NULL; // Use default ACL
    SecurityAttributes.bInheritHandle = FALSE; // No inheritance

    //
    // Store the client socket handle in the session structure so the thread
    // can get at it. This also signals that the session is connected.
    //
    Session->ClientSocket = ClientSocket;

    //
    // Create the session threads
    //
    Session->ReadShellThreadHandle = 
        CreateThread(&SecurityAttributes, 0,
                     (LPTHREAD_START_ROUTINE) SessionReadShellThreadFn, 
                     (LPVOID) Session, 0, &ThreadId);

    if (Session->ReadShellThreadHandle == NULL) {
        holler("Failed to create ReadShell session thread, error = %s", 
			itoa(GetLastError(), smbuff, 10), NULL, NULL, NULL, NULL, NULL);

        //
        // Reset the client pipe handle to indicate this session is disconnected
        //
        Session->ClientSocket = INVALID_SOCKET;
        return(FALSE);
    }

    Session->WriteShellThreadHandle = 
        CreateThread(&SecurityAttributes, 0, 
                     (LPTHREAD_START_ROUTINE) SessionWriteShellThreadFn, 
                     (LPVOID) Session, 0, &ThreadId);

    if (Session->WriteShellThreadHandle == NULL) {
        holler("Failed to create ReadShell session thread, error = %s", 
			itoa(GetLastError(), smbuff, 10), NULL, NULL, NULL, NULL, NULL);

        //
        // Reset the client pipe handle to indicate this session is disconnected
        //
        Session->ClientSocket = INVALID_SOCKET;

        TerminateThread(Session->WriteShellThreadHandle, 0);
        return(FALSE);
    }

    //
    // Wait for either thread or the shell process to finish
    //

    HandleArray[0] = Session->ReadShellThreadHandle;
    HandleArray[1] = Session->WriteShellThreadHandle;
    HandleArray[2] = Session->ProcessHandle;

	
    i = WaitForMultipleObjects(3, HandleArray, FALSE, 0xffffffff);
    
	
	switch (i) {
      case WAIT_OBJECT_0 + 0:
        TerminateThread(Session->WriteShellThreadHandle, 0);
        TerminateProcess(Session->ProcessHandle, 1);
        break;

      case WAIT_OBJECT_0 + 1:
        TerminateThread(Session->ReadShellThreadHandle, 0);
        TerminateProcess(Session->ProcessHandle, 1);
        break;
      case WAIT_OBJECT_0 + 2:
        TerminateThread(Session->WriteShellThreadHandle, 0);
        TerminateThread(Session->ReadShellThreadHandle, 0);
        break;
 
	  default:
        holler("WaitForMultipleObjects error: %s", 
			itoa(GetLastError(), smbuff, 10), NULL, NULL, NULL, NULL, NULL);

        break;
    }


    // Close my handles to the threads, the shell process, and the shell pipes
	shutdown(Session->ClientSocket, SD_BOTH);
  	closesocket(Session->ClientSocket);
	
	DisconnectNamedPipe(Session->ReadPipeHandle);
    CloseHandle(Session->ReadPipeHandle);

	DisconnectNamedPipe(Session->WritePipeHandle);
    CloseHandle(Session->WritePipeHandle);


    CloseHandle(Session->ReadShellThreadHandle);
    CloseHandle(Session->WriteShellThreadHandle);

    CloseHandle(Session->ProcessHandle);
 
    free(Session);

    return(TRUE);
}