PRBool NTStatsServer::createStatsChannel(void)
{
    HANDLE hPipe = createPipe();
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        return PR_FALSE;
    }
    HANDLE hEvent = CreateEvent(NULL,   // Security descriptor
                                TRUE,   // Manual Rest
                                TRUE,   // Initially Signaled state
                                NULL);  // Unnamed
    if (hEvent == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hPipe);
        return PR_FALSE;
    }
    if (addPollItem(hPipe, hEvent) != PR_TRUE)
    {
        CloseHandle(hPipe);
        CloseHandle(hEvent);
        return PR_FALSE;
    }
    int nIndex = nPollItems_ - 1;
    if (connectPipe(nIndex) == PR_FALSE)
    {
        return PR_FALSE;
    }
    return PR_TRUE;
}