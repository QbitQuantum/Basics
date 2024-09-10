int execute(sigset_t *pset, char *prog, char *argv[], char *env[]) {
    child = fork();
    if ( child > 1 ) {
        return child;
    } else if ( child < 0 ) {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    }
    // We're now in the child so need to exec the requested program
    sigprocmask(SIG_SETMASK, pset, 0);
    setsid();
    setpgid(0, 0);
    execvpe(prog, argv, env);
    printf("execvpe failed\n");
    exit(255);
}