static int
tmp_inout_popen(FILE **fr, FILE **fw, char *cmd)
{
    char  buf[NFILEN + 128];
    DWORD dummy, len;
    int   rc, term_status, tmpin_fd;

    TRACE(("tmp_inout_popen cmd=%s\n", cmd));
    proc_handle = BAD_PROC_HANDLE;
    handles[0]  = handles[1] = handles[2]  = INVALID_HANDLE_VALUE;
    tmpin_fd    = stdin_fd   = stdout_fd   = BAD_FD;
    tmpin_name  = stdin_name = stdout_name = NULL;
    set_console_title(cmd);
    do
    {
        if (fr)
        {
            *fr = NULL;
            if ((stdin_name = _tempnam(getenv("TEMP"), "vile")) == NULL)
                break;
            if ((stdin_fd = open(stdin_name,
                                 O_RDWR|O_CREAT|O_TRUNC|O_TEXT,
                                 _S_IWRITE|_S_IREAD)) == BAD_FD)
            {
                break;
            }
            handles[2] = handles[1] = (HANDLE) _get_osfhandle(stdin_fd);
            if (! fw)
            {
                /*
                 * This is a read pipe (only).  Connect child's stdin to
                 * an empty file.  Under no circumstances should the
                 * child's stdin be connected to a device (else lots of
                 * screwy things will occur).  In particular, connecting
                 * the child's stdin to the parent's stdin will cause
                 * aborts and hangs on the various Win32 hosts.  You've
                 * been warned.
                 */

                if ((tmpin_name = _tempnam(getenv("TEMP"), "vile")) == NULL)
                    break;
                if ((tmpin_fd = open(tmpin_name,
                                     O_RDONLY|O_CREAT|O_TRUNC,
                                     _S_IWRITE|_S_IREAD)) == BAD_FD)
                {
                    break;
                }
                handles[0] = (HANDLE) _get_osfhandle(tmpin_fd);
            }
            else
            {
                /*
                 * Set up descriptor for filter operation.   Note the
                 * sublteties here:  exec'd shell is passed a descriptor
                 * to the temp file that's opened "w".  The editor
                 * receives a descriptor to the file that's opened "r".
                 */

                if ((*fr = fopen(stdin_name, "r")) == NULL)
                    break;
            }
        }
        if (fw)
        {
            *fw = NULL;

            /* create a temp file to receive data from the editor */
            if ((stdout_name = _tempnam(getenv("TEMP"), "vile")) == NULL)
                break;
            if ((stdout_fd = open(stdout_name,
                                  O_RDWR|O_CREAT|O_TRUNC|O_BINARY,
                                  _S_IWRITE|_S_IREAD)) == BAD_FD)
            {
                break;
            }
            if ((*fw = fdopen(stdout_fd, "w")) == 0)
                break;

            /*
             * we're all set up, but can't exec "cmd" until the editor
             * writes data to the temp file connected to stdout.
             */
            shcmd = cmd;   /* remember this */
            return (TRUE);
        }

        /* This must be a read (only) pipe.  Appropriate to exec "cmd". */
        rc = (exec_shell(cmd,
                         handles,
                         TRUE       /* hide child wdw */
                        ) == BAD_PROC_HANDLE) ? FALSE : TRUE;

        if (! rc)
        {
            /*
             * Shell process failed, put complaint in user's buffer, which
             * is currently proxied by a temp file that the editor will
             * suck in shortly.
             */

            len = (DWORD) (lsprintf(buf, SHELL_ERR_MSG, get_shell()) - buf);
            (void) WriteFile(handles[1], buf, len, &dummy, NULL);
            FlushFileBuffers(handles[1]);
        }
        else
        {
            /* wait for exec'd process to exit */

            (void) cwait(&term_status, (CWAIT_PARAM_TYPE) proc_handle, 0);
            TRACE(("...CreateProcess finished waiting in tmp_inout_popen\n"));
            close_proc_handle();
        }

        /*
         * When closing descriptors shared between parent and child, order
         * is quite important when $shell == command.com .  In this
         * situation, the descriptors can't be closed until the exec'd
         * process exits (I kid you not).
         */
        close_fd(stdin_fd);
        (void) close(tmpin_fd);

        /* let the editor consume the output of the read pipe */
        if ((*fr = fopen(stdin_name, "r")) == NULL)
        {
            /*
             * impossible to put error in user's buffer since that file
             * descriptor is closed.
             */

            sprintf(buf,
                    "[error opening temp file \"%s\": %s]",
                    stdin_name,
                    strerror(errno));
            lastditch_msg(buf);
            break;
        }
        return (rc);
    }
    while (FALSE);

    /* If we get here -- some operation has failed.  Clean up. */
    tmp_cleanup();
    return (FALSE);
}