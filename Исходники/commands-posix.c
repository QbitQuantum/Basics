void qmp_guest_shutdown(bool has_mode, const char *mode, Error **err)
{
    const char *shutdown_flag;
    pid_t rpid, pid;
    int status;

    slog("guest-shutdown called, mode: %s", mode);
    if (!has_mode || strcmp(mode, "powerdown") == 0) {
        shutdown_flag = "-P";
    } else if (strcmp(mode, "halt") == 0) {
        shutdown_flag = "-H";
    } else if (strcmp(mode, "reboot") == 0) {
        shutdown_flag = "-r";
    } else {
        error_set(err, QERR_INVALID_PARAMETER_VALUE, "mode",
                  "halt|powerdown|reboot");
        return;
    }

    pid = fork();
    if (pid == 0) {
        /* child, start the shutdown */
        setsid();
        reopen_fd_to_null(0);
        reopen_fd_to_null(1);
        reopen_fd_to_null(2);

        execle("/sbin/shutdown", "shutdown", shutdown_flag, "+0",
               "hypervisor initiated shutdown", (char*)NULL, environ);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        goto exit_err;
    }

    do {
        rpid = waitpid(pid, &status, 0);
    } while (rpid == -1 && errno == EINTR);
    if (rpid == pid && WIFEXITED(status) && !WEXITSTATUS(status)) {
        return;
    }

exit_err:
    error_set(err, QERR_UNDEFINED_ERROR);
}