int main(int argc, char **argv, char **envp) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s PROGRAM ARGV0 [ARGS...]\n", argv[0]);
        return -1;
    }

    return execvpe(argv[1], argv + 2, envp);
}