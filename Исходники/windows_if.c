static LPUSER_INFO_1 find_windows_user_entry(char *username)
{
	LPUSER_INFO_1 buf;
    wchar_t username_wide[32];
    mbstowcs(username_wide, username, 32);

    if (NetUserGetInfo(NULL, username_wide, (DWORD) 1, (LPBYTE *) &buf) == NERR_Success)
    {
        return buf;
    }
    else
    {
        return NULL;
    }
}