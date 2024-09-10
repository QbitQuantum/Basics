/**
 * Connects to VBoxTray IPC under the behalf of the user running
 * in the current thread context.
 *
 * @return  IPRT status code.
 * @param   phSession               Where to store the IPC session.
 */
static int vboxConnectToVBoxTray(RTLOCALIPCSESSION *phSession)
{
    int rc = VINF_SUCCESS;

    RTUTF16 wszUserName[255];
    DWORD cchUserName = sizeof(wszUserName) / sizeof(RTUTF16);
    BOOL fRc = GetUserNameW(wszUserName, &cchUserName);
    if (!fRc)
        rc = RTErrConvertFromWin32(GetLastError());

    if (RT_SUCCESS(rc))
    {
        char *pszUserName;
        rc = RTUtf16ToUtf8(wszUserName, &pszUserName);
        if (RT_SUCCESS(rc))
        {
            char szPipeName[255];
            if (RTStrPrintf(szPipeName, sizeof(szPipeName), "%s%s",
                            VBOXTRAY_IPC_PIPE_PREFIX, pszUserName))
            {
                rc = RTLocalIpcSessionConnect(phSession, szPipeName, 0 /* Flags */);
            }
            else
                rc = VERR_NO_MEMORY;

            RTStrFree(pszUserName);
        }
    }

    return rc;
}