/**
 * Common implementation between pcsl_datagram_read_start() 
 * and pcsl_datagram_read_finish().
 */
static int pcsl_datagram_read_common(void *handle, unsigned char *pAddress,
        int *port, char *buffer, int length, int *pBytesRead) {
    SOCKET s = (SOCKET)handle;
    struct sockaddr_in addr;
    int len = sizeof(struct sockaddr_in);
    int status;

    status = recvfrom(s, buffer, length, 0, (struct sockaddr*)&addr,  &len);
    lastError = WSAGetLastError();

    if (SOCKET_ERROR == status) {
        if (WSAEWOULDBLOCK == lastError) {
            /*
             * Win32 only has one notifier per socket so always set both and
             * close, the MIDP event code can handle any extra notifications.
             * Do not cancel the notifications until the socket is closed.
             */
            WSAAsyncSelect(s, win32app_get_window_handle(), WM_NETWORK,
                           FD_READ | FD_WRITE | FD_CLOSE);
            return PCSL_NET_WOULDBLOCK;
        }

        if (WSAECONNRESET == lastError) {
            /* The last call to sendto failed. Just return 0. */
            memset(pAddress, 0, sizeof(addr.sin_addr.s_addr)); 
            *port = 0;
            *pBytesRead = 0;

            return PCSL_NET_SUCCESS;
        }

        if (WSAEINTR == lastError) {
            return PCSL_NET_INTERRUPTED;
        }

        if (WSAEMSGSIZE == lastError) {
            /* The message was bigger than the buffer provided. */
            status = length;
        } else {
            return PCSL_NET_IOERROR;
        }
    }

    memcpy(pAddress, &addr.sin_addr.s_addr, sizeof(addr.sin_addr.s_addr)); 
    *port = ntohs(addr.sin_port);
    *pBytesRead = status;

    return PCSL_NET_SUCCESS;
}