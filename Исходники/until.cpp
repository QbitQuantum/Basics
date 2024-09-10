char *GetLogUserXP()
{
    TCHAR	*szLogName = NULL;
    DWORD	dwSize = 0;
    if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &szLogName, &dwSize))
    {
        char	*lpUser = new char[256];
        lstrcpy(lpUser, szLogName);
        WTSFreeMemory(szLogName);
        return lpUser;
    }
    else
        return NULL;
}