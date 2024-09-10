BOOL SysvolWriteOwner(
    _In_ HANDLE hOutfile,
    _In_ PTCHAR ptPath,
    _In_ PTCHAR ptDnSlave,
    _In_ PTCHAR ptKeyword
    ) {
    BOOL bResult = FALSE;
    DWORD dwResult = 0;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    PSECURITY_DESCRIPTOR pSd = NULL;

    hFile = FileOpenWithBackupPriv(ptPath, sSysvolOptions.bUseBackupPriv);
    if (hFile == INVALID_HANDLE_VALUE) {
        LOG(Err, _T("Cannot open file <%s> : <%u>"), ptPath, GetLastError());
        return FALSE;
    }

    dwResult = GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, NULL, NULL, NULL, NULL, &pSd);
    if (dwResult != ERROR_SUCCESS) {
        LOG(Err, _T("Cannot get security information for <%s> : <%u>"), ptPath, dwResult);
        return FALSE;
    }

    bResult = ControlWriteOwnerOutline(hOutfile, pSd, ptDnSlave, ptKeyword);
    if (!bResult) {
        LOG(Err, _T("Cannot write owner control relation for <%s>"), ptDnSlave);
        return FALSE;
    }

    return TRUE;
}