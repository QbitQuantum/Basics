/*
 * @implemented
 */
long
WINAPI
_hwrite(HFILE hFile, LPCSTR lpBuffer, long lBytes)
{
    DWORD NumberOfBytesWritten;

    if (lBytes == 0)
    {
        if (!SetEndOfFile((HANDLE) hFile))
        {
            return HFILE_ERROR;
        }
        return 0;
    }
    if (!WriteFile(LongToHandle(hFile),
                   (LPVOID) lpBuffer,
                   (DWORD) lBytes,
                   &NumberOfBytesWritten,
                   NULL))
    {
        return HFILE_ERROR;
    }
    return NumberOfBytesWritten;
}