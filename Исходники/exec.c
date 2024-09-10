HANDLE GetLoggedOnUserToken(
    OUT PWCHAR userName,
    IN  DWORD cchUserName // at least UNLEN WCHARs
    )
{
    DWORD consoleSessionId;
    HANDLE userToken, duplicateToken;
    DWORD nameSize = UNLEN;

    consoleSessionId = WTSGetActiveConsoleSessionId();
    if (0xFFFFFFFF == consoleSessionId)
    {
        LogWarning("no active console session");
        return NULL;
    }

    if (!WTSQueryUserToken(consoleSessionId, &userToken))
    {
        LogDebug("no user is logged on");
        return NULL;
    }

    // create a primary token (needed for logon)
    if (!DuplicateTokenEx(
        userToken,
        MAXIMUM_ALLOWED,
        NULL,
        SecurityIdentification,
        TokenPrimary,
        &duplicateToken))
    {
        perror("DuplicateTokenEx");
        CloseHandle(userToken);
        return NULL;
    }

    CloseHandle(userToken);

    if (!ImpersonateLoggedOnUser(duplicateToken))
    {
        perror("ImpersonateLoggedOnUser");
        CloseHandle(duplicateToken);
        return NULL;
    }

    if (!GetUserName(userName, &cchUserName))
    {
        perror("GetUserName");
        userName[0] = 0;
    }

    RevertToSelf();

    return duplicateToken;
}