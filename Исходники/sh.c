static void fork_and_execvpe()
{
    int pid = fork();

    if (pid != 0) {
        if (bg_flag != '&') {
            waitpid(pid, NULL, 0);
        } else {
            printf("Added [%d] to BG", pid);
        }

    } else {
        execvpe(prog, execargs, NULL);
        exit(1);
    }
}