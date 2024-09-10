/* returns 1 on success, 0 on failure */
int
Valid_Group(char *UserName, char *Group)
{
    int result = FALSE;
    WCHAR wszUserName[256];	// Unicode user name
    WCHAR wszGroup[256];	// Unicode Group

    LPLOCALGROUP_USERS_INFO_0 pBuf = NULL;
    LPLOCALGROUP_USERS_INFO_0 pTmpBuf;
    DWORD dwLevel = 0;
    DWORD dwFlags = LG_INCLUDE_INDIRECT;
    DWORD dwPrefMaxLen = -1;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    NET_API_STATUS nStatus;
    DWORD i;
    DWORD dwTotalCount = 0;

/* Convert ANSI User Name and Group to Unicode */

    MultiByteToWideChar(CP_ACP, 0, UserName,
	strlen(UserName) + 1, wszUserName,
	sizeof(wszUserName) / sizeof(wszUserName[0]));
    MultiByteToWideChar(CP_ACP, 0, Group,
	strlen(Group) + 1, wszGroup, sizeof(wszGroup) / sizeof(wszGroup[0]));

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
	    (LPBYTE *) & pBuf, dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries);
	/*
	 * If the call succeeds,
	 */
    if (nStatus == NERR_Success) {
	if ((pTmpBuf = pBuf) != NULL) {
	    for (i = 0; i < dwEntriesRead; i++) {
		if (pTmpBuf == NULL) {
		    result = FALSE;
		    break;
		}
		if (wcscmp(pTmpBuf->lgrui0_name, wszGroup) == 0) {
		    result = TRUE;
		    break;
		}
		pTmpBuf++;
		dwTotalCount++;
	    }
	}
    } else
	    result = FALSE;
/*
 * Free the allocated memory.
 */
    if (pBuf != NULL)
	NetApiBufferFree(pBuf);
    return result;
}