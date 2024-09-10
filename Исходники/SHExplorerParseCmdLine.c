static
VOID
TestCommandLine(
    _In_ INT ExpectedRet,
    _In_ INT ExpectedCsidl,
    _In_ DWORD ExpectedFlags,
    _In_ PCWSTR ExpectedFileName,
    _In_ PCWSTR PidlPath)
{
    EXPLORER_INFO Info;
    PVOID Ret;
    ULONG i;

    FillMemory(&Info, sizeof(Info), 0x55);
    Info.dwFlags = 0x00000000;
    Ret = SHExplorerParseCmdLine(&Info);

    if (ExpectedRet == -1)
        ok(Ret == Info.pidl, "Ret = %p, expected %p\n", Ret, Info.pidl);
    else
        ok(Ret == (PVOID)ExpectedRet, "Ret = %p, expected %p\n", Ret, (PVOID)ExpectedRet);

    if (ExpectedFileName == NULL)
        ok(Info.FileName == InvalidPointer, "FileName = %p\n", Info.FileName);
    else
    {
        ok(Info.FileName != NULL && Info.FileName != InvalidPointer, "FileName = %p\n", Info.FileName);
        if (Info.FileName != NULL && Info.FileName != InvalidPointer)
        {
            ok(!wcscmp(Info.FileName, ExpectedFileName), "FileName = %ls, expected %ls\n", Info.FileName, ExpectedFileName);
            LocalFree(Info.FileName);
        }
    }

    if (ExpectedCsidl == PIDL_IS_UNTOUCHED)
        ok(Info.pidl == InvalidPointer, "pidl = %p\n", Info.pidl);
    else if (ExpectedCsidl == PIDL_IS_NULL)
        ok(Info.pidl == NULL, "pidl = %p\n", Info.pidl);
    else
    {
        PIDLIST_ABSOLUTE ExpectedPidl;
        HRESULT hr;

        ok(Info.pidl != NULL, "pidl = %p\n", Info.pidl);
        if (Info.pidl != NULL && Info.pidl != InvalidPointer)
        {
            if (ExpectedCsidl == PIDL_IS_PATH)
            {
                ExpectedPidl = SHSimpleIDListFromPath(PidlPath);
                hr = ExpectedPidl == NULL ? E_FAIL : S_OK;
                ok(ExpectedPidl != NULL, "SHSimpleIDListFromPath failed\n");
            }
            else
            {
                hr = SHGetFolderLocation(NULL, ExpectedCsidl, NULL, 0, &ExpectedPidl);
                ok(hr == S_OK, "SHGetFolderLocation returned %08lx\n", hr);
            }
            if (SUCCEEDED(hr))
            {
                ok(ILIsEqual(Info.pidl, ExpectedPidl), "Unexpected pidl value\n");
                ILFree(ExpectedPidl);
            }
            ILFree(Info.pidl);
        }
    }

    ok(Info.dwFlags == ExpectedFlags, "dwFlags = %08lx, expected %08lx\n", Info.dwFlags, ExpectedFlags);
    for (i = 0; i < sizeof(Info.Unknown) / sizeof(Info.Unknown[0]); i++)
        ok(Info.Unknown[i] == 0x55555555, "Unknown[%lu] = %08lx\n", i, Info.Unknown[i]);
}