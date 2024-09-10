//Return FALSE if no message is available
//Return TRUE and write the output to message in case of no error.
BOOL ReadSlot(HANDLE hSlot, char* message) 
{ 
    DWORD cbMessage, cMessage, cbRead; 
    BOOL fResult; 
    LPTSTR lpszBuffer; 
    TCHAR achID[80]; 
    DWORD cAllMessages; 
    HANDLE hEvent;
    OVERLAPPED ov;
 
    //Clear message contents
    message[0] = '\0';

    cbMessage = cMessage = cbRead = 0; 

    hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ExampleSlot"));
    if( NULL == hEvent )
        return FALSE;
    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = hEvent;
 
    fResult = GetMailslotInfo( hSlot, // mailslot handle 
        (LPDWORD) NULL,               // no maximum message size 
        &cbMessage,                   // size of next message 
        &cMessage,                    // number of messages 
        (LPDWORD) NULL);              // no read time-out 
 
    if (!fResult) 
    { 
         std::cout << "GetMailslotInfo failed." << std::endl; 
        return FALSE; 
    } 
 
    if (cbMessage == MAILSLOT_NO_MESSAGE) 
    { 
        //std::cout << "Waiting for a message..." << std::endl; 
        return FALSE; 
    } 
 
    cAllMessages = cMessage; 
    if (cMessage != 0)
    {
        while (cMessage != 0)  // retrieve all messages
        { 
            // Allocate memory for the message. 

            lpszBuffer = (LPTSTR) GlobalAlloc(GPTR, 
                lstrlen((LPTSTR) achID)*sizeof(TCHAR) + cbMessage); 
            if( NULL == lpszBuffer )
                return FALSE;
            lpszBuffer[0] = '\0'; 
 
            fResult = ReadFile(hSlot, 
                lpszBuffer, 
                cbMessage, 
                &cbRead, 
                &ov); 
 
            if (!fResult) 
            { 
                 std::cout << "ReadFile failed." << std::endl; 
                GlobalFree((HGLOBAL) lpszBuffer); 
                return FALSE; 
            } 
 
            // Write the message. 
        
            strcpy_s(message, 1024, lpszBuffer);
            //std::cout << message << std::endl;

            GlobalFree((HGLOBAL) lpszBuffer); 
 
            fResult = GetMailslotInfo(hSlot,  // mailslot handle 
                (LPDWORD) NULL,               // no maximum message size 
                &cbMessage,                   // size of next message 
                &cMessage,                    // number of messages 
                (LPDWORD) NULL);              // no read time-out 
 
            if (!fResult) 
            { 
                 std::cout << "GetMailslotInfo failed." << std::endl;
                return FALSE; 
            } 
        } 
        CloseHandle(hEvent);
        return TRUE;
    }
    CloseHandle(hEvent);
    return FALSE; 
}