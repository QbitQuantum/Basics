/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ServerRoutine
-- DATE:	14/04/16
-- REVISIONS:	(V1.0)
-- DESIGNER:	Martin Minkov
-- PROGRAMMER:  Martin Minkov
-- INTERFACE:	void CALLBACK ServerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags)
--
--
-- RETURNS: VOID
-- NOTES: The completion routine used for UDP receiving. Constantly pushes valid data received into the circ buff
            so it can be used to play audio later.
----------------------------------------------------------------------------------------------------------------------*/
void CALLBACK ServerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, DWORD InFlags)
{
    DWORD RecvBytes = 0, Index;
    DWORD Flags = 0;
    WSAEVENT			EventArray[1] = { 0 };
    WSAEVENT			acceptEvent;

    // Reference the WSAOVERLAPPED structure as a SOCKET_INFORMATION structure
    LPSOCKET_INFORMATION SOCKINFO = (LPSOCKET_INFORMATION)Overlapped;
    initSockInfo(SOCKINFO, SOCKINFO->Buffer, SOCKINFO->server);

    if (Error != 0)
    {
        qDebug() << "I/O operation failed with value" + Error;
        printf("%d", Error);
        fflush(stdout);
        GlobalFree(SOCKINFO);
        SetEvent(streamStop);
        return;
    }
    if ((acceptEvent = WSACreateEvent()) == WSA_INVALID_EVENT)
    {
        qDebug() <<"WSACreateEvent() failed";
        GlobalFree(SOCKINFO);
        return;
    }

    Index = WSAWaitForMultipleEvents(1, EventArray, FALSE, 10000000, TRUE);

    if (Index == WSA_WAIT_TIMEOUT)
    {
        qDebug() <<"Timeout in UDP Server";
        GlobalFree(SOCKINFO);
        return;
    }
    receiveUDP(SOCKINFO, streamServer, BytesTransferred, Flags);
    cData.push(SOCKINFO->Buffer, 60000);
}