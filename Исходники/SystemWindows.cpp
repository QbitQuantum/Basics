Boolean System::isSystemUser(const char* userName)
{
    if (processUserName.size() == 0)
    {
        // Lock and recheck the processUserName length in case two threads
        // enter this block simultaneously
        AutoMutex mut(processUserNameMut);
        if (processUserName.size() == 0)
        {
            processUserName = getEffectiveUserName();
        }
    }
    if (processUserName == userName)
    {
      return true;
    }

    Boolean isSystemUser = false;

    char mUserName[UNLEN+1];
    char mDomainName[UNLEN+1];
    char tUserName[UNLEN+1];
    wchar_t wUserName[UNLEN+1];
    wchar_t wDomainName[UNLEN+1];
    char* pbs;
    bool usingDomain = false;

    LPBYTE pComputerName=NULL;
    DWORD dwLevel = 1;
    LPUSER_INFO_1 pUserInfo = NULL;
    NET_API_STATUS nStatus = NULL;

    // Make a copy of the specified username, it cannot be used directly
    // because it's declared as const and strchr() may modify the string.
    strncpy(tUserName, userName, sizeof(tUserName) - 1);
    tUserName[sizeof(tUserName)- 1] = '\0';

    //separate the domain and user name if both are present.
    if (NULL != (pbs = strchr(tUserName, '\\')))
    {
        *pbs = '\0';
        strcpy(mDomainName, tUserName);
        strcpy(mUserName, pbs+1);
        usingDomain = true;

    }
    else if ((NULL != (pbs = (strchr(tUserName, '@')))) ||
             (NULL != (pbs = (strchr(tUserName, '.')))))
    {
        *pbs = '\0';
        strcpy(mDomainName, pbs+1);
        strcpy(mUserName, tUserName);
        usingDomain = true;

    }
    else
    {
        strcpy(mDomainName, ".");
        strcpy(mUserName, tUserName);
    }

    //convert domain name to unicode
    if (!MultiByteToWideChar(
            CP_ACP, 0, mDomainName, -1, wDomainName,
            (int)(strlen(mDomainName) + 1)))
    {
        return false;
    }

    //convert username to unicode
    if (!MultiByteToWideChar(
            CP_ACP, 0, mUserName, -1, wUserName, (int)(strlen(mUserName) + 1)))
    {
        return false;
    }

    if (usingDomain)
    {
        //get domain controller
        DWORD rc = NetGetDCName(NULL, wDomainName, &pComputerName);
        if (rc == NERR_Success)
        {
            // this is automatically prefixed with "\\"
            wcscpy(wDomainName, (LPWSTR) pComputerName);
        }
        /*
        else
        {
            // failover
            // ATTN: This is commented out until there is resolution on
            // Bugzilla 2236. -hns 2/2005
            // This needs to be more thoroughly tested when we uncomment it out.

            PDOMAIN_CONTROLLER_INFO DomainControllerInfo = NULL;

            //this function does not take wide strings
            rc = DsGetDcName(NULL,
                             mDomainName,
                             NULL,
                             NULL,
                             //not sure what flags we want here
                             DS_DIRECTORY_SERVICE_REQUIRED,
                             &DomainControllerInfo);

            if (rc == ERROR_SUCCESS && DomainControllerInfo)
            {
                strcpy(mDomainName, DomainControllerInfo->DomainName);
                NetApiBufferFree(DomainControllerInfo);

                if (!MultiByteToWideChar(
                        CP_ACP, 0, mDomainName, -1, wDomainName,
                        strlen(mDomainName) + 1))
                {
                    return false;
                }
            }
        }
        */
    }

    //get user info
    nStatus = NetUserGetInfo(wDomainName,
                             wUserName,
                             dwLevel,
                             (LPBYTE *)&pUserInfo);

    if (nStatus == NERR_Success)
    {
        isSystemUser = true;
    }

    if (pComputerName != NULL)
    {
        NetApiBufferFree(pComputerName);
    }

    if (pUserInfo != NULL)
    {
        NetApiBufferFree(pUserInfo);
    }

    return isSystemUser;
}