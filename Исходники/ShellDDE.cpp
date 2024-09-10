static LPITEMIDLIST _ILReadFromSharedMemory(PCWSTR strField)
{
    LPITEMIDLIST ret = NULL;

    // Ensure it really is an IDLIST-formatted parameter
    // Format for IDLIST params: ":pid:shared"
    if (*strField != L':')
        return NULL;

    HANDLE hData = (HANDLE) StrToIntW(strField + 1);
    PWSTR strSecond = StrChrW(strField + 1, L':');

    if (strSecond)
    {
        int pid = StrToIntW(strSecond + 1);
        void* pvShared = SHLockShared(hData, pid);
        if (pvShared)
        {
            ret = ILClone((LPCITEMIDLIST) pvShared);
            SHUnlockShared(pvShared);
            SHFreeShared(hData, pid);
        }
    }
    return ret;
}