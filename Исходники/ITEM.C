static WORD ClearItemChunks(WORD wType)
{
    WORD wSize;
    GLOBALHANDLE hChunk, hChunk1; 

    GetHandle(wType, (GLOBALHANDLE *) &hChunk, (WORD FAR *) &wSize, 
              (BOOL) GET_CHUNK);

    while (hChunk && (hChunk1 = hChunk)) {
        FIXCHUNKHDR lpChunk = (FIXCHUNKHDR) GLOBALLOCK(hChunk);
        
        if (!lpChunk)
            return ERROR;
        
        if (lpChunk->hTable)
            GLOBALFREE(lpChunk->hTable);
        if (lpChunk->hChunkTable)
            GLOBALFREE(lpChunk->hChunkTable);

        hChunk = lpChunk->hNext;
        GLOBALUNLOCK(hChunk1);
        GLOBALFREE(hChunk1);
    }

    return TRUE;
}