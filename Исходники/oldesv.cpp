int msgRead(HANDLE hSlot)
{
	TCHAR eventNameTCHAR[STR_SIZE];
	char eventName[STR_SIZE];

    DWORD cbMessage, cMessage, cbRead; 
    BOOL fResult; 
    int receivedMsg;

    HANDLE hEvent;
    OVERLAPPED ov;
 
    cbMessage = cMessage = cbRead = 0; 

	sprintf(eventName,"%d_event",GetCurrentProcessId());
	charToTCHAR(eventNameTCHAR, eventName);
    hEvent = CreateEvent(NULL, FALSE, FALSE, eventNameTCHAR);
    if( NULL == hEvent )
        return FALSE;
    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = hEvent;
 
    fResult = GetMailslotInfo(hSlot, // mailslot handle 
        (LPDWORD) NULL,               // no maximum message size 
        &cbMessage,                   // size of next message 
        &cMessage,                    // number of messages 
        (LPDWORD) NULL);              // no read time-out 
    if (!fResult) 
    { 
        printf("GetMailslotInfo failed with %d.\n", GetLastError()); 
        exit(0);
    } 
 
    if (cbMessage == MAILSLOT_NO_MESSAGE) 
    { 
        /*no message in the mail box*/
        return MSG_NO_MESSAGE; 
    } 
	
	/*with the way we set up the mail box, there should only be 1 message waiting*/
    if(cMessage!=1)
	{
		printf("ERROR messaging system is not synchronized\n");
		exit(0);
	}
    if(cbMessage!=4)
	{
		printf("ERROR message size is incorrect\n");
		exit(0);
	}
 
    /*retrieve the message*/
    fResult = ReadFile(hSlot, 
        &receivedMsg, 
        cbMessage, 
        &cbRead, 
        &ov); 
    if (!fResult) 
    { 
        printf("ReadFile failed with %d.\n", GetLastError());
        exit(0);
    } 

    CloseHandle(hEvent);

    return receivedMsg; 
}