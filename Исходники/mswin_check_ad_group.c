/* returns 1 on success, 0 on failure */
int
Valid_Local_Groups(char *UserName, const char **Groups)
{
    int result = 0;
    char *Domain_Separator;
    WCHAR wszUserName[UNLEN + 1];	// Unicode user name

    LPLOCALGROUP_USERS_INFO_0 pBuf;
    LPLOCALGROUP_USERS_INFO_0 pTmpBuf;
    DWORD dwLevel = 0;
    DWORD dwFlags = LG_INCLUDE_INDIRECT;
    DWORD dwPrefMaxLen = -1;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    NET_API_STATUS nStatus;
    DWORD i;
    DWORD dwTotalCount = 0;
    LPBYTE pBufTmp = NULL;

    if ((Domain_Separator = strchr(UserName, '/')) != NULL)
        *Domain_Separator = '\\';

    debug("Valid_Local_Groups: checking group membership of '%s'.\n", UserName);

    /* Convert ANSI User Name and Group to Unicode */

    MultiByteToWideChar(CP_ACP, 0, UserName,
                        strlen(UserName) + 1, wszUserName, sizeof(wszUserName) / sizeof(wszUserName[0]));

    /*
     * Call the NetUserGetLocalGroups function
     * specifying information level 0.
     *
     * The LG_INCLUDE_INDIRECT flag specifies that the
     * function should also return the names of the local
     * groups in which the user is indirectly a member.
     */
    nStatus = NetUserGetLocalGroups(NULL,
                                    wszUserName,
                                    dwLevel,
                                    dwFlags,
                                    &pBufTmp,
                                    dwPrefMaxLen,
                                    &dwEntriesRead,
                                    &dwTotalEntries);
    pBuf = (LPLOCALGROUP_USERS_INFO_0) pBufTmp;
    /*
     * If the call succeeds,
     */
    if (nStatus == NERR_Success) {
        if ((pTmpBuf = pBuf) != NULL) {
            for (i = 0; i < dwEntriesRead; i++) {
                assert(pTmpBuf != NULL);
                if (pTmpBuf == NULL) {
                    result = 0;
                    break;
                }
                if (wcstrcmparray(pTmpBuf->lgrui0_name, Groups) == 0) {
                    result = 1;
                    break;
                }
                pTmpBuf++;
                dwTotalCount++;
            }
        }
    } else
        result = 0;
    /*
     * Free the allocated memory.
     */
    if (pBuf != NULL)
        NetApiBufferFree(pBuf);
    return result;
}