static void file_list_single_test(void)
{
    HANDLE Handle;
    BOOL Success;
    WCHAR FileName[MAX_PATH];
    WIN32_FIND_DATAW FindData;

    for (ULONG ListIndex = 0; OptListCount > ListIndex; ListIndex++)
        for (ULONG Index = 0; OptFileCount > Index; Index++)
        {
            StringCbPrintfW(FileName, sizeof FileName, L"fsbench-file%lu", Index);
            Handle = FindFirstFileW(FileName, &FindData);
            ASSERT(INVALID_HANDLE_VALUE != Handle);
            do
            {
            } while (FindNextFileW(Handle, &FindData));
            Success = FindClose(Handle);
            ASSERT(Success);
        }
}