void gfire_process_list_update(gfire_process_list *p_list)
{
    if(!p_list)
        return;

    gfire_process_list_clear(p_list);

    acquirePrivileges();

    PROCESSENTRY32 pe;
    memset(&pe, 0, sizeof(pe));

    pe.dwSize = sizeof(pe);

    HANDLE hProcSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(!hProcSnapShot)
        return;

    if(!Process32First(hProcSnapShot, &pe))
    {
        CloseHandle(hProcSnapShot);
        return;
    }

    do
    {
        if(pe.th32ProcessID > 0)
        {
#ifdef DEBUG
            purple_debug_info("gfire", "detection: probing %s\n", pe.szExeFile);
#endif // DEBUG

            gchar *cmdline = NULL;
            gchar *executable_file = NULL;
            if(!get_process_cmdline(pe.th32ProcessID, &executable_file, &cmdline))
                continue;

#ifdef DEBUG
            purple_debug_info("gfire", "executable file: %s\n", executable_file);
            purple_debug_info("gfire", "cmdline: %s\n", cmdline);
#endif // DEBUG

            // Extract the args from the command line
            gchar *args = strstr(g_strstrip(cmdline), pe.szExeFile);
            if(args)
            {
                args += strlen(pe.szExeFile);
                if(args[0] == 0)
                    args = NULL;
                // If the first char behind the process' name is ", strip it
                else if(args[0] == '\"')
                {
                    args++;
                    if(args[0] == 0)
                        args = NULL;
                }
            }

            if(args)
            {
                g_strstrip(args);
#ifdef DEBUG
                purple_debug_info("gfire", "args: %s\n", args);
#endif // DEBUG
            }

            // Add the process
            process_info *info = gfire_process_info_new(executable_file, pe.th32ProcessID, args);
            g_free(cmdline);
            g_free(executable_file);

            p_list->processes = g_list_append(p_list->processes, info);
        }
    } while(Process32Next(hProcSnapShot, &pe));

    CloseHandle(hProcSnapShot);
}