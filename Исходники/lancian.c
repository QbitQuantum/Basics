int main(int argc, char *argv[]) {
    int i, status;
    unsigned int n;
    char *cmd;
    char **args;
    char *envp[2];
    int n_args = argc-2;
    char ncopia[17];
    int **fds;
    char buffer[1024];
    size_t len;

    if (argc < 3)
        err("usage: lancian n cmd arg1 arg2 ...");

    envp[0] = (char *)ncopia;
    envp[1] = NULL;

    n = atoi(argv[1]);
    args = malloc((n_args+1)*sizeof(char *));
    cmd = args[0] = argv[2];
    args[n_args] = NULL;
    for (i = 1; i < n_args; ++i)
        args[i] = argv[i+2];

    fds = malloc(n*sizeof(int *));
    for (i = 0; i < n; ++i) {
        fds[i] = malloc(2*sizeof(int));
        pipe(fds[i]);
        if (fork() == 0) {
            close(fds[i][0]);
            dup2(fds[i][1], 1);
            close(fds[i][1]);

            sprintf(ncopia, "NCOPIA=%d", i);
            if (execvpe(cmd, args, envp) == -1)
                sys_err("execvpe");
        }
    }

    for (i = 0; i < n; ++i) {
        close(fds[i][1]);
        while ((len = read(fds[i][0], buffer, sizeof(buffer))) != 0)
            write(1, buffer, len);
    }

    printf("lancian: fine\n");
    exit(0);
}