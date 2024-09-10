/**
 * Opens a datagram socket
 *
 * @param port The local port to attach to
 * @param pHandle address of variable to receive the handle; this is set
 *        only when this function returns JAVACALL_OK.
 *
 * @return JAVACALL_OK if the function completes successfully
 *         JAVACALL_FAIL if there was an IO error and IOException needs to be thrown;
 */
javacall_result javacall_datagram_open(
    int port,
  javacall_handle *pHandle) {

    SOCKET s;
    int truebuf = -1;
    int status;
    struct sockaddr_in addr;
    unsigned long nonblockingFlag = 1;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    lastError = WSAGetLastError();
    if (INVALID_SOCKET == s) {
        return JAVACALL_OK;
    }

    status = setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
                        (char*)&truebuf, sizeof (truebuf));
    lastError = WSAGetLastError();
    if (SOCKET_ERROR == status) {
        (void)closesocket(s);
        return JAVACALL_FAIL;
    }

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons((unsigned short)port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    status = bind(s, (struct sockaddr*)&addr, sizeof (addr));
    lastError = WSAGetLastError();
    if (SOCKET_ERROR == status) {
        (void)closesocket(s);
        return JAVACALL_FAIL;
    }

    /* Set the socket to non-blocking. */
    ioctlsocket(s, FIONBIO, &nonblockingFlag);
     /*
       * Win32 only has one notifier per socket so always set both and
       * close, the MIDP event code can handle any extra notifications.
       * Do not cancel the notifications until the socket is closed.
       */
        WSAAsyncSelect(s, midpGetWindowHandle(), WM_NETWORK,
                           FD_READ | FD_WRITE | FD_CLOSE);

    *pHandle = (void*)s;

    return JAVACALL_OK;
  }