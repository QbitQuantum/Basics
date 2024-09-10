/*---------------------------------------------------------------------------*/
static PIMAGE_NT_HEADERS getPEHeader(const wchar_t *dllfilename)
{
    HANDLE hMap = INVALID_HANDLE_VALUE;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    void* mapAddr = NULL;
    PIMAGE_NT_HEADERS peHdr = NULL;


    hFile = CreateFileW(dllfilename,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    hMap = CreateFileMapping(hFile,
                             NULL,           // security attrs
                             PAGE_READONLY,  // protection flags
                             0,              // max size - high DWORD
                             0,              // max size - low DWORD
                             NULL );         // mapping name - not used

    if (hMap == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
        return NULL;
    }

    // next, map the file to our address space
    mapAddr = MapViewOfFileEx(
                  hMap,             // mapping object
                  FILE_MAP_READ,  // desired access
                  0,
                  0,
                  0,
                  NULL );         // suggested map addr

    if (mapAddr == NULL)
    {
        CloseHandle(hMap);
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
        hMap = INVALID_HANDLE_VALUE;
        return NULL;
    }

    peHdr = ImageNtHeader( mapAddr );
    if (peHdr)
    {
        if (peHdr->FileHeader.SizeOfOptionalHeader == 0)
        {
            peHdr = NULL;
        }
    }

    CloseHandle(hMap);
    CloseHandle(hFile);
    hFile = INVALID_HANDLE_VALUE;
    hMap = INVALID_HANDLE_VALUE;

    return peHdr;
}