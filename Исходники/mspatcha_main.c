/*****************************************************
 *    GetFilePatchSignatureA (MSPATCHA.7)
 */
BOOL WINAPI GetFilePatchSignatureA(LPCSTR filename, ULONG flags, PVOID data, ULONG ignore_range_count,
                                   PPATCH_IGNORE_RANGE ignore_range, ULONG retain_range_count,
                                   PPATCH_RETAIN_RANGE retain_range, ULONG bufsize, PVOID buffer)
{
    BOOL ret = FALSE;
    HANDLE hFile;

    hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        ret = GetFilePatchSignatureByHandle(hFile, flags, data, ignore_range_count, ignore_range,
                                            retain_range_count, retain_range, bufsize, buffer);
        CloseHandle(hFile);
    }

    return ret;
}