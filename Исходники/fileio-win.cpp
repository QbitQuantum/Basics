RTR3DECL(int)  RTFileUnlock(RTFILE hFile, int64_t offLock, uint64_t cbLock)
{
    Assert(offLock >= 0);

    if (UnlockFile((HANDLE)RTFileToNative(hFile),
                   LOW_DWORD(offLock), HIGH_DWORD(offLock),
                   LOW_DWORD(cbLock), HIGH_DWORD(cbLock)))
        return VINF_SUCCESS;

    return RTErrConvertFromWin32(GetLastError());
}