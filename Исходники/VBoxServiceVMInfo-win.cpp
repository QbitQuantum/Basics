/**
 * Detects whether a user is logged on.
 *
 * @returns true if logged in, false if not (or error).
 * @param   pUserInfo           Where to return the user information.
 * @param   pSession            The session to check.
 */
bool VBoxServiceVMInfoWinIsLoggedIn(PVBOXSERVICEVMINFOUSER pUserInfo, PLUID pSession)
{
    AssertPtrReturn(pUserInfo, false);
    if (!pSession)
        return false;

    PSECURITY_LOGON_SESSION_DATA pSessionData = NULL;
    NTSTATUS rcNt = LsaGetLogonSessionData(pSession, &pSessionData);
    if (rcNt != STATUS_SUCCESS)
    {
        ULONG ulError = LsaNtStatusToWinError(rcNt);
        switch (ulError)
        {
            case ERROR_NOT_ENOUGH_MEMORY:
                /* If we don't have enough memory it's hard to judge whether the specified user
                 * is logged in or not, so just assume he/she's not. */
                VBoxServiceVerbose(3, "Not enough memory to retrieve logon session data!\n");
                break;

            case ERROR_NO_SUCH_LOGON_SESSION:
                /* Skip session data which is not valid anymore because it may have been
                 * already terminated. */
                break;

            default:
                VBoxServiceError("LsaGetLogonSessionData failed with error %u\n", ulError);
                break;
        }
        if (pSessionData)
            LsaFreeReturnBuffer(pSessionData);
        return false;
    }
    if (!pSessionData)
    {
        VBoxServiceError("Invalid logon session data!\n");
        return false;
    }

    VBoxServiceVerbose(3, "Session data: Name=%ls, Session=%u, LogonID=%ld,%ld, LogonType=%ld\n",
                       pSessionData->UserName.Buffer,
                       pSessionData->Session,
                       pSessionData->LogonId.HighPart, pSessionData->LogonId.LowPart,
                       pSessionData->LogonType);

    /*
     * Only handle users which can login interactively or logged in
     * remotely over native RDP.
     */
    bool fFoundUser = false;
    DWORD dwErr = NO_ERROR;
    if (   IsValidSid(pSessionData->Sid)
        && (   (SECURITY_LOGON_TYPE)pSessionData->LogonType == Interactive
            || (SECURITY_LOGON_TYPE)pSessionData->LogonType == RemoteInteractive
            /* Note: We also need CachedInteractive in case Windows cached the credentials
             *       or just wants to reuse them! */
            || (SECURITY_LOGON_TYPE)pSessionData->LogonType == CachedInteractive))
    {
        VBoxServiceVerbose(3, "Session LogonType=%ld is supported -- looking up SID + type ...\n",
                           pSessionData->LogonType);

        /*
         * Copy out relevant data.
         */
        VBoxServiceVMInfoWinSafeCopy(pUserInfo->wszUser, sizeof(pUserInfo->wszUser),
                                     &pSessionData->UserName, "User name");
        VBoxServiceVMInfoWinSafeCopy(pUserInfo->wszAuthenticationPackage, sizeof(pUserInfo->wszAuthenticationPackage),
                                     &pSessionData->AuthenticationPackage, "Authentication pkg name");
        VBoxServiceVMInfoWinSafeCopy(pUserInfo->wszLogonDomain, sizeof(pUserInfo->wszLogonDomain),
                                     &pSessionData->LogonDomain, "Logon domain name");

        TCHAR           szOwnerName[_MAX_PATH]  = { 0 };
        DWORD           dwOwnerNameSize         = sizeof(szOwnerName);
        TCHAR           szDomainName[_MAX_PATH] = { 0 };
        DWORD           dwDomainNameSize        = sizeof(szDomainName);
        SID_NAME_USE    enmOwnerType            = SidTypeInvalid;
        if (!LookupAccountSid(NULL,
                              pSessionData->Sid,
                              szOwnerName,
                              &dwOwnerNameSize,
                              szDomainName,
                              &dwDomainNameSize,
                              &enmOwnerType))
        {
            DWORD dwErr = GetLastError();
            /*
             * If a network time-out prevents the function from finding the name or
             * if a SID that does not have a corresponding account name (such as a
             * logon SID that identifies a logon session), we get ERROR_NONE_MAPPED
             * here that we just skip.
             */
            if (dwErr != ERROR_NONE_MAPPED)
                VBoxServiceError("Failed looking up account info for user=%ls, error=$ld!\n",
                                 pUserInfo->wszUser, dwErr);
        }
        else
        {
            if (enmOwnerType == SidTypeUser) /* Only recognize users; we don't care about the rest! */
            {
                VBoxServiceVerbose(3, "Account User=%ls, Session=%ld, LogonID=%ld,%ld, AuthPkg=%ls, Domain=%ls\n",
                                   pUserInfo->wszUser, pSessionData->Session, pSessionData->LogonId.HighPart,
                                   pSessionData->LogonId.LowPart, pUserInfo->wszAuthenticationPackage,
                                   pUserInfo->wszLogonDomain);

                /* Detect RDP sessions as well. */
                LPTSTR  pBuffer = NULL;
                DWORD   cbRet   = 0;
                int     iState  = -1;
                if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE,
                                               pSessionData->Session,
                                               WTSConnectState,
                                               &pBuffer,
                                               &cbRet))
                {
                    if (cbRet)
                        iState = *pBuffer;
                    VBoxServiceVerbose(3, "Account User=%ls, WTSConnectState=%d (%ld)\n",
                                       pUserInfo->wszUser, iState, cbRet);
                    if (    iState == WTSActive           /* User logged on to WinStation. */
                         || iState == WTSShadow           /* Shadowing another WinStation. */
                         || iState == WTSDisconnected)    /* WinStation logged on without client. */
                    {
                        /** @todo On Vista and W2K, always "old" user name are still
                         *        there. Filter out the old one! */
                        VBoxServiceVerbose(3, "Account User=%ls using TCS/RDP, state=%d \n",
                                           pUserInfo->wszUser, iState);
                        fFoundUser = true;
                    }
                    if (pBuffer)
                        WTSFreeMemory(pBuffer);
                }
                else
                {
                    DWORD dwLastErr = GetLastError();
                    switch (dwLastErr)
                    {
                        /*
                         * Terminal services don't run (for example in W2K,
                         * nothing to worry about ...).  ... or is on the Vista
                         * fast user switching page!
                         */
                        case ERROR_CTX_WINSTATION_NOT_FOUND:
                            VBoxServiceVerbose(3, "No WinStation found for user=%ls\n",
                                               pUserInfo->wszUser);
                            break;

                        default:
                            VBoxServiceVerbose(3, "Cannot query WTS connection state for user=%ls, error=%ld\n",
                                               pUserInfo->wszUser, dwLastErr);
                            break;
                    }

                    fFoundUser = true;
                }
            }
            else
                VBoxServiceVerbose(3, "SID owner type=%d not handled, skipping\n",
                                   enmOwnerType);
        }

        VBoxServiceVerbose(3, "Account User=%ls %s logged in\n",
                           pUserInfo->wszUser, fFoundUser ? "is" : "is not");
    }

    LsaFreeReturnBuffer(pSessionData);
    return fFoundUser;
}