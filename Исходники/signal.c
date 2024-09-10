/**
 * CHILD
 */
static void handle_sigchld(int sig)
{
    pid_t pid;
    int status;
//#ifdef _DEBUG
	fprintf( stderr, "handle_sigchld SIG(%d)\n", sig);
//#endif
    for (;;) {

#ifdef _WIN32
        pid = _cwait(&status, -1, WAIT_CHILD);
#else
        pid = waitpid((pid_t) -1, &status, WNOHANG);
#endif
        /*none left*/
        if (pid == 0)
            break;

        if (pid < 0) {
            /*because of ptrace*/
            if (errno == EINTR)
                continue;
            break;
        }
    }
}