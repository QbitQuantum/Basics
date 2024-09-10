int get_exec_pipes (char *cmd, int *fdIn, int *fdOut, netsnmp_pid_t * pid)
{

/*     Alexander Prömel, [email protected] 08/24/2006
    The following code, is tested on picotux rev. 1.01.
    I think, it will be better to put the named pipes, into /var/run or make it selectable via CONFIG file.
    If the pipe file already exist, the creation will fail.
    I put the pipes into /flash, the pipepath has to change in ucd-snmp/pass_persist.c too, if you change it here.
*/
#if HAVE_EXECV
#ifdef __uClinux__                /* HAVE uClinux */
    int in, out;

    char fifo_in_path[256];

    char fifo_out_path[256];

    pid_t tpid;

    if ((tpid = vfork ()) == 0)
    {                            /*temp child */
        execve (cmd, NULL, NULL);
        perror (cmd);
        exit (1);
    }
    else
    {
        if (tpid > 0)
        {
            /*initialize workspace */
            snprintf (fifo_in_path, 256, "/flash/cp_%d", tpid);
            snprintf (fifo_out_path, 256, "/flash/pc_%d", tpid);

            in = mkfifo (fifo_in_path, S_IRWXU);    /*Create Input Pipe, 700 */
            if (in)
            {
                perror ("parent: inpipe");
                exit (0);
            }
            out = mkfifo (fifo_out_path, S_IRWXU);    /*Create Output Pipe, 700 */
            if (out)
            {
                perror ("parent: outpipe");
                exit (0);
            }

            in = open (fifo_in_path, O_RDONLY);    /*open the Input Pipe read Only */
            if (in < 0)
            {
                perror ("parent: input");
                exit (0);
            }
            out = open (fifo_out_path, O_WRONLY);    /*open the Output Pipe write Only */
            if (out < 0)
            {
                perror ("parent: output");
                exit (0);
            }

            *fdIn = in;            /*read */
            *fdOut = out;        /*write */
            *pid = tpid;
            return (1);            /* We are returning 0 for error... */
        }
        else
        {                        /*pid < 0 */
            setPerrorstatus ("vfork");
            return 0;
        }

    }
#else                            /*HAVE x86 */
    int fd[2][2], i, cnt;

    char ctmp[STRMAX], *cptr1, *cptr2, argvs[STRMAX], **argv, **aptr;

    /*
     * Setup our pipes 
     */
    if (pipe (fd[0]) || pipe (fd[1]))
    {
        setPerrorstatus ("pipe");
        return 0;
    }
    if ((*pid = fork ()) == 0)
    {                            /* First handle for the child */
        close (0);
        if (dup (fd[0][0]) != 0)
        {
            setPerrorstatus ("dup 0");
            return 0;
        }
        close (1);
        if (dup (fd[1][1]) != 1)
        {
            setPerrorstatus ("dup 1");
            return 0;
        }

        /*
         * write standard output and standard error to pipe. 
         */
        /*
         * close all non-standard open file descriptors 
         */
        for (cnt = getdtablesize () - 1; cnt >= 2; --cnt)
            (void) close (cnt);
        (void) dup (1);            /* stderr */

        for (cnt = 1, cptr1 = cmd, cptr2 = argvs; *cptr1 != 0; cptr2++, cptr1++)
        {
            *cptr2 = *cptr1;
            if (*cptr1 == ' ')
            {
                *(cptr2++) = 0;
                if ((cptr1 = skip_white (cptr1)) == NULL)
                    break;
                *cptr2 = *cptr1;
                if (*cptr1 != 0)
                    cnt++;
            }
        }
        *cptr2 = 0;
        *(cptr2 + 1) = 0;
        argv = (char **) malloc ((cnt + 2) * sizeof (char *));
        if (argv == NULL)
            return 0;            /* memory alloc error */
        aptr = argv;
        *(aptr++) = argvs;
        for (cptr2 = argvs, i = 1; i != cnt; cptr2++)
            if (*cptr2 == 0)
            {
                *(aptr++) = cptr2 + 1;
                i++;
            }
        while (*cptr2 != 0)
            cptr2++;
        *(aptr++) = NULL;
        copy_nword (cmd, ctmp, sizeof (ctmp));
        execv (ctmp, argv);
        perror (ctmp);
        exit (1);
    }
    else
    {
        close (fd[0][0]);
        close (fd[1][1]);
        if (*pid < 0)
        {
            close (fd[0][1]);
            close (fd[1][0]);
            setPerrorstatus ("fork");
            return 0;
        }
        *fdIn = fd[1][0];
        *fdOut = fd[0][1];
        return (1);                /* We are returning 0 for error... */
    }
#endif                            /* uClinux or x86 */
#endif                            /* !HAVE_EXECV */
#if defined(WIN32) && !defined (mingw32) && !defined(HAVE_EXECV)

/* MSVC (MinGW not working but should use this code).  Cygwin already works as it has execv and fork */
    /* Reference:  MS tech note: 190351 */
    HANDLE hInputWriteTmp, hInputRead, hInputWrite = NULL;

    HANDLE hOutputReadTmp, hOutputRead, hOutputWrite = NULL;

    HANDLE hErrorWrite;

    SECURITY_ATTRIBUTES sa;

    PROCESS_INFORMATION pi;

    STARTUPINFO si;

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    /* Child temporary output pipe with Inheritance on (sa.bInheritHandle is true) */
    if (!CreatePipe (&hOutputReadTmp, &hOutputWrite, &sa, 0))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CreatePipe ChildOut: %d\n", GetLastError ()));
        return 0;
    }
    /* Child temporary input pipe with Inheritance on (sa.bInheritHandle is true) */
    if (!CreatePipe (&hInputRead, &hInputWriteTmp, &sa, 0))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CreatePipe ChildIn: %d\n", GetLastError ()));
        return 0;
    }

    /* Copy the stdout handle to the stderr handle in case the child closes one of 
     * its stdout handles. */
    if (!DuplicateHandle (GetCurrentProcess (), hOutputWrite, GetCurrentProcess (),
                          &hErrorWrite, 0, TRUE, DUPLICATE_SAME_ACCESS))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes DuplicateHandle: %d\n", GetLastError ()));
        return 0;
    }

    /* Create new copies of the input and output handles but set bInheritHandle to 
     * FALSE so the new handle can not be inherited.  Otherwise the handles can not
     * be closed.  */
    if (!DuplicateHandle (GetCurrentProcess (), hOutputReadTmp, GetCurrentProcess (),
                          &hOutputRead, 0, FALSE, DUPLICATE_SAME_ACCESS))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes DupliateHandle ChildOut: %d\n", GetLastError ()));
        CloseHandle (hErrorWrite);
        return 0;
    }
    if (!DuplicateHandle (GetCurrentProcess (), hInputWriteTmp,
                          GetCurrentProcess (), &hInputWrite, 0, FALSE, DUPLICATE_SAME_ACCESS))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes DupliateHandle ChildIn: %d\n", GetLastError ()));
        CloseHandle (hErrorWrite);
        CloseHandle (hOutputRead);
        return 0;
    }

    /* Close the temporary output and input handles */
    if (!CloseHandle (hOutputReadTmp))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle (hOutputReadTmp): %d\n", GetLastError ()));
        CloseHandle (hErrorWrite);
        CloseHandle (hOutputRead);
        CloseHandle (hInputWrite);
        return 0;
    }
    if (!CloseHandle (hInputWriteTmp))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle (hInputWriteTmp): %d\n", GetLastError ()));
        CloseHandle (hErrorWrite);
        CloseHandle (hOutputRead);
        CloseHandle (hInputWrite);
        return 0;
    }

    /* Associates a C run-time file descriptor with an existing operating-system file handle. */
    *fdIn = _open_osfhandle ((long) hOutputRead, 0);
    *fdOut = _open_osfhandle ((long) hInputWrite, 0);

    /* Set up STARTUPINFO for CreateProcess with the handles and have it hide the window
     * for the new process. */
    ZeroMemory (&si, sizeof (STARTUPINFO));
    si.cb = sizeof (STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdOutput = hOutputWrite;
    si.hStdInput = hInputRead;
    si.hStdError = hErrorWrite;
    si.wShowWindow = SW_HIDE;

    /* Launch the process that you want to redirect.  Example snmpd.conf pass_persist:
     * pass_persist    .1.3.6.1.4.1.2021.255  c:/perl/bin/perl c:/temp/pass_persisttest
     */
    if (!CreateProcess (NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CreateProcess:'%s' %d\n", cmd, GetLastError ()));
        CloseHandle (hErrorWrite);
        CloseHandle (hOutputRead);
        CloseHandle (hInputWrite);
        return 0;
    }

    DEBUGMSGTL (("util_funcs", "child hProcess (stored in pid): %d\n", (int) pi.hProcess));
    DEBUGMSGTL (("util_funcs", "child dwProcessId (task manager): %d\n", (int) pi.dwProcessId));

    /* Set global child process handle */
    *pid = pi.hProcess;

    /* Cleanup */
    if (!CloseHandle (pi.hThread))
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle pi.hThread: %d\n", cmd));

    /* Close pipe handles to make sure that no handles to the write end of the
     * output pipe are maintained in this process or else the pipe will
     * not close when the child process exits and any calls to ReadFile 
     * will hang.
     */

    if (!CloseHandle (hOutputWrite))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle hOutputWrite: %d\n", cmd, GetLastError ()));
        return 0;
    }
    if (!CloseHandle (hInputRead))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle hInputRead: %d\n", cmd, GetLastError ()));
        return 0;
    }
    if (!CloseHandle (hErrorWrite))
    {
        DEBUGMSGTL (("util_funcs", "get_exec_pipes CloseHandle hErrorWrite: %d\n", cmd, GetLastError ()));
        return 0;
    }
    return 1;
#endif                            /* WIN32 */
    return 0;
}