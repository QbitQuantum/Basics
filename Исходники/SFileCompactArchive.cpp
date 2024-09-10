bool WINAPI SFileCompactArchive(HANDLE hMpq, const char * szListFile, bool /* bReserved */)
{
    TFileStream * pTempStream = NULL;
    TMPQArchive * ha = (TMPQArchive *)hMpq;
    ULONGLONG ByteOffset;
    ULONGLONG ByteCount;
    LPDWORD pFileKeys = NULL;
    TCHAR szTempFile[MAX_PATH] = _T("");
    TCHAR * szTemp = NULL;
    int nError = ERROR_SUCCESS;

    // Test the valid parameters
    if(!IsValidMpqHandle(ha))
        nError = ERROR_INVALID_HANDLE;
    if(ha->dwFlags & MPQ_FLAG_READ_ONLY)
        nError = ERROR_ACCESS_DENIED;

    // If the MPQ is changed at this moment, we have to flush the archive
    if(nError == ERROR_SUCCESS && (ha->dwFlags & MPQ_FLAG_CHANGED))
    {
        SFileFlushArchive(hMpq);
    }

    // Create the table with file keys
    if(nError == ERROR_SUCCESS)
    {
        if((pFileKeys = STORM_ALLOC(DWORD, ha->dwFileTableSize)) != NULL)
            memset(pFileKeys, 0, sizeof(DWORD) * ha->dwFileTableSize);
        else
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // First of all, we have to check of we are able to decrypt all files.
    // If not, sorry, but the archive cannot be compacted.
    if(nError == ERROR_SUCCESS)
    {
        // Initialize the progress variables for compact callback
        FileStream_GetSize(ha->pStream, CompactTotalBytes);
        CompactBytesProcessed = 0;
        nError = CheckIfAllFilesKnown(ha, szListFile, pFileKeys);
    }

    // Get the temporary file name and create it
    if(nError == ERROR_SUCCESS)
    {
        _tcscpy(szTempFile, ha->pStream->szFileName);
        if((szTemp = _tcsrchr(szTempFile, '.')) != NULL)
            _tcscpy(szTemp + 1, _T("mp_"));
        else
            _tcscat(szTempFile, _T("_"));

        pTempStream = FileStream_CreateFile(szTempFile);
        if(pTempStream == NULL)
            nError = GetLastError();
    }

    // Write the data before MPQ user data (if any)
    if(nError == ERROR_SUCCESS && ha->UserDataPos != 0)
    {
        // Inform the application about the progress
        if(CompactCB != NULL)
            CompactCB(pvUserData, CCB_COPYING_NON_MPQ_DATA, CompactBytesProcessed, CompactTotalBytes);

        ByteOffset = 0;
        ByteCount = ha->UserDataPos;
        nError = CopyNonMpqData(ha->pStream, pTempStream, ByteOffset, ByteCount);
    }

    // Write the MPQ user data (if any)
    if(nError == ERROR_SUCCESS && ha->MpqPos > ha->UserDataPos)
    {
        // At this point, we assume that the user data size is equal
        // to pUserData->dwHeaderOffs.
        // If this assumption doesn't work, then we have an unknown version of MPQ
        ByteOffset = ha->UserDataPos;
        ByteCount = ha->MpqPos - ha->UserDataPos;

        assert(ha->pUserData != NULL);
        assert(ha->pUserData->dwHeaderOffs == ByteCount);
        nError = CopyNonMpqData(ha->pStream, pTempStream, ByteOffset, ByteCount);
    }

    // Write the MPQ header
    if(nError == ERROR_SUCCESS)
    {
        // Remember the header size before swapping
        DWORD dwBytesToWrite = ha->pHeader->dwHeaderSize;

        BSWAP_TMPQHEADER(ha->pHeader);
        if(!FileStream_Write(pTempStream, NULL, ha->pHeader, dwBytesToWrite))
            nError = GetLastError();
        BSWAP_TMPQHEADER(ha->pHeader);

        // Update the progress
        CompactBytesProcessed += ha->pHeader->dwHeaderSize;
    }

    // Now copy all files
    if(nError == ERROR_SUCCESS)
    {
        nError = CopyMpqFiles(ha, pFileKeys, pTempStream);
        ha->dwFlags |= MPQ_FLAG_CHANGED;
    }

    // If succeeded, switch the streams
    if(nError == ERROR_SUCCESS)
    {
        if(FileStream_MoveFile(ha->pStream, pTempStream))
            pTempStream = NULL;
        else
            nError = ERROR_CAN_NOT_COMPLETE;
    }

    // If all succeeded, save the MPQ tables
    if(nError == ERROR_SUCCESS)
    {
        //
        // Note: We don't recalculate position of the MPQ tables at this point.
        // SaveMPQTables does it automatically.
        // 

        nError = SaveMPQTables(ha);
        if(nError == ERROR_SUCCESS && CompactCB != NULL)
        {
            CompactBytesProcessed += (ha->pHeader->dwHashTableSize * sizeof(TMPQHash));
            CompactBytesProcessed += (ha->pHeader->dwBlockTableSize * sizeof(TMPQBlock));
            CompactCB(pvUserData, CCB_CLOSING_ARCHIVE, CompactBytesProcessed, CompactTotalBytes);
        }
    }

    // Invalidate the compact callback
    pvUserData = NULL;
    CompactCB = NULL;

    // Cleanup and return
    if(pTempStream != NULL)
        FileStream_Close(pTempStream);
    if(pFileKeys != NULL)
        STORM_FREE(pFileKeys);
    if(nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}