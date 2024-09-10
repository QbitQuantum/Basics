//-----------------------------------------------------------------------------
// Name: GetChecksum
// Object: return the current file checksum stored in NTHeader.OptionalHeader.CheckSum
//         and the real file checksum
// Parameters :
//     in  : 
//     out :
//     return : FALSE on error
//-----------------------------------------------------------------------------
BOOL CPEChecksum::GetChecksum(DWORD* pCurrentHeaderCheckSum,DWORD* pRealCheckSum)
{
    HANDLE hFile;
    HANDLE hFileMapping;
    LPVOID BaseAddress;

    if (IsBadWritePtr(pCurrentHeaderCheckSum,sizeof(DWORD))
        || IsBadWritePtr(pRealCheckSum,sizeof(DWORD)))
        return FALSE;

    // open file
    hFile = CreateFile(this->pcFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile==INVALID_HANDLE_VALUE)
    {
        CAPIError::ShowLastError();
        return FALSE;
    }
    // create file mapping
    hFileMapping=CreateFileMapping(hFile,NULL,PAGE_READONLY,0,0,NULL);
    if (!hFileMapping)
    {
        CAPIError::ShowLastError();
        CloseHandle(hFile);
        return FALSE;
    }
    // map view of file
    BaseAddress=MapViewOfFile(hFileMapping,FILE_MAP_READ,0,0,0);

    if (BaseAddress==NULL)
    {
        CAPIError::ShowLastError();
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        return FALSE;
    }

    // get checksum infos
    if (!CheckSumMappedFile(
                        BaseAddress,
                        GetFileSize(hFile,NULL), // FileLength
                        pCurrentHeaderCheckSum,  // HeaderSum
                        pRealCheckSum            // CheckSum
                        )
       )
    {
        CAPIError::ShowLastError();
        UnmapViewOfFile(BaseAddress);
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        return FALSE;
    }

    // unmap view of file
    UnmapViewOfFile(BaseAddress);
    // close file mapping
    CloseHandle(hFileMapping);
    // close file
    CloseHandle(hFile);
    return TRUE;
}