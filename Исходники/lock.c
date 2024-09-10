/*
 * @implemented
 */
BOOL
WINAPI
UnlockFile(IN HANDLE hFile,
           IN DWORD dwFileOffsetLow,
           IN DWORD dwFileOffsetHigh,
           IN DWORD nNumberOfBytesToUnlockLow,
           IN DWORD nNumberOfBytesToUnlockHigh)
{
    OVERLAPPED Overlapped;
    NTSTATUS Status;
    BOOLEAN Result;

    /* Convert parameters to Ex format and call the new API */
    Overlapped.Offset = dwFileOffsetLow;
    Overlapped.OffsetHigh = dwFileOffsetHigh;
    Result = UnlockFileEx(hFile,
                          0,
                          nNumberOfBytesToUnlockLow,
                          nNumberOfBytesToUnlockHigh,
                          &Overlapped);
    if (!(Result) && (GetLastError() == ERROR_IO_PENDING))
    {
        /* Ex fails during STATUS_PENDING, handle that here by waiting */
        Status = NtWaitForSingleObject(hFile, FALSE, NULL);
        if (NT_SUCCESS(Status)) Status = Overlapped.Internal;

        /* Now if the status is successful, return */
        if (!NT_SUCCESS(Status)) return TRUE;

        /* Otherwise the asynchronous operation had a failure, so fail */
        BaseSetLastNTError(Status);
        return FALSE;
    }

    /* Success or error case -- Ex took care of the rest, just return */
    return Result;
}