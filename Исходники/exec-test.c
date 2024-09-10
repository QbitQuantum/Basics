static void exec_dotest(ULONG Flags, PWSTR Prefix, ULONG FileInfoTimeout)
{
    void *memfs = memfs_start_ex(Flags, FileInfoTimeout);

    WCHAR FilePath[MAX_PATH];
    HANDLE Process;

    StringCbPrintfW(FilePath, sizeof FilePath, L"%s%s\\helper.exe",
        Prefix ? L"" : L"\\\\?\\GLOBALROOT", Prefix ? Prefix : memfs_volumename(memfs));

    ExecHelper(FilePath, 0, &Process);
    WaitHelper(Process, 0);

    ASSERT(DeleteFileW(FilePath));

    memfs_stop(memfs);
}