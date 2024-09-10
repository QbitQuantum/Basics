int Action_exec(Action *action, Profile *prof)
{
    int rc = 0;
    char *procer_run_log = NULL;

    bstring pidfile_env = bformat("PROCER_PIDFILE=%s", bdata(prof->pid_file)); 
    putenv(bdata(pidfile_env));

    bstring action_env = bformat("PROCER_ACTION=%s", bdata(action->name)); 
    putenv(bdata(action_env));

    debug("ACTION: command=%s, pid_file=%s, restart=%d, depends=%s",
            bdata(prof->command), bdata(prof->pid_file), prof->restart,
            bdata(action->depends));

    pid_t pid = fork();
    check(pid >= 0, "Fork failed, WTF.  How can fork fail?");

    if(pid == 0) {
        rc = Unixy_drop_priv(action->profile_dir);

        if(rc != 0) {
            log_err("Not fatal, but we couldn't drop priv for %s",
                    bdata(action->name));
        }

        if( (procer_run_log = getenv("PROCER_RUN_LOG")) == NULL)
            procer_run_log = "run.log";
        redirect_output(procer_run_log);

        rc = execle(bdatae(prof->command, ""), bdatae(prof->command, ""), NULL, environ);
        check(rc != -1, "Failed to exec command: %s", bdata(prof->command));
    } else {
        int status = 0;
        debug("WAITING FOR CHILD.");
        pid = waitpid(pid, &status, 0);
    }

    debug("Command ran and exited successfully, now looking for the PID file.");
    return 0;
error:
    return -1;
}