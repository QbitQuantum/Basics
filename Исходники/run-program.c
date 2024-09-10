/* Set up in, out, err pipes and spawn a program, waiting or otherwise. */
HANDLE spawn (
    const char *program,
    const char *const *argv,
    int in,
    int out,
    int err,
    int search,
    char *envp,
    char *ptyname,
    int wait,
    char *pwd
    )
{
    int stdout_backup, stdin_backup, stderr_backup, wait_mode;
    HANDLE hProcess;
    HANDLE hReturn;

    /* Duplicate and save the original stdin/out/err handles. */
    stdout_backup = _dup (  _fileno ( stdout ) );
    stdin_backup  = _dup (  _fileno ( stdin  ) );
    stderr_backup = _dup (  _fileno ( stderr ) );

    /* If we are not using stdin/out/err
     * then duplicate the new pipes to current stdin/out/err handles.
     *
     * Default std fds are used if in, out or err parameters
     * are -1. */

    hReturn = (HANDLE)-1;
    hProcess = (HANDLE)-1;
    if ( ( out >= 0 ) && ( out != _fileno ( stdout ) ) ) {
        if ( _dup2 ( out, _fileno ( stdout ) ) != 0 ) goto error_exit;
    }
    if ( ( in >= 0 ) && ( in != _fileno ( stdin ) ) ) {
        if ( _dup2 ( in,  _fileno ( stdin )  ) != 0 ) goto error_exit_out;
    }
    if ( ( err >= 0 ) && ( err != _fileno ( stderr ) ) ) {
        if ( _dup2 ( err, _fileno ( stderr ) ) != 0 ) goto error_exit_in;
    }

    /* Set the wait mode. */
    if ( 0 == wait ) {
        wait_mode = P_NOWAIT;
    } else {
        wait_mode = P_WAIT;
    }

    /* Change working directory if supplied. */
    if (pwd) {
        if (chdir(pwd) < 0) {
            goto error_exit;
        }
    }

    /* Spawn process given on the command line*/
    if (search)
        hProcess = (HANDLE) spawnvp ( wait_mode, program, (char* const* )argv );
    else
        hProcess = (HANDLE) spawnv ( wait_mode, program, (char* const* )argv );

    /* Now that the process is launched, replace the original
     * in/out/err handles and close the backups. */

    if ( _dup2 ( stderr_backup, _fileno ( stderr ) ) != 0 ) goto error_exit;
 error_exit_in:
    if ( _dup2 ( stdin_backup,  _fileno ( stdin )  ) != 0 ) goto error_exit;
 error_exit_out:
    if ( _dup2 ( stdout_backup, _fileno ( stdout ) ) != 0 ) goto error_exit;

    hReturn = hProcess;

 error_exit:
    close ( stdout_backup );
    close ( stdin_backup  );
    close ( stderr_backup );

    return hReturn;

}