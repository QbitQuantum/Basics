void TUI::CheckMailslot()
{
    DWORD cbMessage, cMessage, cbRead;
	BOOL fResult;
	LPSTR lpszBuffer;

    cbMessage = cMessage = cbRead = 0;
    fResult = GetMailslotInfo(hMailSlot,	// mailslot handle
        (LPDWORD) NULL,						// no maximum message size
        &cbMessage,							// size of next message
        &cMessage,							// number of messages
        (LPDWORD) NULL);					// no read time-out
	R_ASSERT2(fResult,"Can't get mailslot info");
	if (cbMessage == MAILSLOT_NO_MESSAGE) return;
    while (cMessage != 0)  // retrieve all messages
	{
		// Allocate memory for the message.
		lpszBuffer = (LPSTR) GlobalAlloc(GPTR, cbMessage);
		lpszBuffer[0] = '\0';
		fResult = ReadFile(hMailSlot, lpszBuffer, cbMessage, &cbRead, (LPOVERLAPPED) NULL);
		if (!fResult) {
			GlobalFree((HGLOBAL) lpszBuffer);
			throw Exception("Can't ReadFile");
		}
		OnReceiveMail(lpszBuffer);
		GlobalFree((HGLOBAL) lpszBuffer);
		fResult = GetMailslotInfo(hMailSlot,	// mailslot handle
			(LPDWORD) NULL,							// no maximum message size
			&cbMessage,								// size of next message
			&cMessage,								// number of messages
			(LPDWORD) NULL);						// no read time-out
		R_ASSERT2(fResult,"Can't get mailslot info");
    }
}