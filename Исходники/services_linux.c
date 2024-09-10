gboolean
services_os_action_execute(svc_action_t * op, gboolean synchronous)
{
    int rc, lpc;
    int stdout_fd[2];
    int stderr_fd[2];

    if (pipe(stdout_fd) < 0) {
        crm_err("pipe() failed");
    }

    if (pipe(stderr_fd) < 0) {
        crm_err("pipe() failed");
    }

    op->pid = fork();
    switch (op->pid) {
        case -1:
            crm_err("fork() failed");
            close(stdout_fd[0]);
            close(stdout_fd[1]);
            close(stderr_fd[0]);
            close(stderr_fd[1]);
            return FALSE;

        case 0:                /* Child */
            /* Man: The call setpgrp() is equivalent to setpgid(0,0)
             * _and_ compiles on BSD variants too
             * need to investigate if it works the same too.
             */
            setpgid(0, 0);
            close(stdout_fd[0]);
            close(stderr_fd[0]);
            if (STDOUT_FILENO != stdout_fd[1]) {
                if (dup2(stdout_fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                    crm_err("dup2() failed (stdout)");
                }
                close(stdout_fd[1]);
            }
            if (STDERR_FILENO != stderr_fd[1]) {
                if (dup2(stderr_fd[1], STDERR_FILENO) != STDERR_FILENO) {
                    crm_err("dup2() failed (stderr)");
                }
                close(stderr_fd[1]);
            }

            /* close all descriptors except stdin/out/err and channels to logd */
            for (lpc = getdtablesize() - 1; lpc > STDERR_FILENO; lpc--) {
                close(lpc);
            }

            /* Setup environment correctly */
            add_OCF_env_vars(op);

            /* execute the RA */
            execvp(op->opaque->exec, op->opaque->args);

            switch (errno) {    /* see execve(2) */
                case ENOENT:   /* No such file or directory */
                case EISDIR:   /* Is a directory */
                    rc = PCMK_OCF_NOT_INSTALLED;
#if SUPPORT_NAGIOS
                    if (safe_str_eq(op->standard, "nagios")) {
                        rc = NAGIOS_NOT_INSTALLED;
                    }
#endif
                    break;
                case EACCES:   /* permission denied (various errors) */
                    rc = PCMK_OCF_INSUFFICIENT_PRIV;
#if SUPPORT_NAGIOS
                    if (safe_str_eq(op->standard, "nagios")) {
                        rc = NAGIOS_INSUFFICIENT_PRIV;
                    }
#endif
                    break;
                default:
                    rc = PCMK_OCF_UNKNOWN_ERROR;
                    break;
            }
            _exit(rc);
    }

    /* Only the parent reaches here */
    close(stdout_fd[1]);
    close(stderr_fd[1]);

    op->opaque->stdout_fd = stdout_fd[0];
    set_fd_opts(op->opaque->stdout_fd, O_NONBLOCK);

    op->opaque->stderr_fd = stderr_fd[0];
    set_fd_opts(op->opaque->stderr_fd, O_NONBLOCK);

    if (synchronous) {
        int status = 0;
        int timeout = (1 + op->timeout) / 1000;

        crm_trace("Waiting for %d", op->pid);
        while ((op->timeout < 0 || timeout > 0) && waitpid(op->pid, &status, WNOHANG) <= 0) {
            sleep(1);
            read_output(op->opaque->stdout_fd, op);
            read_output(op->opaque->stderr_fd, op);
            timeout--;
        }

        crm_trace("Child done: %d", op->pid);
        if (timeout == 0) {
            int killrc = kill(op->pid, 9 /*SIGKILL*/);

            op->rc = PCMK_OCF_UNKNOWN_ERROR;
            op->status = PCMK_LRM_OP_TIMEOUT;
            crm_warn("%s:%d - timed out after %dms", op->id, op->pid, op->timeout);

            if (killrc && errno != ESRCH) {
                crm_err("kill(%d, KILL) failed: %d", op->pid, errno);
            }

        } else if (WIFEXITED(status)) {
            op->status = PCMK_LRM_OP_DONE;
            op->rc = WEXITSTATUS(status);
            crm_info("Managed %s process %d exited with rc=%d", op->id, op->pid, op->rc);

        } else if (WIFSIGNALED(status)) {
            int signo = WTERMSIG(status);

            op->status = PCMK_LRM_OP_ERROR;
            crm_err("Managed %s process %d exited with signal=%d", op->id, op->pid, signo);
        }
#ifdef WCOREDUMP
        if (WCOREDUMP(status)) {
            crm_err("Managed %s process %d dumped core", op->id, op->pid);
        }
#endif

        read_output(op->opaque->stdout_fd, op);
        read_output(op->opaque->stderr_fd, op);

    } else {
        crm_trace("Async waiting for %d - %s", op->pid, op->opaque->exec);
        mainloop_add_child(op->pid, op->timeout, op->id, op, operation_finished);

        op->opaque->stdout_gsource = mainloop_add_fd(op->id,
                                                     G_PRIORITY_LOW,
                                                     op->opaque->stdout_fd, op, &stdout_callbacks);

        op->opaque->stderr_gsource = mainloop_add_fd(op->id,
                                                     G_PRIORITY_LOW,
                                                     op->opaque->stderr_fd, op, &stderr_callbacks);
    }

    return TRUE;
}