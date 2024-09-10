    static int WSAAPI WSACleanup_hook()
    {
        // don't let the application murder our sockets with a mismatched WSACleanup() call
        if(syshooks.m_WSARefCount == 1)
        {
            RDCLOG("WSACleanup called with (to the application) no WSAStartup! Ignoring.");
            SetLastError(WSANOTINITIALISED);
            return SOCKET_ERROR;
        }

        // decrement refcount and call the real thing
        syshooks.m_WSARefCount--;
        return syshooks.WSACleanup()();
    }