void msRead(void)
{
    DWORD cbMessage, cMessage, cbRead;
    BOOL fResult;
    LPSTR lpszBuffer;

    cbMessage = cMessage = cbRead = 0;
    fResult = GetMailslotInfo(hLocalSlot, // mailslot handle
                              (LPDWORD)NULL, // no maximum message size
                              &cbMessage, // size of next message
                              &cMessage, // number of messages
                              (LPDWORD)NULL); // no read time-out
    if (!fResult) return;
    if (cbMessage == MAILSLOT_NO_MESSAGE) return;
    while (cMessage != 0) // retrieve all messages
    {
        // Allocate memory for the message.
        lpszBuffer = (LPSTR)GlobalAlloc(GPTR, cbMessage);
        lpszBuffer[0] = '\0';
        fResult = ReadFile(hLocalSlot, lpszBuffer, cbMessage, &cbRead, (LPOVERLAPPED)NULL);
        if (!fResult)
        {
            GlobalFree((HGLOBAL)lpszBuffer);
            return;
        }
        msParse(lpszBuffer);
        GlobalFree((HGLOBAL)lpszBuffer);
        fResult = GetMailslotInfo(hLocalSlot, // mailslot handle
                                  (LPDWORD)NULL, // no maximum message size
                                  &cbMessage, // size of next message
                                  &cMessage, // number of messages
                                  (LPDWORD)NULL); // no read time-out
        if (!fResult) return;
    }
}