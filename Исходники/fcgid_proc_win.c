apr_status_t proc_spawn_process(const char *cmdline, fcgid_proc_info *procinfo,
                                fcgid_procnode *procnode)
{
    HANDLE *finish_event, listen_handle;
    SECURITY_ATTRIBUTES SecurityAttributes;
    fcgid_server_conf *sconf;
    apr_procattr_t *proc_attr;
    apr_status_t rv;
    apr_file_t *file;
    const char * const *proc_environ;
    char sock_path[FCGID_PATH_MAX];
    int argc;
    char const * wargv[APACHE_ARG_MAX + 1], *word; /* For wrapper */
    const char *tmp;

    /* Build wrapper args */
    argc = 0;
    tmp = cmdline;
    while (1) {
        word = ap_getword_white(procnode->proc_pool, &tmp);
        if (word == NULL || *word == '\0')
            break;
        if (argc >= APACHE_ARG_MAX)
            break;
        wargv[argc++] = word;
    }
    wargv[argc] = NULL;

    memset(&SecurityAttributes, 0, sizeof(SecurityAttributes));

    /* Prepare finish event */
    finish_event = apr_palloc(procnode->proc_pool, sizeof(HANDLE));
    *finish_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (*finish_event == NULL
        || !SetHandleInformation(*finish_event, HANDLE_FLAG_INHERIT, TRUE))
    {
        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                     procinfo->main_server,
                     "mod_fcgid: can't create mutex for subprocess");
        return APR_ENOLOCK;
    }
    apr_pool_cleanup_register(procnode->proc_pool, finish_event,
                              close_finish_event, apr_pool_cleanup_null);

    /* For proc_kill_gracefully() */
    apr_pool_userdata_set(finish_event, FINISH_EVENT_DATA_NAME,
                          NULL, procnode->proc_pool);

    /* Pass the finish event id to subprocess */
    apr_table_setn(procinfo->proc_environ, SHUTDOWN_EVENT_NAME,
                   apr_ltoa(procnode->proc_pool, (long) *finish_event));

    /* Prepare the listen namedpipe file name (no check for truncation) */
    apr_snprintf(sock_path, sizeof sock_path,
                 "\\\\.\\pipe\\fcgidpipe-%lu.%d",
                 GetCurrentProcessId(), g_process_counter++);

    /* Prepare the listen namedpipe handle */
    SecurityAttributes.bInheritHandle = TRUE;
    SecurityAttributes.nLength = sizeof(SecurityAttributes);
    SecurityAttributes.lpSecurityDescriptor = NULL;
    listen_handle = CreateNamedPipe(sock_path,
                                    PIPE_ACCESS_DUPLEX,
                                    PIPE_TYPE_BYTE | PIPE_READMODE_BYTE |
                                    PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
                                    8192, 8192, 0, &SecurityAttributes);
    if (listen_handle == INVALID_HANDLE_VALUE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                     procinfo->main_server,
                     "mod_fcgid: can't create namedpipe for subprocess");
        return APR_ENOSOCKET;
    }
    apr_cpystrn(procnode->socket_path, sock_path, sizeof(procnode->socket_path));
    apr_cpystrn(procnode->executable_path, wargv[0],
                sizeof(procnode->executable_path));

    /* Build environment variables */
    proc_environ = (const char * const *)
                   ap_create_environment(procnode->proc_pool,
                                         procinfo->proc_environ);
    if (!proc_environ) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                     procinfo->main_server,
                     "mod_fcgid: can't build environment variables");
        return APR_ENOMEM;
    }

    /* Create process now */
    if ((rv = apr_procattr_create(&proc_attr, procnode->proc_pool))
               != APR_SUCCESS
        || (rv = apr_procattr_dir_set(proc_attr,
                     ap_make_dirstr_parent(procnode->proc_pool,
                                           wargv[0]))) != APR_SUCCESS
        || (rv = apr_procattr_cmdtype_set(proc_attr, APR_PROGRAM))
               != APR_SUCCESS
        || (rv = apr_procattr_detach_set(proc_attr, 1)) != APR_SUCCESS
        || (rv = apr_procattr_io_set(proc_attr, APR_NO_PIPE,
                                     APR_NO_FILE, APR_NO_FILE)) != APR_SUCCESS
        || (rv = apr_os_file_put(&file, &listen_handle, 0,
                                 procnode->proc_pool)) != APR_SUCCESS
        || (rv = apr_procattr_child_in_set(proc_attr, file, NULL))
               != APR_SUCCESS)
    {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, procinfo->main_server,
                     "mod_fcgid: can't create FastCGI process attribute");
        CloseHandle(listen_handle);
        return APR_ENOPROC;
    }

    /* fork and exec now */
    rv = apr_proc_create(&(procnode->proc_id), wargv[0], wargv,
                         proc_environ,
                         proc_attr, procnode->proc_pool);

    /* OK, I created the process, now put it back to idle list */
    CloseHandle(listen_handle);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, procinfo->main_server,
                     "mod_fcgid: can't run %s", wargv[0]);
        return rv;
    }

    /* FcgidWin32PreventOrphans feature */
    sconf = ap_get_module_config(procinfo->main_server->module_config,
                                 &fcgid_module);

    if (sconf->hJobObjectForAutoCleanup != NULL) {
        /* Associate cgi process to current process */
        if (AssignProcessToJobObject(sconf->hJobObjectForAutoCleanup,
                                     procnode->proc_id.hproc) == 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                         procinfo->main_server,
                         "mod_fcgid: unable to assign child process to "
                         "job object");
        }
    }

    return APR_SUCCESS;
}