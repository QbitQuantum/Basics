RTDECL(int) RTSystemShutdown(RTMSINTERVAL cMsDelay, uint32_t fFlags, const char *pszLogMsg)
{
    AssertPtrReturn(pszLogMsg, VERR_INVALID_POINTER);
    AssertReturn(!(fFlags & ~RTSYSTEM_SHUTDOWN_VALID_MASK), VERR_INVALID_PARAMETER);

    PRTUTF16 pwszLogMsg;
    int rc = RTStrToUtf16(pszLogMsg, &pwszLogMsg);
    if (RT_FAILURE(rc))
        return rc;
    DWORD cSecsTimeout = (cMsDelay + 499) / 1000;
    BOOL  fRebootAfterShutdown = (fFlags & RTSYSTEM_SHUTDOWN_ACTION_MASK) == RTSYSTEM_SHUTDOWN_REBOOT
                               ? TRUE : FALSE;
    BOOL  fForceAppsClosed = fFlags & RTSYSTEM_SHUTDOWN_FORCE ? TRUE : FALSE;

    /*
     * Do the
     */
    if (InitiateSystemShutdownW(NULL /*pwszMachineName = NULL = localhost*/,
                                pwszLogMsg,
                                cSecsTimeout,
                                fForceAppsClosed,
                                fRebootAfterShutdown))
        rc = (fFlags & RTSYSTEM_SHUTDOWN_ACTION_MASK) == RTSYSTEM_SHUTDOWN_HALT ? VINF_SYS_MAY_POWER_OFF : VINF_SUCCESS;
    else
    {
        /* If we failed because of missing privileges, try get the right to
           shut down the system and call the api again. */
        DWORD dwErr = GetLastError();
        rc = RTErrConvertFromWin32(dwErr);
        if (dwErr == ERROR_ACCESS_DENIED)
        {
            HANDLE hToken = NULL;
            if (OpenThreadToken(GetCurrentThread(),
                                TOKEN_ADJUST_PRIVILEGES,
                                TRUE /*OpenAsSelf*/,
                                &hToken))
                dwErr = NO_ERROR;
            else
            {
                dwErr  = GetLastError();
                if (dwErr == ERROR_NO_TOKEN)
                {
                    if (OpenProcessToken(GetCurrentProcess(),
                                         TOKEN_ADJUST_PRIVILEGES,
                                         &hToken))
                        dwErr = NO_ERROR;
                    else
                        dwErr = GetLastError();
                }
            }

            if (dwErr == NO_ERROR)
            {
                union
                {
                    TOKEN_PRIVILEGES TokenPriv;
                    char ab[sizeof(TOKEN_PRIVILEGES) + sizeof(LUID_AND_ATTRIBUTES)];
                } u;
                u.TokenPriv.PrivilegeCount = 1;
                u.TokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                if (LookupPrivilegeValue(NULL /*localhost*/, SE_SHUTDOWN_NAME, &u.TokenPriv.Privileges[0].Luid))
                {
                    if (AdjustTokenPrivileges(hToken,
                                              FALSE /*DisableAllPrivileges*/,
                                              &u.TokenPriv,
                                              RT_OFFSETOF(TOKEN_PRIVILEGES, Privileges[1]),
                                              NULL,
                                              NULL) )
                    {
                        if (InitiateSystemShutdownW(NULL /*pwszMachineName = NULL = localhost*/,
                                                    pwszLogMsg,
                                                    cSecsTimeout,
                                                    fForceAppsClosed,
                                                    fRebootAfterShutdown))
                            rc = (fFlags & RTSYSTEM_SHUTDOWN_ACTION_MASK) == RTSYSTEM_SHUTDOWN_HALT ? VINF_SYS_MAY_POWER_OFF : VINF_SUCCESS;
                        else
                        {
                            dwErr = GetLastError();
                            rc = RTErrConvertFromWin32(dwErr);
                        }
                    }
                    CloseHandle(hToken);
                }
            }
        }
    }

    RTUtf16Free(pwszLogMsg);
    return rc;
}