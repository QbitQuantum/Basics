/*
    This function is the entry point for the AsyncSelect Accept implementation.
*/
void AsyncSelectAcceptMain()
{
    PSOCK_INFO pSockInfo;
    int rc;
    MSG msg;
     
    printf("Entering AsyncSelectAcceptMain()\n");

    // create a dummy hidden window to receive the async select messages.
    g_AcceptContext.hAcceptWindow = CreateAcceptWindow();
    if (g_AcceptContext.hAcceptWindow == NULL)
    {
        printf("Error in creating the accept window.\n");
        goto CLEANUP;
    }

    // Set for all the listening sockets to be signalled on FD_ACCEPT event.
    for(pSockInfo = g_AcceptContext.pSockList; pSockInfo != NULL;
                                               pSockInfo = pSockInfo->next)
    {
        // request asynchronous notifications for the FD_ACCEPT and FD_CLOSE
        // events to be sent to the hAcceptWindow for this sock.
        rc = WSAAsyncSelect(pSockInfo->sock,
                            g_AcceptContext.hAcceptWindow, 
                            WM_USER_ASYNCSELECT_MSG,
                            FD_ACCEPT | FD_CLOSE);
        if (rc == SOCKET_ERROR)
        {
            printf("ERROR: WSAAsyncSelect failed for sock %d. Error = %d\n", 
                                    pSockInfo->sock, WSAGetLastError());
            continue;                                                  
        }
    }

    // Main message loop to process messages to the Accept Window.
    // This will indirectly call MainWndProc which will in turn call
    // ProcessAsyncSelectMessage.
    while (GetMessage(&msg, (HWND) NULL, 0, 0)) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 

   
CLEANUP:        

    printf("Exiting AsyncSelectAcceptMain()\n");
    return ;
}