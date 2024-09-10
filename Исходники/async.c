VOID
WSAAPI
WsAsyncGetHost(IN HANDLE TaskHandle,
               IN DWORD Operation,
               IN HWND hWnd,
               IN UINT wMsg,
               IN CHAR FAR *ByWhat,
               IN INT Length,
               IN INT Type,
               IN CHAR FAR *Buffer,
               IN INT BufferLength)
{
    PHOSTENT Hostent;
    SIZE_T BufferSize = 0;
    LPARAM lParam;
    INT ErrorCode = 0;

    /* Check the operaiton */
    if (Operation == WsAsyncGetHostByAddr)
    {
        /* Call the API */
        Hostent = gethostbyaddr(ByWhat, Length, Type);
    }
    else
    {
        /* Call the API */
        Hostent = gethostbyname(ByWhat);
    }

    /* Make sure we got one */
    if (!Hostent) ErrorCode = GetLastError();

    /* Acquire the lock */
    WsAsyncLock();

    /* Check if this task got cancelled */
    if (TaskHandle == WsAsyncCancelledTaskHandle)
    {
        /* Return */
        WsAsyncUnlock();
        return;
    }

    /* If we got a Servent back, copy it */
    if (Hostent)
    {
        /* Copy it into the buffer */
        BufferSize = CopyHostentToBuffer(Buffer, BufferLength, Hostent);

        /* Check if we had enough space */
        if (BufferSize > (DWORD)BufferLength)
        {
            /* Not enough */
            ErrorCode = WSAENOBUFS;
        }
        else
        {
            /* Perfect */
            ErrorCode = NO_ERROR;
        }
    }

    /* Not processing anyomre */
    WsAsyncCurrentTaskHandle = NULL;

    /* Release the lock */
    WsAsyncUnlock();

    /* Make the messed-up lParam reply */
    lParam = WSAMAKEASYNCREPLY(BufferSize, ErrorCode);

    /* Sent it through the Upcall API */
    WPUPostMessage(hWnd, wMsg, (WPARAM)TaskHandle, lParam);
}