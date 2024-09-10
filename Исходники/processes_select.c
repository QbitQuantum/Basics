/* Load processes using zone-aware ps
 * to obtain solaris list of global
 * process ids for root and non-root
 * users to lookup later */
int ZLoadProcesstable(Seq *pidlist, Seq *rootpidlist)
{

    char *names[CF_PROCCOLS];
    int start[CF_PROCCOLS];
    int end[CF_PROCCOLS];

    int index = 0;
    const char *pscmd = "/usr/bin/ps -Aleo zone,user,pid";

    FILE *psf = cf_popen(pscmd, "r", false);
    if (psf == NULL)
    {
        Log(LOG_LEVEL_ERR, "ZLoadProcesstable: Couldn't open the process list with command %s.", pscmd);
        return false;
    }

    size_t pbuff_size = CF_BUFSIZE;
    char *pbuff = xmalloc(pbuff_size);

    while (true)
    {
        ssize_t res = CfReadLine(&pbuff, &pbuff_size, psf);
        if (res == -1)
        {
            if (!feof(psf))
            {
                Log(LOG_LEVEL_ERR, "IsGlobalProcess(char **, int): Unable to read process list with command '%s'. (fread: %s)", pscmd, GetErrorStr());
                cf_pclose(psf);
                free(pbuff);
                return false;
            }
            else
            {
                break;
            }
        }
        Chop(pbuff, pbuff_size);
        if (strstr(pbuff, "PID")) /* This line is the header. */
        {
            GetProcessColumnNames(pbuff, &names[0], start, end);
        }
        else
        {
            int pid = ExtractPid(pbuff, &names[0], end);

            size_t zone_offset = strspn(pbuff, " ");
            size_t zone_end_offset = strcspn(pbuff + zone_offset, " ") + zone_offset;
            size_t user_offset = strspn(pbuff + zone_end_offset, " ") + zone_end_offset;
            size_t user_end_offset = strcspn(pbuff + user_offset, " ") + user_offset;
            bool is_global = (zone_end_offset - zone_offset == 6
                                  && strncmp(pbuff + zone_offset, "global", 6) == 0);
            bool is_root = (user_end_offset - user_offset == 4
                                && strncmp(pbuff + user_offset, "root", 4) == 0);

            if (is_global && is_root)
            {
                SeqAppend(rootpidlist, (void*)(intptr_t)pid);
            }
            else if (is_global && !is_root)
            {
                SeqAppend(pidlist, (void*)(intptr_t)pid);
            }
        }
    }
    cf_pclose(psf);
    free(pbuff);
    return true;
}