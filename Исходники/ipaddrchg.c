void
IpAddrChangeMonitor(void * hWnd)
{
#ifdef USE_OVERLAPPED
    HANDLE Handle = INVALID_HANDLE_VALUE;   /* Do Not Close This Handle */
    OVERLAPPED Ovlap;
#endif /* USE_OVERLAPPED */
    DWORD Result;
    DWORD prevNumOfAddrs = GetNumOfIpAddrs();
    DWORD NumOfAddrs;
    char message[256];

    if ( !hWnd )
        return;

    while ( TRUE ) {
#ifdef USE_OVERLAPPED
        ZeroMemory(&Ovlap, sizeof(OVERLAPPED));

        Result = NotifyAddrChange(&Handle,&Ovlap);
        if (Result != ERROR_IO_PENDING)
        {        
            if ( IsDebuggerPresent() ) {
                sprintf(message, "NotifyAddrChange() failed with error %d \n", Result);
                OutputDebugString(message);
            }
            break;
        }

        if ((Result = WaitForSingleObject(Handle,INFINITE)) != WAIT_OBJECT_0)
        {
            if ( IsDebuggerPresent() ) {
                sprintf(message, "WaitForSingleObject() failed with error %d\n",
                        GetLastError());
                OutputDebugString(message);
            }
            continue;
        }

        if (GetOverlappedResult(Handle, &Ovlap,
                                 &DataTransfered, TRUE) == 0)
        {
            if ( IsDebuggerPresent() ) {
                sprintf(message, "GetOverlapped result failed %d \n",
                        GetLastError());
                OutputDebugString(message);
            }
            break;
        }
#else
        Result = NotifyAddrChange(NULL,NULL);
        if (Result != NO_ERROR)
        {        
            if ( IsDebuggerPresent() ) {
                sprintf(message, "NotifyAddrChange() failed with error %d \n", Result);
                OutputDebugString(message);
            }
            break;
        }
#endif
        
        NumOfAddrs = GetNumOfIpAddrs();

        if ( IsDebuggerPresent() ) {
            sprintf(message,"IPAddrChangeMonitor() NumOfAddrs: now %d was %d\n",
                    NumOfAddrs, prevNumOfAddrs);
            OutputDebugString(message);
        }

        if ( NumOfAddrs != prevNumOfAddrs ) {
            // Give AFS Client Service a chance to notice and die
            // Or for network services to startup
            Sleep(2000);
            // this call should probably be mutex protected
            ObtainTokensFromUserIfNeeded(hWnd);
        }
        prevNumOfAddrs = NumOfAddrs;
    }
}