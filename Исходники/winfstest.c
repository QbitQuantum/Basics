static int do_SetEndOfFile(int argc, wchar_t **argv)
{
    if (argc != 3)
        fail("usage: SetEndOfFile FileName Length");
    HANDLE h = CreateFileW(argv[1],
        GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        0, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, 0);
    if (INVALID_HANDLE_VALUE == h)
        errprint(0);
    else
    {
        FILE_END_OF_FILE_INFO EofInfo;
        EofInfo.EndOfFile.QuadPart = wcstoull(argv[2], 0, 0);
        BOOL r = SetFileInformationByHandle(h, FileEndOfFileInfo, &EofInfo, sizeof EofInfo);
        errprint(r);
        CloseHandle(h);
    }
    return 0;
}