// TODO: Test for archives > 4GB
BOOL WINAPI SFileCreateArchiveEx(const char * szMpqName, DWORD dwCreationDisposition, DWORD dwHashTableSize, HANDLE * phMPQ)
{
    LARGE_INTEGER MpqPos = {0};             // Position of MPQ header in the file
    TMPQArchive * ha = NULL;                // MPQ archive handle
    HANDLE hFile = INVALID_HANDLE_VALUE;    // File handle
    DWORD dwTransferred = 0;                // Number of bytes written into the archive
    USHORT wFormatVersion;
    BOOL bFileExists = FALSE;
    int nIndex = 0;
    int nError = ERROR_SUCCESS;

    // Pre-initialize the result value
    if(phMPQ != NULL)
        *phMPQ = NULL;

    // Check the parameters, if they are valid
    if(szMpqName == NULL || *szMpqName == 0 || phMPQ == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // Check the value of dwCreationDisposition against file existence
    bFileExists = (GetFileAttributes(szMpqName) != 0xFFFFFFFF);

    // Extract format version from the "dwCreationDisposition"
    wFormatVersion = (USHORT)(dwCreationDisposition >> 0x10);
    dwCreationDisposition &= 0x0000FFFF;

    // If the file exists and open required, do it.
    if(bFileExists && (dwCreationDisposition == OPEN_EXISTING || dwCreationDisposition == OPEN_ALWAYS))
    {
        // Try to open the archive normal way. If it fails, it means that
        // the file exist, but it is not a MPQ archive.
        if(SFileOpenArchiveEx(szMpqName, 0, 0, phMPQ, GENERIC_READ | GENERIC_WRITE))
            return TRUE;
    }

    // Two error cases
    if(dwCreationDisposition == CREATE_NEW && bFileExists)
    {
        SetLastError(ERROR_ALREADY_EXISTS);
        return FALSE;
    }
    if(dwCreationDisposition == OPEN_EXISTING && bFileExists == FALSE)
    {
        SetLastError(ERROR_FILE_NOT_FOUND);
        return FALSE;
    }

    // At this point, we have to create the archive. If the file exists,
    // we will convert it to MPQ archive.
    // Check the value of hash table size. It has to be a power of two
    // and must be between HASH_TABLE_SIZE_MIN and HASH_TABLE_SIZE_MAX
    if(dwHashTableSize < HASH_TABLE_SIZE_MIN)
        dwHashTableSize = HASH_TABLE_SIZE_MIN;
    if(dwHashTableSize > HASH_TABLE_SIZE_MAX)
        dwHashTableSize = HASH_TABLE_SIZE_MAX;
    
    // Round the hash table size up to the nearest power of two
    for(nIndex = 0; PowersOfTwo[nIndex] != 0; nIndex++)
    {
        if(dwHashTableSize <= PowersOfTwo[nIndex])
        {
            dwHashTableSize = PowersOfTwo[nIndex];
            break;
        }
    }

    // Prepare the buffer for decryption engine
    if(nError == ERROR_SUCCESS)
        nError = PrepareStormBuffer();

    // Get the position where the MPQ header will begin.
    if(nError == ERROR_SUCCESS)
    {
        hFile = CreateFile(szMpqName,
                           GENERIC_READ | GENERIC_WRITE,
                           FILE_SHARE_READ,
                           NULL,
                           dwCreationDisposition,
                           0,
                           NULL);
        if(hFile == INVALID_HANDLE_VALUE)
            nError = GetLastError();
    }

    // Retrieve the file size and round it up to 0x200 bytes
    if(nError == ERROR_SUCCESS)
    {
        MpqPos.LowPart  = GetFileSize(hFile, (LPDWORD)&MpqPos.HighPart);
        MpqPos.QuadPart += 0x1FF;
        MpqPos.LowPart &= 0xFFFFFE00;

        if(wFormatVersion == MPQ_FORMAT_VERSION_1 && MpqPos.HighPart != 0)
            nError = ERROR_DISK_FULL;
        if(wFormatVersion == MPQ_FORMAT_VERSION_2 && MpqPos.HighPart > 0x0000FFFF)
            nError = ERROR_DISK_FULL;
    }

    // Move to the end of the file (i.e. begin of the MPQ)
    if(nError == ERROR_SUCCESS)
    {
        if(SetFilePointer(hFile, MpqPos.LowPart, &MpqPos.HighPart, FILE_BEGIN) == 0xFFFFFFFF)
            nError = GetLastError();
    }

    // Set the new end of the file to the MPQ header position
    if(nError == ERROR_SUCCESS)
    {
        if(!SetEndOfFile(hFile))
            nError = GetLastError();
    }

    // Create the archive handle
    if(nError == ERROR_SUCCESS)
    {
        if((ha = ALLOCMEM(TMPQArchive, 1)) == NULL)
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Fill the MPQ archive handle structure and create the header,
    // block buffer, hash table and block table
    if(nError == ERROR_SUCCESS)
    {
        memset(ha, 0, sizeof(TMPQArchive));
        strcpy(ha->szFileName, szMpqName);
        ha->hFile          = hFile;
        ha->dwBlockSize    = 0x200 << DEFAULT_BLOCK_SIZE;
        ha->MpqPos         = MpqPos;
        ha->FilePointer    = MpqPos;
        ha->pHeader        = &ha->Header;
        ha->pHashTable     = ALLOCMEM(TMPQHash, dwHashTableSize);
        ha->pBlockTable    = ALLOCMEM(TMPQBlock, dwHashTableSize);
        ha->pExtBlockTable = ALLOCMEM(TMPQBlockEx, dwHashTableSize);
        ha->pbBlockBuffer  = ALLOCMEM(BYTE, ha->dwBlockSize);
        ha->pListFile      = NULL;
        ha->dwFlags       |= MPQ_FLAG_CHANGED;

        if(!ha->pHashTable || !ha->pBlockTable || !ha->pExtBlockTable || !ha->pbBlockBuffer)
            nError = GetLastError();
        hFile = INVALID_HANDLE_VALUE;
    }

    // Fill the MPQ header and all buffers
    if(nError == ERROR_SUCCESS)
    {
        LARGE_INTEGER TempPos;
        TMPQHeader2 * pHeader = ha->pHeader;
        DWORD dwHeaderSize = (wFormatVersion == MPQ_FORMAT_VERSION_2) ? sizeof(TMPQHeader2) : sizeof(TMPQHeader);

        memset(pHeader, 0, sizeof(TMPQHeader2));
        pHeader->dwID            = ID_MPQ;
        pHeader->dwHeaderSize    = dwHeaderSize;
        pHeader->dwArchiveSize   = pHeader->dwHeaderSize + dwHashTableSize * sizeof(TMPQHash);
        pHeader->wFormatVersion  = wFormatVersion;
        pHeader->wBlockSize      = 3;               // 0x1000 bytes per block
        pHeader->dwHashTableSize = dwHashTableSize;

        // Set proper hash table positions
        ha->HashTablePos.QuadPart = ha->MpqPos.QuadPart + pHeader->dwHeaderSize;
        ha->pHeader->dwHashTablePos = pHeader->dwHeaderSize;
        ha->pHeader->wHashTablePosHigh = 0;

        // Set proper block table positions
        ha->BlockTablePos.QuadPart = ha->HashTablePos.QuadPart +
                                     (ha->pHeader->dwHashTableSize * sizeof(TMPQHash));
        TempPos.QuadPart = ha->BlockTablePos.QuadPart - ha->MpqPos.QuadPart;
        ha->pHeader->dwBlockTablePos = TempPos.LowPart;
        ha->pHeader->wBlockTablePosHigh = (USHORT)TempPos.HighPart;

        // For now, we set extended block table positioon top zero unless we add enough
        // files to cause the archive size exceed 4 GB
        ha->ExtBlockTablePos.QuadPart = 0;

        // Clear all tables
        memset(ha->pBlockTable, 0, sizeof(TMPQBlock) * dwHashTableSize);
        memset(ha->pExtBlockTable, 0, sizeof(TMPQBlockEx) * dwHashTableSize);
        memset(ha->pHashTable, 0xFF, sizeof(TMPQHash) * dwHashTableSize);
    }

    // Write the MPQ header to the file
    if(nError == ERROR_SUCCESS)
    {
        DWORD dwHeaderSize = ha->pHeader->dwHeaderSize;

        BSWAP_TMPQHEADER(ha->pHeader);
        WriteFile(ha->hFile, ha->pHeader, dwHeaderSize, &dwTransferred, NULL);
        BSWAP_TMPQHEADER(ha->pHeader);
        
        if(dwTransferred != ha->pHeader->dwHeaderSize)
            nError = ERROR_DISK_FULL;

        ha->FilePointer.QuadPart = ha->MpqPos.QuadPart + dwTransferred;
        ha->MpqSize.QuadPart += dwTransferred;
    }

    // Create the internal listfile
    if(nError == ERROR_SUCCESS)
        nError = SListFileCreateListFile(ha);

    // Try to add the internal listfile
    if(nError == ERROR_SUCCESS)
        SFileAddListFile((HANDLE)ha, NULL);

    // Cleanup : If an error, delete all buffers and return
    if(nError != ERROR_SUCCESS)
    {
        FreeMPQArchive(ha);
        if(hFile != INVALID_HANDLE_VALUE)
            CloseHandle(hFile);
        SetLastError(nError);
    }
    
    // Return the values
    *phMPQ = (HANDLE)ha;
    return (nError == ERROR_SUCCESS);
}