GOS_ERROR_CODE vos_taskLogWrite(LOG_PRINT_MSG_T* pMsg)
{
    LOG_ID loggerId;

    LOG_ENTRY_HEADER_T tempEntry;
    UINT32 msgSize, entrySize;
    LOG_ENTRY_HEADER_T* pNextEntry;
    UINT32 preEntrySize, paddedSize;

    VOS_ASSERT(NULL != pMsg);

    loggerId = vos_taskLogGetId(pMsg->loggerId);
    if (0 > (loggerId))
    {
        return GOS_ERR_NOT_FOUND;
    }
    
    tempEntry.ulTime = pMsg->tick;
    tempEntry.level = pMsg->ubLogLevel;
    tempEntry.line = pMsg->lineNum;
    memcpy(tempEntry.fileName, pMsg->fileName, LOG_FILE_NAME_MAX_LEN);
    tempEntry.pNext = (UINT32)NULL;
    tempEntry.pPrev = (UINT32)NULL;

    if (gTaskLogs[loggerId].enableUdp)
    {
        CHAR buf[LOG_ENTRY_MAX_SIZE * 5];
        INT32 fd;
        struct sockaddr_in to;
        UINT32 toLen = sizeof(to);

        sprintf(buf, "%s:0x%x:%s:%d:%s", gTaskLogs[loggerId].logName, 
                tempEntry.ulTime, tempEntry.fileName, tempEntry.line, pMsg->content);
                
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (ERROR != fd)
        {
            BOOL on;
            
            memset(&to, 0, toLen);

            to.sin_family = AF_INET;
            to.sin_port = VOS_Htons((UINT16)gTaskLogs[loggerId].hostPort);
            to.sin_addr.s_addr = inet_addr(gTaskLogs[loggerId].hostIp);

            // non-blocking IO
            on = TRUE;
            ioctl (fd, FIONBIO, (INT32)&on);
            sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&to, toLen);

            close(fd);
        }
    }

    if (!gTaskLogs[loggerId].enableMem)
    {
        return GOS_OK;
    }

    // Get message size
    msgSize = ((strlen(pMsg->content)+1) > LOG_ENTRY_MAX_SIZE) ? LOG_ENTRY_MAX_SIZE : (strlen(pMsg->content)+1);
    // Terminate the string
    pMsg->content[msgSize - 1] = 0;

    
    // Get entry size (message size + head size)
    entrySize = msgSize + sizeof(LOG_ENTRY_HEADER_T);
    // Align with 4 bytes
    entrySize = (entrySize + 3) & 0xFFFFFFFC;
    VOS_Lock(gTaskLogs[loggerId].lockId, 0);

    // If the log is empty
    if ((NULL == gTaskLogs[loggerId].pPrevEntry) || (NULL == gTaskLogs[loggerId].pFirstEntry))
    {
        tempEntry.pPrev = (UINT32)NULL;
        tempEntry.pNext = (UINT32)(gTaskLogs[loggerId].pBuff + entrySize);
        memcpy(gTaskLogs[loggerId].pBuff, &tempEntry, sizeof(LOG_ENTRY_HEADER_T));
        memcpy(gTaskLogs[loggerId].pBuff + sizeof(LOG_ENTRY_HEADER_T), pMsg->content, msgSize);
        gTaskLogs[loggerId].pFirstEntry = (LOG_ENTRY_HEADER_T*)gTaskLogs[loggerId].pBuff;
        gTaskLogs[loggerId].pPrevEntry = (LOG_ENTRY_HEADER_T*)gTaskLogs[loggerId].pBuff;

        // Initialize the next header
        pNextEntry = (LOG_ENTRY_HEADER_T*)tempEntry.pNext;
        pNextEntry->pNext = (UINT32)NULL;
        pNextEntry->pPrev = (UINT32)gTaskLogs[loggerId].pPrevEntry;

        *(UINT32*)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize + 8 ) = (UINT32)gTaskLogs[loggerId].pFirstEntry;
        *(UINT32*)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize + 12) = (UINT32)gTaskLogs[loggerId].pPrevEntry;

        VOS_Unlock(gTaskLogs[loggerId].lockId);
        return GOS_OK;
    }

    // Get previous entity size
    if ((UINT32)gTaskLogs[loggerId].pPrevEntry->pNext > (UINT32)gTaskLogs[loggerId].pPrevEntry)
    {
        preEntrySize = (UINT32)gTaskLogs[loggerId].pPrevEntry->pNext - (UINT32)gTaskLogs[loggerId].pPrevEntry;
    }
    else
    {
        preEntrySize = (UINT32)gTaskLogs[loggerId].pPrevEntry->pNext + gTaskLogs[loggerId].bufSize - (UINT32)gTaskLogs[loggerId].pPrevEntry;
    }

    // Get padded size
    paddedSize = 0;
    // if the available space is not enough, then leave it, go to the head
    if ((gTaskLogs[loggerId].pPrevEntry->pNext + entrySize + sizeof(LOG_ENTRY_HEADER_T)) > (UINT32)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize))
    {
        paddedSize = (UINT32)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize - gTaskLogs[loggerId].pPrevEntry->pNext);
        gTaskLogs[loggerId].pPrevEntry->pNext = (UINT32)gTaskLogs[loggerId].pBuff;
    }

    // log_GetFreeSpaceSize returns the space between m_pPrevEntry and m_pFirstEntry
    // including m_pPrevEntry self
    while (vos_taskLogGetFreeSize(loggerId) < preEntrySize + paddedSize + entrySize + sizeof(LOG_ENTRY_HEADER_T))
    {
        if (gTaskLogs[loggerId].pFirstEntry)
        {
            gTaskLogs[loggerId].pFirstEntry = (LOG_ENTRY_HEADER_T*)gTaskLogs[loggerId].pFirstEntry->pNext;
        }
        else
        {
            VOS_Unlock(gTaskLogs[loggerId].lockId);
            return GOS_ERR_OVERFLOW;
        }
    }
    gTaskLogs[loggerId].pFirstEntry->pPrev = (UINT32)NULL;

    // Find the right place
    tempEntry.pPrev = (UINT32)gTaskLogs[loggerId].pPrevEntry;
    tempEntry.pNext = gTaskLogs[loggerId].pPrevEntry->pNext + entrySize;
    
    memcpy((CHAR*)gTaskLogs[loggerId].pPrevEntry->pNext, &tempEntry, sizeof(LOG_ENTRY_HEADER_T));
    memcpy((CHAR*)gTaskLogs[loggerId].pPrevEntry->pNext + sizeof(LOG_ENTRY_HEADER_T), pMsg->content, msgSize);

    gTaskLogs[loggerId].pPrevEntry = (LOG_ENTRY_HEADER_T*)gTaskLogs[loggerId].pPrevEntry->pNext;

    // Initialize the next header
    pNextEntry = (LOG_ENTRY_HEADER_T*)tempEntry.pNext;
    pNextEntry->pNext = (UINT32)NULL;
    pNextEntry->pPrev = (UINT32)gTaskLogs[loggerId].pPrevEntry;

    *(UINT32*)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize + 8 ) = (UINT32)gTaskLogs[loggerId].pFirstEntry;
    *(UINT32*)(gTaskLogs[loggerId].pBuff + gTaskLogs[loggerId].bufSize + 12) = (UINT32)gTaskLogs[loggerId].pPrevEntry;

    VOS_Unlock(gTaskLogs[loggerId].lockId);

    return GOS_OK;
}