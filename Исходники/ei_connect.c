static int initWinSock(void)
{
    WORD wVersionRequested;  
    WSADATA wsaData; 
    int i; 

    static LONG volatile initialized = 0;
    
    wVersionRequested = MAKEWORD(1, 1); 
    if (InterlockedCompareExchange((LPLONG) &initialized,1L,0L) == 0L) {
	/* FIXME not terminate, just a message?! */
	if ((i = WSAStartup(wVersionRequested, &wsaData))) {
	    EI_TRACE_ERR1("ei_connect_init",
			  "ERROR: can't initialize windows sockets: %d",i);
	    initialized = 2L;
	    return 0;
	}
	
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) { 
	    EI_TRACE_ERR0("initWinSock","ERROR: this version of windows "
			  "sockets not supported");
	    WSACleanup(); 
	    initialized = 2L;
	    return 0;
	}
	initialized = 3L;
    } else while (initialized < 2) {
	SwitchToThread();
    }
    return (int) (initialized - 2);
}