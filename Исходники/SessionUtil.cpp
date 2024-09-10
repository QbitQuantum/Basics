int findSession(TCHAR *userToFind)
{
    int sessionId = -1;

    WTS_SESSION_INFO *sessions; 
    DWORD count;
    if (!WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessions, &count))
    {
        printError(L"WTSEnumerateSessions failed: %s\n");
        return -1;
    }

    for (DWORD i = 0; i < count; i++)
    {
        WCHAR *sessionUser; 
        DWORD bytes;
        if (!WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessions[i].SessionId, WTSUserName, &sessionUser, &bytes))
        {
            printError(L"WTSQuerySessionInformation error: %s\n");
            continue;
        }

#if DEBUG
        wprintf(L"  * Session %d: \n      user: %s\n      state: %d\n      name: %s\n", 
            sessions[i].SessionId, 
            sessionUser, 
            sessions[i].State, 
            sessions[i].pWinStationName);
#endif

        if (sessionUser != NULL && _wcsicmp(userToFind, sessionUser) == 0)
            sessionId = sessions[i].SessionId;

        WTSFreeMemory(sessionUser);

        if (sessionId != -1)
            break;
    }
    WTSFreeMemory(sessions);

    return sessionId;
}