__declspec(dllexport) bool TITCALL FixHeaderCheckSumW(wchar_t* szFileName)
{
    HANDLE FileHandle;
    DWORD FileSize;
    HANDLE FileMap;
    ULONG_PTR FileMapVA;
    bool retVal = false;

    if(MapFileExW(szFileName, UE_ACCESS_READ, &FileHandle, &FileSize, &FileMap, &FileMapVA, 0))
    {
        DWORD HeaderSum;
        DWORD CheckSum;
        if(CheckSumMappedFile((PVOID)FileMapVA, FileSize, &HeaderSum, &CheckSum))
        {
            retVal = SetPE32DataW(szFileName, NULL, UE_CHECKSUM, (ULONG_PTR)CheckSum);
        }
        UnMapFileEx(FileHandle, FileSize, FileMap, FileMapVA);
    }
    return retVal;
}