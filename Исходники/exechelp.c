/* Fork and exec the program with /dev/null as stdin, stdout and
   stderr.  Returns 0 on success or an error code.  */
gpg_error_t
gpgex_spawn_detached (const char *cmdline)
{
    SECURITY_ATTRIBUTES sec_attr;
    PROCESS_INFORMATION pi =
    {
        NULL,      /* Returns process handle.  */
        0,         /* Returns primary thread handle.  */
        0,         /* Returns pid.  */
        0          /* Returns tid.  */
    };
    STARTUPINFO si;
    int cr_flags;

    TRACE_BEG1 (DEBUG_ASSUAN, "gpgex_spawn_detached", cmdline,
                "cmdline=%s", cmdline);

    /* Prepare security attributes.  */
    memset (&sec_attr, 0, sizeof sec_attr);
    sec_attr.nLength = sizeof sec_attr;
    sec_attr.bInheritHandle = FALSE;

    /* Start the process.  Note that we can't run the PREEXEC function
       because this would change our own environment. */
    memset (&si, 0, sizeof si);
    si.cb = sizeof (si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = DEBUG_W32_SPAWN ? SW_SHOW : SW_MINIMIZE;

    cr_flags = (CREATE_DEFAULT_ERROR_MODE
                | GetPriorityClass (GetCurrentProcess ())
                | CREATE_NEW_PROCESS_GROUP
                | DETACHED_PROCESS);

    if (!CreateProcess (NULL,          /* pgmname; Program to start.  */
                        (char *) cmdline, /* Command line arguments.  */
                        &sec_attr,     /* Process security attributes.  */
                        &sec_attr,     /* Thread security attributes.  */
                        TRUE,          /* Inherit handles.  */
                        cr_flags,      /* Creation flags.  */
                        NULL,          /* Environment.  */
                        NULL,          /* Use current drive/directory.  */
                        &si,           /* Startup information. */
                        &pi            /* Returns process information.  */
                       ))
    {
        (void) TRACE_LOG1 ("CreateProcess failed: %i\n", GetLastError ());
        return gpg_error (GPG_ERR_GENERAL);
    }

    /* Process has been created suspended; resume it now. */
    CloseHandle (pi.hThread);
    CloseHandle (pi.hProcess);

    return 0;
}