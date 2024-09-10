/* run a check */
int run_check(char *processed_command, char **ret, char **err) {
    char *argv[MAX_CMD_ARGS];
    FILE *fp;
    pid_t pid;
    int pipe_stdout[2], pipe_stderr[2], pipe_rwe[3];
    int retval;
    sigset_t mask;

#ifdef EMBEDDEDPERL
    retval = run_epn_check(processed_command, ret, err);
    if(retval != GM_NO_EPN) {
        return retval;
    }
#endif

    /* check for check execution method (shell or execvp)
     * command line does not have to contain shell meta characters
     * and cmd must begin with a /. Otherwise "BLAH=BLUB cmd" would lead
     * to file not found errors
     */
    if((*processed_command == '/' || *processed_command == '.') && !strpbrk(processed_command,"!$^&*()~[]\\|{};<>?`\"'")) {
        /* use the fast execvp when there are no shell characters */
        gm_log( GM_LOG_TRACE, "using execvp, no shell characters found\n" );

        parse_command_line(processed_command,argv);
        if(!argv[0])
            _exit(STATE_UNKNOWN);

        if(pipe(pipe_stdout)) {
            gm_log( GM_LOG_ERROR, "error creating pipe: %s\n", strerror(errno));
            _exit(STATE_UNKNOWN);
        }
        if(pipe(pipe_stderr)) {
            gm_log( GM_LOG_ERROR, "error creating pipe: %s\n", strerror(errno));
            _exit(STATE_UNKNOWN);
        }
        if((pid=fork())<0){
            gm_log( GM_LOG_ERROR, "fork error\n");
            _exit(STATE_UNKNOWN);
        }
        else if(!pid){
            /* remove all customn signal handler */
            sigfillset(&mask);
            sigprocmask(SIG_UNBLOCK, &mask, NULL);

            /* child process */
            if((dup2(pipe_stdout[1],STDOUT_FILENO)<0)){
                gm_log( GM_LOG_ERROR, "dup2 error\n");
                _exit(STATE_UNKNOWN);
            }
            if((dup2(pipe_stderr[1],STDERR_FILENO)<0)){
                gm_log( GM_LOG_ERROR, "dup2 error\n");
                _exit(STATE_UNKNOWN);
            }
            close(pipe_stdout[1]);
            close(pipe_stderr[1]);
            current_child_pid = getpid();
            execvp(argv[0], argv);
            if(errno == 2)
                _exit(127);
            if(errno == 13)
                _exit(126);
            _exit(STATE_UNKNOWN);
        }

        /* parent */
        /* prepare stdout pipe reading */
        close(pipe_stdout[1]);
        fp=fdopen(pipe_stdout[0],"r");
        if(!fp){
            gm_log( GM_LOG_ERROR, "fdopen error\n");
            _exit(STATE_UNKNOWN);
        }
        *ret = extract_check_result(fp, GM_DISABLED);
        fclose(fp);

        /* prepare stderr pipe reading */
        close(pipe_stderr[1]);
        fp=fdopen(pipe_stderr[0],"r");
        if(!fp){
            gm_log( GM_LOG_ERROR, "fdopen error\n");
            _exit(STATE_UNKNOWN);
        }
        *err = extract_check_result(fp, GM_ENABLED);
        fclose(fp);

        close(pipe_stdout[0]);
        close(pipe_stderr[0]);
        if(waitpid(pid,&retval,0)!=pid)
            retval=-1;
    }
    else {
        /* use the slower popen when there were shell characters */
        gm_log( GM_LOG_TRACE, "using popen, found shell characters\n" );
        current_child_pid = getpid();
        pid = popenRWE(pipe_rwe, processed_command);

        /* extract check result */
        fp=fdopen(pipe_rwe[1],"r");
        if(!fp){
            gm_log( GM_LOG_ERROR, "fdopen error\n");
            _exit(STATE_UNKNOWN);
        }
        *ret = extract_check_result(fp, GM_DISABLED);
        fclose(fp);

        /* extract check stderr */
        fp=fdopen(pipe_rwe[2],"r");
        if(!fp){
            gm_log( GM_LOG_ERROR, "fdopen error\n");
            _exit(STATE_UNKNOWN);
        }
        *err = extract_check_result(fp, GM_ENABLED);
        fclose(fp);

        /* close the process */
        retval=pcloseRWE(pid, pipe_rwe);
    }

    return retval;
}