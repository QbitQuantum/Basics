/*++
Function:
  GetFileTime

Notes: As noted at the top of this file, there is no analog to "creation
time" on Unix systems, so the inode change time is used instead. Also, Win32
LastAccessTime is updated after a write operation, but it is not on Unix.
To be consistent with Win32, this function returns the greater of mtime and
atime for LastAccessTime.
--*/
BOOL
PALAPI
GetFileTime(
        IN HANDLE hFile,
        OUT LPFILETIME lpCreationTime,
        OUT LPFILETIME lpLastAccessTime,
        OUT LPFILETIME lpLastWriteTime)
{
    CPalThread *pThread;
    PAL_ERROR palError = NO_ERROR;

    PERF_ENTRY(GetFileTime);
    ENTRY("GetFileTime(hFile=%p, lpCreationTime=%p, lpLastAccessTime=%p, "
          "lpLastWriteTime=%p)\n",
          hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime);

    pThread = InternalGetCurrentThread();

    palError = InternalGetFileTime(
        pThread,
        hFile,
        lpCreationTime,
        lpLastAccessTime,
        lpLastWriteTime
        );

    if (NO_ERROR != palError)
    {
        pThread->SetLastError(palError);
    }

    LOGEXIT("GetFileTime returns BOOL %s\n", NO_ERROR == palError ? "TRUE":"FALSE");
    PERF_EXIT(GetFileTime);
    return NO_ERROR == palError;
}