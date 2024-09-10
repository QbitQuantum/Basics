static VOID ModifyStatus(VOID)
{
    LONG Ret;
    DWORD GlobalFlags;
    HKEY IFEOKey;
    WCHAR Buffer[11];

    if (!OpenImageFileExecOptions(KEY_WRITE | KEY_READ, Image, &IFEOKey))
    {
        return;
    }

    GlobalFlags = ReadSZFlagsFromRegistry(IFEOKey, L"GlobalFlag");
    if (Set)
    {
        GlobalFlags |= FLG_HEAP_PAGE_ALLOCS;
    }
    else
    {
        GlobalFlags &= ~FLG_HEAP_PAGE_ALLOCS;
    }

    if (GlobalFlags != 0)
    {
        wsprintf(Buffer, L"0x%08x", GlobalFlags);
        Ret = RegSetValueExW(IFEOKey, L"GlobalFlag", 0, REG_SZ, (BYTE*)Buffer, (wcslen(Buffer) + 1) * sizeof(WCHAR));
        if (Ret != ERROR_SUCCESS)
        {
            wprintf(L"MS: RegSetValueEx failed (%d)\n", Ret);
        }
    }
    else
    {
        Ret = RegDeleteValueW(IFEOKey, L"GlobalFlag");
        if (Ret != ERROR_SUCCESS)
        {
            wprintf(L"MS: RegDeleteValue failed (%d)\n", Ret);
        }
    }

    if (Unset)
    {
        Ret = RegDeleteValueW(IFEOKey, L"PageHeapFlags");
        if (Ret != ERROR_SUCCESS)
        {
            wprintf(L"MS: RegDeleteValue failed (%d)\n", Ret);
        }
    }
    else
    {
        DWORD PageHeapFlags;

        PageHeapFlags = ReadSZFlagsFromRegistry(IFEOKey, L"PageHeapFlags");
        PageHeapFlags &= ~3;

        if (Full)
        {
            PageHeapFlags |= 1;
        }
        PageHeapFlags |= 2;

        wsprintf(Buffer, L"0x%x", PageHeapFlags);
        Ret = RegSetValueExW(IFEOKey, L"PageHeapFlags", 0, REG_SZ, (BYTE*)Buffer, (wcslen(Buffer) + 1) * sizeof(WCHAR));
        if (Ret != ERROR_SUCCESS)
        {
            wprintf(L"MS: RegSetValueEx failed (%d)\n", Ret);
        }
    }

    if (Set)
    {
        DWORD Type, VerifierFlags, Len;

        VerifierFlags = 0;
        Len = VerifierFlags;
        if (RegQueryValueExW(IFEOKey, L"VerifierFlags", NULL, &Type, (BYTE *)&VerifierFlags, &Len) == ERROR_SUCCESS &&
            Type == REG_DWORD && Len == sizeof(DWORD))
        {
            VerifierFlags &= ~0x8001;   /* RTL_VRF_FLG_FAST_FILL_HEAP | RTL_VRF_FLG_FULL_PAGE_HEAP */
        }
        else
        {
            VerifierFlags = 0;
        }

        if (Full)
        {
            VerifierFlags |= 1; /* RTL_VRF_FLG_FULL_PAGE_HEAP */
        }
        else
        {
            VerifierFlags |= 0x8000;    /* RTL_VRF_FLG_FAST_FILL_HEAP */
        }

        Ret = RegSetValueExW(IFEOKey, L"VerifierFlags", 0, REG_DWORD, (const BYTE *)&VerifierFlags, sizeof(DWORD));
        if (Ret != ERROR_SUCCESS)
        {
            wprintf(L"MS: RegSetValueEx failed (%d)\n", Ret);
        }
    }

    wprintf(L"path: %s\n", ImageExecOptionsString);
    wprintf(L"\t%s: page heap %s\n", Image, (Set ? L"enabled" : L"disabled"));

    HeapFree(GetProcessHeap(), 0, Buffer);
    RegCloseKey(IFEOKey);
}