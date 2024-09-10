//===========================================================================
SOCKET winSocketCreate () {
    SOCKET handle = WSASocketW(
        AF_UNSPEC,
        SOCK_STREAM,
        IPPROTO_TCP,
        NULL,
        0,
        WSA_FLAG_REGISTERED_IO
    );
    if (handle == INVALID_SOCKET) {
        logMsgError() << "WSASocket: " << WinError{};
        return INVALID_SOCKET;
    }

    int yes = 1;

    //DWORD bytes;
    //if (SOCKET_ERROR == WSAIoctl(
    //    handle,
    //    SIO_LOOPBACK_FAST_PATH,
    //    &yes, sizeof yes,
    //    nullptr, 0, // output buffer, buffer size
    //    &bytes,     // bytes returned
    //    nullptr,    // overlapped
    //    nullptr     // completion routine
    //)) {
    //    logMsgError() << "WSAIoctl(SIO_LOOPBACK_FAST_PATH): " << WinError{};
    //}

    if (SOCKET_ERROR == setsockopt(
        handle,
        SOL_SOCKET,
        TCP_NODELAY,
        (char *) &yes,
        sizeof(yes)
    )) {
        logMsgError() << "WSAIoctl(FIONBIO): " << WinError{};
    }

#ifdef SO_REUSE_UNICASTPORT
    if (SOCKET_ERROR == setsockopt(
        handle,
        SOL_SOCKET,
        SO_REUSE_UNICASTPORT,
        (char *) &yes,
        sizeof(yes)
    )) {
#endif        
        if (SOCKET_ERROR == setsockopt(
            handle, 
            SOL_SOCKET, 
            SO_PORT_SCALABILITY, 
            (char *) &yes, 
            sizeof(yes)
        )) {
            logMsgError() << "setsockopt(SO_PORT_SCALABILITY): " 
                << WinError{};
        }
#ifdef SO_REUSE_UNICASTPORT
    }
#endif

    return handle;
}