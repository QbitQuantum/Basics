static BOOL
RecieveIncomingPackets(SOCKET sock)
{
    CHAR readBuffer[BUFSIZE];
    INT readBytes;

    do
    {
        readBytes = recv(sock, readBuffer, BUFSIZE, 0);
        if (readBytes > 0)
        {
            TCHAR logBuf[256];

            _swprintf(logBuf, L"Discard: Received %d bytes from client", readBytes);
            LogEvent(logBuf, 0, 0, LOG_FILE);
        }
        else if (readBytes == SOCKET_ERROR)
        {
            LogEvent(L"Discard: Socket Error", WSAGetLastError(), 0, LOG_ERROR);
            return FALSE;
        }
    } while ((readBytes > 0) && (!bShutdown));

    if (!bShutdown)
        LogEvent(L"Discard: Connection closed by peer", 0, 0, LOG_FILE);

    return TRUE;
}