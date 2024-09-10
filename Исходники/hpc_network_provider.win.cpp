static void load_socket_functions()
{
    if (s_lpfnGetAcceptExSockaddrs != NULL)
        return;

    socket_t s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        dassert(false, "create Socket Failed, err = %d", ::GetLastError());
    }

    GUID GuidAcceptEx = WSAID_ACCEPTEX;
    GUID GuidConnectEx = WSAID_CONNECTEX;
    GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
    DWORD dwBytes;

    // Load the AcceptEx function into memory using WSAIoctl.
    // The WSAIoctl function is an extension of the ioctlsocket()
    // function that can use overlapped I/O. The function's 3rd
    // through 6th parameters are input and output buffers where
    // we pass the pointer to our AcceptEx function. This is used
    // so that we can call the AcceptEx function directly, rather
    // than refer to the Mswsock.lib library.
    int rt = WSAIoctl(s,
                      SIO_GET_EXTENSION_FUNCTION_POINTER,
                      &GuidAcceptEx,
                      sizeof(GuidAcceptEx),
                      &s_lpfnAcceptEx,
                      sizeof(s_lpfnAcceptEx),
                      &dwBytes,
                      NULL,
                      NULL);
    if (rt == SOCKET_ERROR)
    {
        dwarn("WSAIoctl for AcceptEx failed, err = %d", ::WSAGetLastError());
        closesocket(s);
        return;
    }


    rt = WSAIoctl(s,
                  SIO_GET_EXTENSION_FUNCTION_POINTER,
                  &GuidConnectEx,
                  sizeof(GuidConnectEx),
                  &s_lpfnConnectEx,
                  sizeof(s_lpfnConnectEx),
                  &dwBytes,
                  NULL,
                  NULL);
    if (rt == SOCKET_ERROR)
    {
        dwarn("WSAIoctl for ConnectEx failed, err = %d", ::WSAGetLastError());
        closesocket(s);
        return;
    }

    rt = WSAIoctl(s,
                  SIO_GET_EXTENSION_FUNCTION_POINTER,
                  &GuidGetAcceptExSockaddrs,
                  sizeof(GuidGetAcceptExSockaddrs),
                  &s_lpfnGetAcceptExSockaddrs,
                  sizeof(s_lpfnGetAcceptExSockaddrs),
                  &dwBytes,
                  NULL,
                  NULL);
    if (rt == SOCKET_ERROR)
    {
        dwarn("WSAIoctl for GetAcceptExSockaddrs failed, err = %d", ::WSAGetLastError());
        closesocket(s);
        return;
    }

    closesocket(s);
}