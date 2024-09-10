int jumpMessageQueueWaitForMessage(JUMPPlatformCString type, int32 timeout){
    DWORD cbBytes, cbMessage, cMessage = 0;
    BOOL fResult;
    char buffer;
    DWORD err, to;// error code, time out parameter
    HANDLE hSlot = mailslotGet(type, NULL);
    if (hSlot == NULL) {
        printf("ERROR: jumpMessageQueueWaitForMessage - MessageQueue does not exist\n");
        return 1;
    }
    fResult = GetMailslotInfo(hSlot,                  // mailslot handle
    (LPDWORD) NULL,         // no maximum message size
    &cbMessage,             // size of next message
    &cMessage,              // number of messages
    &to);                   // retrieves read time-out
    
    if (to != timeout){
        if (timeout < 0){
            to = MAILSLOT_WAIT_FOREVER;
        } else {
            to = timeout;
        }
        fResult = SetMailslotInfo(hSlot, to);
        if (JUMP_WIN_DEBUG) {
            printf("jumpMessageQueueWaitForMessage: read timeout set to %d\n", to);
        }
    }
    
    if (cMessage > 0) { // there are messages waiting in the MessageQueue
        return 1;
    }
    
    
    // Wait for message using blocking read
    fResult = ReadFile(hSlot,            // handle to mailslot
    &buffer,           // buffer to receive data
    0,                // size of buffer
    &cbBytes,         // number of bytes read
    NULL);            // not overlapped I/O
    if (fResult == 0) {
        err = GetLastError();
        if (err != ERROR_INSUFFICIENT_BUFFER && err != ERROR_SEM_TIMEOUT) {
            printf("ERROR: jumpMessageQueueWaitForMessage - error in reading file (%d)\n", err);
        }
    }
    if (JUMP_WIN_DEBUG) {
        GetMailslotInfo(hSlot, // mailslot handle
        (LPDWORD) NULL,               // no maximum message size
        &cbMessage,                   // size of next message
        &cMessage,                    // number of messages
        NULL);              // no read time-out
        printf("jumpMessageQueueWaitForMessage: # of messages in MessageQueue: %d\n", cMessage);
    }
    return 0;
}