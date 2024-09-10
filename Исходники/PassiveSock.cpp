//sends a message, or part of one
int CPassiveSock::Send(const void * const lpBuf, const int Len)
{
    WSAOVERLAPPED os;
    WSABUF buffers[2];
    WSAEVENT hEvents[2] = {NULL,NULL};
    DWORD
    dwWait,
    bytes_sent=0,
    msg_flags = 0;

    // Setup up the events to wait on
    hEvents[1] = write_event;
    hEvents[0] = m_hStopEvent;
    // Setup the buffers array
    buffers[0].buf = (char *)lpBuf;
    buffers[0].len = Len;
    msg_flags = 0;
    dwWait = 0;
    int rc;

    LastError = 0;

    // Create the overlapped I/O event and structures
    memset(&os, 0, sizeof(OVERLAPPED));
    os.hEvent = write_event;
    WSAResetEvent(read_event);
    rc = WSASend(ActualSocket, buffers, 1, &bytes_sent, 0, &os, NULL);
    LastError=WSAGetLastError();
    if ((rc == SOCKET_ERROR) && (LastError == WSA_IO_PENDING))  // Write in progress
    {
        CTimeSpan TimeLeft = SendEndTime - CTime::GetCurrentTime();
        dwWait = WaitForMultipleObjects(2, hEvents, false, (DWORD)TimeLeft.GetTotalSeconds()*1000);
        if (dwWait == WAIT_OBJECT_0+1) // I/O completed
        {
            if (WSAGetOverlappedResult(ActualSocket, &os, &bytes_sent, true, &msg_flags))
                return bytes_sent;
        }
    }
    else if (!rc) // if rc is zero, the read was completed immediately
    {
        if (WSAGetOverlappedResult(ActualSocket, &os, &bytes_sent, true, &msg_flags))
            return bytes_sent;
    }
    return SOCKET_ERROR;
}