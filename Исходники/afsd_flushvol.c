BOOL
afsd_ServicePerformFlushVolumes()
{
    CONST CHAR	COLON = ':';
    CONST CHAR	SLASH = '\\';
    CONST DWORD	NETRESBUFSIZE = 16384;
    CHAR	bufMessage[1024];
    UINT	i;
    DWORD	dwServerSize;
    DWORD	dwRet;
    DWORD	dwCount;
    DWORD	dwNetResBufSize;
    DWORD	dwTotalVols = 0;
    DWORD	dwVolBegin, dwVolEnd;
    DWORD	dwFlushBegin, dwFlushEnd;
    HANDLE	hEnum;
    LPNETRESOURCE	lpNetResBuf, lpnr;
    char        *pszShareName, *pc;
    afs_int32	afsRet = 0;

    if (cm_noIPAddr == 0) {
        // Nothing to do if we only have a loopback interface
        return TRUE;
    }

    // Determine the root share name (\\AFS\ALL or \\<machine>-AFS\ALL),
    // and the length of the server name prefix.
    pszShareName = smb_GetSharename();
    if (pszShareName == NULL)
    {
        LogEvent(EVENTLOG_ERROR_TYPE, MSG_FLUSH_NO_SHARE_NAME, NULL);
        return FALSE;
    }
    pc = strrchr(pszShareName, SLASH);
    if ((pc == NULL) || ((dwServerSize = (DWORD)(pc - pszShareName)) < 3))
    {
        LogEvent(EVENTLOG_ERROR_TYPE, MSG_FLUSH_BAD_SHARE_NAME,
                  pszShareName, NULL);
        free(pszShareName);
        return FALSE;
    }

    // Allocate a buffer to hold network resources returned by
    // WNetEnumResource().
    lpNetResBuf = malloc(NETRESBUFSIZE);
    if (lpNetResBuf == NULL)
    {
        // Out of memory, give up now.
        LogEvent(EVENTLOG_ERROR_TYPE, MSG_FLUSH_NO_MEMORY, NULL);
        free(pszShareName);
        return FALSE;
    }

    // Initialize the flush timer.  Note that GetTickCount() returns
    // the number of milliseconds since the system started, in a DWORD,
    // so that the value wraps around every 49.7 days.  We do not bother
    // to handle the case where the flush elapsed time is greater than
    // that.
    dwFlushBegin = GetTickCount();

    dwRet = WNetOpenEnum(RESOURCE_CONNECTED, RESOURCETYPE_ANY, 0, NULL,
                          &hEnum);
    if (dwRet != NO_ERROR)
    {
        LogEventMessage(EVENTLOG_ERROR_TYPE, MSG_FLUSH_OPEN_ENUM_ERROR,
                         dwRet);
        free(pszShareName);
        return FALSE;
    }

    // Loop to enumerate network resources, and flush those associated
    // with AFS volumes.
    while (1)
    {
        dwCount = -1;
        memset(lpNetResBuf, 0, NETRESBUFSIZE);
        dwNetResBufSize = NETRESBUFSIZE;
        dwRet = WNetEnumResource(hEnum, &dwCount,
                                  lpNetResBuf, &dwNetResBufSize);
        if (dwRet != NO_ERROR)
            break;
        // Iterate over the returned network resources.
        for (i = 0, lpnr = lpNetResBuf; i < dwCount; i++, lpnr++)
        {
            // Ensure resource has a remote name, and is connected.
            if ((lpnr->lpRemoteName == NULL) ||
                 (lpnr->dwScope != RESOURCE_CONNECTED))
                continue;
            if ((_strnicmp(lpnr->lpRemoteName, pszShareName,
                            dwServerSize) == 0) &&
                 (lpnr->lpRemoteName[dwServerSize] == SLASH))
            {
                // got one!
                // but we don't want to flush '\\[...]afs\all'
                if (cm_stricmp_utf8(lpnr->lpRemoteName, pszShareName) == 0)
                    continue;
                ++dwTotalVols;

                dwVolBegin = GetTickCount();
                afsRet = afsd_ServicePerformFlushVolumeCmd(lpnr->lpRemoteName);
                dwVolEnd = GetTickCount();
                if (afsRet == 0)
                {
                    LogTimingEvent(MSG_TIME_FLUSH_PER_VOLUME,
                                    lpnr->lpRemoteName,
                                    dwVolEnd - dwVolBegin);
                }
                else
                {
                    LogEvent(EVENTLOG_WARNING_TYPE,
                              MSG_FLUSH_FAILED,
                              lpnr->lpRemoteName, NULL);
                }
            }
        }
    }
    WNetCloseEnum(hEnum);
    free(lpNetResBuf);
    free(pszShareName);
    if (dwRet != ERROR_NO_MORE_ITEMS)
    {
        LogEventMessage(EVENTLOG_ERROR_TYPE, MSG_FLUSH_ENUM_ERROR,
                         dwRet);
        return FALSE;
    }

    dwFlushEnd = GetTickCount();

    // display total volume count in Event Logger
    sprintf(bufMessage, "%d", dwTotalVols);
    LogTimingEvent(MSG_TIME_FLUSH_TOTAL, bufMessage,
                    dwFlushEnd - dwFlushBegin);

    return TRUE;
}