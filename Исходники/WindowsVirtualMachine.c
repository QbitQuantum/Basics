/*
 * Attempts to enable the SE_DEBUG_NAME privilege and open the given process.
 */
static HANDLE
doPrivilegedOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId) {
    HANDLE hToken;
    HANDLE hProcess = NULL;
    LUID luid;
    TOKEN_PRIVILEGES tp, tpPrevious;
    DWORD retLength, error;

    /*
     * Get the access token
     */
    if (!OpenThreadToken(GetCurrentThread(),
                         TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
                         FALSE,
                         &hToken)) {
        if (GetLastError() != ERROR_NO_TOKEN) {
            return (HANDLE)NULL;
        }

        /*
         * No access token for the thread so impersonate the security context
         * of the process.
         */
        if (!ImpersonateSelf(SecurityImpersonation)) {
            return (HANDLE)NULL;
        }
        if (!OpenThreadToken(GetCurrentThread(),
                             TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
                             FALSE,
                             &hToken)) {
            return (HANDLE)NULL;
        }
    }

    /*
     * Get LUID for the privilege
     */
    if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        error = GetLastError();
        CloseHandle(hToken);
        SetLastError(error);
        return (HANDLE)NULL;
    }

    /*
     * Enable the privilege
     */
    ZeroMemory(&tp, sizeof(tp));
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;

    error = 0;
    if (AdjustTokenPrivileges(hToken,
                              FALSE,
                              &tp,
                              sizeof(TOKEN_PRIVILEGES),
                              &tpPrevious,
                              &retLength)) {
        /*
         * If we enabled the privilege then attempt to open the
         * process.
         */
        if (GetLastError() == ERROR_SUCCESS) {
            hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
            if (hProcess == NULL) {
                error = GetLastError();
            }
        } else {
            error = ERROR_ACCESS_DENIED;
        }

        /*
         * Revert to the previous privileges
         */
        AdjustTokenPrivileges(hToken,
                              FALSE,
                              &tpPrevious,
                              retLength,
                              NULL,
                              NULL);
    } else {
        error = GetLastError();
    }


    /*
     * Close token and restore error
     */
    CloseHandle(hToken);
    SetLastError(error);

    return hProcess;
}