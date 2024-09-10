void ps_terminal_run_program(int fd_control, char *arguments)
{
    int fd_master, pid_program, exit_status;
    socklen_t sizeof_credentials;
    struct ucred credentials;

    // run the program under the uid of the user that connected to the server

    sizeof_credentials = sizeof(credentials);

    if(getsockopt(fd_control, SOL_SOCKET, SO_PEERCRED, &credentials, &sizeof_credentials) == -1)
        ps_log(EXIT_FAILURE, LOG_ERROR("failed to get uid of controlling user - error [%s]"), strerror(errno));

    if (ps_terminal_set_user(credentials.uid) == EXIT_FAILURE)
    {
        ps_terminal_send_exitcode(fd_control, EXIT_FAILURE);
        return;
    }

    // create a pseudoterminal

    fd_master = posix_openpt(O_RDWR | O_NOCTTY);

    if (fd_master == -1)
        ps_log(EXIT_FAILURE, LOG_ERROR("posix_openpt() failed -error [%s]"), strerror(errno));

    if (grantpt(fd_master) == -1)
        ps_log(0 /*EXIT_FAILURE*/, LOG_ERROR("grantpt() failed - error [%s]"), strerror(errno));

    if (unlockpt(fd_master) == -1)
        ps_log(EXIT_FAILURE, LOG_ERROR("unlockpt() failed - error [%s]"), strerror(errno));

    // fork a new process to run the program

    pid_program=fork();

    if (pid_program == -1)
        ps_log(EXIT_FAILURE, LOG_ERROR("unable to fork - error [%s]"), strerror(errno));

    if (pid_program == 0)
    {
        close(fd_control);
        ps_program_exec(fd_master, arguments);
        ps_log(EXIT_FAILURE, LOG_ERROR("trespassing error!"));
    }

//  TEST for a problem with bash. It seems that bash disables cntl-d (eof) handling
//  in the pseudo terminal if there is input before it outputs its prompt. This requires
//  us to use the exit statement in a script that is inside a here-document. The sh shell
//  does not have this behaviour. Needs further investigation...
//sleep(1);

    ps_terminal_io_loop(fd_control, fd_master);

    if (waitpid(pid_program, &exit_status, 0) == -1)
        ps_log(EXIT_FAILURE, LOG_ERROR("waitpid failed - error [%s]"), strerror(errno));

    // return status to controller

    ps_log(0, LOG_INFO("after wait - exit_status [%d]"), exit_status);
    ps_terminal_send_exitcode(fd_control, exit_status);
    close(fd_master);
    close(fd_control);
}