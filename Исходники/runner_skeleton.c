int main(int argc, char* argv[]) {
        char *args[ARG_BUF_SIZE];
        char base_path[PATH_BUF_SIZE + 1];
        char script_path[PATH_BUF_SIZE + 1];
        char shell_path[PATH_BUF_SIZE + 1];
        char env_path[ENV_VAR_SIZE];
        int argi;

        _fullpath(shell_path, argv[0], PATH_BUF_SIZE);
        strcpy(script_path, shell_path);
        strcpy(base_path, shell_path);

        parent(shell_path);
        strcat(shell_path, "\\sh.exe");

        remove_extension(script_path);
        parent(base_path);

        args[0] = shell_path;
        args[1] = "--norc";
        args[2] = script_path;

        /* Any parameters passed on the command line will be passed through to the shell script */
        for (argi = 0; argi < MIN(argc - 1, ARG_BUF_SIZE); argi++) {
                printf("%s\n", argv[argi + 1]);
                args[argi + NUM_EXEC_ARGS] = argv[argi + 1];
        }
        /* Signal the end of the argument list */
        args[argi + NUM_EXEC_ARGS] = NULL;

        /* Add this executable's directory to the path */
        strcpy(env_path, "PATH=");
        strcat(env_path, getenv("PATH"));
        strcat(env_path, ";");
        strcat(env_path, base_path);
        _putenv(env_path);

        _spawnv(_P_WAIT, args[0], &args[1]);

        _flushall();
}