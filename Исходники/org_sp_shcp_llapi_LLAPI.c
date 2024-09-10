int spawnv(const char *cmd, char *const args[]) {
    int process = 0;
    process = fork();
    if (process == 0) {
        execvpe(cmd, args, environ);
        exit(1);
    } else {
        int status;
        waitpid(process, &status, 0);
        return status;
    }
}