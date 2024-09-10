EXM_API int
exm_process_dependencies_set(Exm_Process *process)
{
    MODULEENTRY32 me32;
    HANDLE h;

    EXM_LOG_DBG("Finding dependencies");
    h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
                                 process->id);
    if (h == INVALID_HANDLE_VALUE)
    {
        EXM_LOG_ERR("Can not retrieve the modules the process %s",
                    process->filename);
        return 0;
    }

    me32.dwSize = sizeof(MODULEENTRY32);
    if (!Module32First(h, &me32))
    {
        EXM_LOG_ERR("Can not retrieve the first module the process %s",
                    process->filename);
        goto close_h;
    }

    do
    {
        size_t i;
        unsigned char is_found;

        EXM_LOG_DBG("Finding module %s in process %s",
                    me32.szExePath, strrchr(process->filename, '\\') + 1);

        for (i = 0; i < (sizeof(_exm_process_crt_names) / sizeof(const char *)); i++)
        {
            if (_stricmp(me32.szModule, _exm_process_crt_names[i]) != 0)
                continue;

            /* FIXME: this following test should be useless as the list of modules has no duplicata */
            if (exm_list_data_is_found(process->crt_names,
                                       me32.szExePath,
                                       _exm_process_dep_cmp))
                continue;

            process->crt_names = exm_list_append(process->crt_names,
                                                 _strdup(me32.szExePath));
        }

        is_found = 0;
        for (i = 0; i < (sizeof(_exm_process_dep_names_supp) / sizeof(const char *)); i++)
        {
            if (_stricmp(me32.szModule, _exm_process_dep_names_supp[i]) == 0)
            {
                is_found = 1;
                break;
            }
        }

        if (!is_found &&
            /* FIXME: this following test should be useless as the list of modules has no duplicata */
            !exm_list_data_is_found(process->dep_names,
                                    me32.szExePath,
                                    _exm_process_dep_cmp))
            process->dep_names = exm_list_append(process->dep_names,
                                                 _strdup(me32.szExePath));
    } while(Module32Next(h, &me32));

    CloseHandle(h);

    return 1;

  close_h:
    CloseHandle(h);

    return 0;
}