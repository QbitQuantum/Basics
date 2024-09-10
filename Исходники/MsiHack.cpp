/** Kernel32 - ReadFileEx */
static BOOL WINAPI MsiHack_Kernel32_ReadFileEx(HANDLE hFile, LPVOID pvBuffer, DWORD cbToRead, LPOVERLAPPED pOverlapped,
                                               LPOVERLAPPED_COMPLETION_ROUTINE pfnCompletionRoutine)
{
    /*
     * If intercepted handle, deal with it.
     */
    PMSIHACKHANDLE pHandle = MsiHackHandleRetain(hFile);
    if (pHandle)
    {
        MsiHackHandleRelease(pHandle);

        MsiHackErrorF("Unexpected ReadFileEx call!\n");
        SetLastError(ERROR_INVALID_FUNCTION);
        return FALSE;
    }

    /*
     * Not one of ours.
     */
    return ReadFileEx(hFile, pvBuffer, cbToRead, pOverlapped, pfnCompletionRoutine);
}