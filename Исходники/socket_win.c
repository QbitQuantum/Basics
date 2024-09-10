static void
chanSwitchAccept(TChanSwitch * const chanSwitchP,
                 TChannel **   const channelPP,
                 void **       const channelInfoPP,
                 const char ** const errorP) {
/*----------------------------------------------------------------------------
   Accept a connection via the channel switch *chanSwitchP.  Return as
   *channelPP the channel for the accepted connection.

   If no connection is waiting at *chanSwitchP, wait until one is.

   If we receive a signal while waiting, return immediately with
   *channelPP == NULL.
-----------------------------------------------------------------------------*/
    struct socketWin * const listenSocketP = chanSwitchP->implP;
    HANDLE acceptEvent = WSACreateEvent();
    bool interrupted;
    TChannel * channelP;

    interrupted = FALSE; /* Haven't been interrupted yet */
    channelP    = NULL;  /* No connection yet */
    *errorP     = NULL;  /* No error yet */

    WSAEventSelect(listenSocketP->winsock, acceptEvent,
                   FD_ACCEPT | FD_CLOSE | FD_READ);

    while (!channelP && !*errorP && !interrupted) {
        HANDLE interrupts[2] = {acceptEvent, listenSocketP->interruptEvent};
        int rc;
        struct sockaddr peerAddr;
        socklen_t size = sizeof(peerAddr);

        rc = WaitForMultipleObjects(2, interrupts, FALSE, INFINITE);
        if (WAIT_OBJECT_0 + 1 == rc) {
            interrupted = TRUE;
            continue;
        };

        rc = accept(listenSocketP->winsock, &peerAddr, &size);

        if (rc >= 0) {
            int const acceptedWinsock = rc;

            createChannelForAccept(acceptedWinsock, peerAddr,
                                   &channelP, channelInfoPP, errorP);

            if (*errorP)
                closesocket(acceptedWinsock);
        } else {
            int const lastError = WSAGetLastError();

            if (lastError == WSAEINTR)
                interrupted = TRUE;
            else
                xmlrpc_asprintf(errorP,
                                "accept() failed, WSA error = %d (%s)",
                                lastError, getWSAError(lastError));
        }
    }
    *channelPP = channelP;
    CloseHandle(acceptEvent);
}