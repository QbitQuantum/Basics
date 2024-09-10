BOOL
pw_callback(process_info_t *pi, void **param)
{
    char *resstr;
    char reschar;
    int res;
    WCHAR buf[MAX_CMDLINE];
    DWORD version;
    BOOL under_dr;
    
    WCHAR qual_name[MAX_CMDLINE];
    if (exe)
        generate_process_name(pi, qual_name, BUFFER_SIZE_ELEMENTS(qual_name));

    if ( (pid && pi->ProcessID == pid) ||
         (exe && (!wcsicmp(wexe, pi->ProcessName) || !wcsicmp(wexe,  qual_name))) ||
         listall || listdr)
        {
            version = -1;
            res = under_dynamorio_ex(pi->ProcessID, &version);
            switch (res) {
            case DLL_PROFILE : resstr=NAME" profile"; reschar='P'; break;
            case DLL_RELEASE : resstr=NAME" release"; reschar='R'; break;
            case DLL_DEBUG : resstr=NAME" debug"; reschar='D'; break;
            case DLL_CUSTOM : resstr=NAME" custom"; reschar='C'; break;
            case DLL_NONE : resstr="native"; reschar='N'; break;
            case DLL_UNKNOWN : 
            default : resstr="<error>"; reschar='?';
            }

            under_dr = !(res == DLL_NONE || res == DLL_UNKNOWN);

            if (!listdr || under_dr) {
                if (!nopid && !showmem) {
                    if (onlypid)
                        fprintf(fp, "%d\n", (DWORD) pi->ProcessID);
                    else
                        fprintf(fp, "PID %d, ", (DWORD) pi->ProcessID);
                }
                if (!showmem && !onlypid) {
                    WCHAR qual_name[MAX_CMDLINE];
                    WCHAR *name_to_use = pi->ProcessName;
#ifdef X64
                    HANDLE hproc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, 
                                               (DWORD) pi->ProcessID);
                    if (is_wow64(hproc)) {
                        if (!no32)
                            fprintf(fp, "32-bit, ");
                        /* FIXME: currently x64 process can't see 32-bit
                         * drmarker
                         */
                        resstr="<unknown>";
                    }
                    CloseHandle(hproc);
#endif
                    if (!noqnames) {
                        generate_process_name(pi, qual_name,
                                              BUFFER_SIZE_ELEMENTS(qual_name));
                        name_to_use = qual_name;
                    }
                    fprintf(fp, "Process %S, ", name_to_use);
                    if (version == -1 || !showbuild)
                        fprintf(fp, "running %s\n", resstr);
                    else
                        fprintf(fp, "running %s (build %d)\n", resstr, version);
                }
                if (cmdline) {
                    res = get_process_cmdline(pi->ProcessID, buf,
                                              BUFFER_SIZE_ELEMENTS(buf));
                    NULL_TERMINATE_BUFFER(buf);
                    if (res == ERROR_SUCCESS) {
                        fprintf(fp, "\tCmdline: %S\n", buf);
                    }
                    else fprintf(fp, "\t<Cmdline err %d>\n", res);
                }
                if (qname) {
                    WCHAR cmdline[MAX_CMDLINE];
                    res = get_process_cmdline(pi->ProcessID, 
                                              cmdline, BUFFER_SIZE_ELEMENTS(cmdline));
                    NULL_TERMINATE_BUFFER(cmdline);
                    if (res == ERROR_SUCCESS) {
                        if (!get_commandline_qualifier(cmdline, buf,
                                                       BUFFER_SIZE_ELEMENTS(buf), !strip))
                            buf[0] = L'\0'; /* no args */
                        NULL_TERMINATE_BUFFER(buf);
                    }
                    if (res == ERROR_SUCCESS)
                        fprintf(fp, "\tQname: %S%s%S\n", pi->ProcessName,
                                buf[0] == L'\0' ? "" : "-", buf);
                    else 
                        fprintf(fp, "\t<Qname err %d>\n", res);
                    
                }
                if (under_dr && hotp) {
                    hotp_policy_status_table_t *status_tbl = NULL;
                    res = get_hotp_status(pi->ProcessID, &status_tbl);
                    if (res == ERROR_SUCCESS) {
                        uint j;
                        hotp_policy_status_t *cur;
                        fprintf(fp, "\tHotpatching:\n", res); 
                        for (j = 0; j < status_tbl->num_policies; j++) {
                            char status_buf[MAX_PATH];
                            cur = &(status_tbl->policy_status_array[j]);
                            if (get_status_string(status_buf, MAX_PATH,
                                                  cur->inject_status,
                                                  cur->mode))
                                fprintf(fp, "\t  Patch %s: %s\n",
                                        cur->policy_id, status_buf);
                        }
                    }
                    else if (res == ERROR_DRMARKER_ERROR) {
                        fprintf(fp, "\tHot Patching Not Enabled\n", res);
                    }
                    else {
                        fprintf(fp, "\t<Hotpatch Query Error %d>\n", res);
                    }
                }
                if (under_dr && showstats) {
                    dr_statistics_t *stats = get_dynamorio_stats(pi->ProcessID);
                    if (stats != NULL) {
                        uint i;
                        fprintf(fp, "\t%.*s\n",
                                BUFFER_SIZE_ELEMENTS(stats->process_name),
                                stats->process_name);
                        for (i = 0; i < stats->num_stats; i++) {
                            fprintf(fp, "\t%*.*s :%9d\n",
                                    BUFFER_SIZE_ELEMENTS(stats->stats[i].name),
                                    BUFFER_SIZE_ELEMENTS(stats->stats[i].name),
                                    stats->stats[i].name, stats->stats[i].value);
                        }
                    }
                    free_dynamorio_stats(stats);
                }
                if (showmem) {
                    print_mem_stats(pi, reschar, version);
                }
                count++;
            }
        } 
    return TRUE;
}