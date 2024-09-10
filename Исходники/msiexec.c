static void ShowUsage(int ExitCode)
{
    WCHAR msiexec_version[40];
    WCHAR filename[MAX_PATH];
    LPWSTR msi_res;
    LPWSTR msiexec_help;
    HMODULE hmsi = GetModuleHandleA("msi.dll");
    DWORD len;
    DWORD res;

    /* MsiGetFileVersion need the full path */
    *filename = 0;
    res = GetModuleFileNameW(hmsi, filename, sizeof(filename) / sizeof(filename[0]));
    if (!res)
        WINE_ERR("GetModuleFileName failed: %d\n", GetLastError());

    len = sizeof(msiexec_version) / sizeof(msiexec_version[0]);
    *msiexec_version = 0;
    res = MsiGetFileVersionW(filename, msiexec_version, &len, NULL, NULL);
    if (res)
        WINE_ERR("MsiGetFileVersion failed with %d\n", res);

    /* Return the length of the resource.
       No typo: The LPWSTR parameter must be a LPWSTR * for this mode */
    len = LoadStringW(hmsi, 10, (LPWSTR) &msi_res, 0);

    msi_res = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR));
    msiexec_help = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR) + sizeof(msiexec_version));
    if (msi_res && msiexec_help) {
        *msi_res = 0;
        LoadStringW(hmsi, 10, msi_res, len + 1);

        sprintfW(msiexec_help, msi_res, msiexec_version);
        MsiMessageBoxW(0, msiexec_help, NULL, 0, GetUserDefaultLangID(), 0);
    }
    HeapFree(GetProcessHeap(), 0, msi_res);
    HeapFree(GetProcessHeap(), 0, msiexec_help);
    ExitProcess(ExitCode);
}