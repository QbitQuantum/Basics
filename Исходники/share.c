/***
 *  check_max_uses()
 *
 *      Check if a share has a /USERS:n switch or a /UNLIMITED
 *      switch.  If not, set max_users to the value of num_admin.
 *
 *      Currently used only on the ADMIN$ share.
 *
 *  Args:
 *      none
 *
 *  Returns:
 *      nothing - success
 *      exit(2) - command failed
 */
VOID NEAR check_max_uses(VOID)
{
    USHORT          err;                /* API return status */
    int                     i;
    struct server_info_2 FAR *      server_entry;
    TCHAR FAR *              ptr;
    USHORT2ULONG            swlen1, swlen2 ;
    static TCHAR             users_switch[20] ;

    _tcscpy(users_switch,swtxt_SW_SHARE_USERS);
    swlen1 = _tcslen(users_switch);
    swlen2 = _tcslen(swtxt_SW_SHARE_UNLIMITED);
    for (i = 0; SwitchList[i]; i++)
    {
        if ( (strncmpf(SwitchList[i], users_switch, swlen1) == 0) ||
             (strncmpf(SwitchList[i], swtxt_SW_SHARE_UNLIMITED, swlen2) == 0)
           )
        {
            return;     //  A specific switch exists; return without
                        //  further action.
        }
    }

    if (err = MNetServerGetInfo(NULL,
                                2,
                                (LPBYTE*)&server_entry))
        ErrorExit (err);

    ptr = _tcschr(users_switch, NULLC);
    nsprintf(ptr, TEXT(":%u"), server_entry->sv2_numadmin);

    SwitchList[i] = users_switch;
    NetApiBufferFree((TCHAR FAR *) server_entry);
}