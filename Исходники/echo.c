static BOOL
EchoIncomingPackets(SOCKET sock)
{
    CHAR readBuffer[RECV_BUF];
    WCHAR logBuf[256];
    INT totalSentBytes;
    INT readBytes;
    INT retVal;

    do 
    {
        readBytes = recv(sock, readBuffer, RECV_BUF, 0);
        if (readBytes > 0)
        {
            _swprintf(logBuf, L"Received %d bytes from client", readBytes);
            LogEvent(logBuf, 0, 0, LOG_FILE);

            totalSentBytes = 0;
            while (!bShutdown && totalSentBytes < readBytes)
            {
                retVal = send(sock, readBuffer + totalSentBytes, readBytes - totalSentBytes, 0);
                if (retVal > 0)
                {
                    _swprintf(logBuf, L"Sent %d bytes back to client", retVal);
                    LogEvent(logBuf, 0, 0, LOG_FILE);
                    totalSentBytes += retVal;
                }
                else if (retVal == SOCKET_ERROR)
                {
                    LogEvent(L"Echo: socket error", WSAGetLastError(), 0, LOG_ERROR);
                    return FALSE;
                }
                else
                {
                    /* Client closed connection before we could reply to
                       all the data it sent, so quit early. */
                    LogEvent(L"Peer unexpectedly dropped connection!", 0, 0, LOG_FILE);
                    return FALSE;
                }
            }
        }
        else if (readBytes == SOCKET_ERROR)
        {
            LogEvent(L"Echo: socket error", WSAGetLastError(), 0, LOG_ERROR);
            return FALSE;
        }
    } while ((readBytes != 0) && (!bShutdown));

    if (!bShutdown)
        LogEvent(L"Echo: Connection closed by peer", 0, 0, LOG_FILE);

    return TRUE;
}