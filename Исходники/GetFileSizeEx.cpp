void CheckFileSize(HANDLE hFile, DWORD dwOffset, DWORD dwHighOrder)
{
    DWORD dwRc = 0;
    DWORD dwError = 0;
    LARGE_INTEGER qwFileSize;

    dwRc = SetFilePointer(hFile, dwOffset, (PLONG)&dwHighOrder, FILE_BEGIN);
    if (dwRc == INVALID_SET_FILE_POINTER)
    {
        Trace("GetFileSizeEx: ERROR -> Call to SetFilePointer failed with %ld.\n", 
            GetLastError());
        CleanUp(hFile);
        Fail("");
    }
    else
    {
        if (!SetEndOfFile(hFile))
        {
            dwError = GetLastError();
            CleanUp(hFile);
            if (dwError == 112)
            {
                Fail("GetFileSizeEx: ERROR -> SetEndOfFile failed due to lack of "
                    "disk space\n");
            }
            else
            {
                Fail("GetFileSizeEx: ERROR -> SetEndOfFile call failed "
                    "with error %ld\n", dwError);
            }
        }
        else
        {
            GetFileSizeEx(hFile, &qwFileSize);
            if ((qwFileSize.u.LowPart != dwOffset) || 
                (qwFileSize.u.HighPart != dwHighOrder))
            {
                CleanUp(hFile);
                Fail("GetFileSizeEx: ERROR -> File sizes do not match up.\n");
            }
        }
    }
}