HRESULT VBoxDrvCfgDrvUpdate(LPCWSTR pcszwHwId, LPCWSTR pcsxwInf, BOOL *pbRebootRequired)
{
    if (pbRebootRequired)
        *pbRebootRequired = FALSE;
    BOOL bRebootRequired = FALSE;
    WCHAR InfFullPath[MAX_PATH];
    DWORD dwChars = GetFullPathNameW(pcsxwInf,
            sizeof (InfFullPath) / sizeof (InfFullPath[0]),
            InfFullPath,
            NULL /* LPTSTR *lpFilePart */
            );
    if (!dwChars || dwChars >= MAX_PATH)
    {
        NonStandardLogCrap(("GetFullPathNameW failed, dwErr=%ld, dwChars=%ld\n",
                            GetLastError(), dwChars));
        return E_INVALIDARG;
    }


    if (!UpdateDriverForPlugAndPlayDevicesW(NULL, /* HWND hwndParent */
            pcszwHwId,
            InfFullPath,
            INSTALLFLAG_FORCE,
            &bRebootRequired))
    {
        DWORD dwErr = GetLastError();
        NonStandardLogCrap(("UpdateDriverForPlugAndPlayDevicesW failed, dwErr=%ld\n",
                            dwErr));
        return HRESULT_FROM_WIN32(dwErr);
    }


    if (bRebootRequired)
        NonStandardLogCrap(("!!Driver Update: REBOOT REQUIRED!!\n", GetLastError(), dwChars));

    if (pbRebootRequired)
        *pbRebootRequired = bRebootRequired;

    return S_OK;
}