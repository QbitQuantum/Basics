/* Wrap the execv() that calls the pinentry program to include a special
 * _CLIENT_PID environment variable, which contains the PID we gathered during
 * accept(). Note that this is potentially racy if we have a lot of concurrent
 * connections, but the worst that could happen is that we end up having a
 * pinentry running on the wrong TTY/display.
 */
int execv(const char *path, char *const argv[])
{
    static int (*_execv)(const char *, char *const[]) = NULL;
    if (_execv == NULL)
        _execv = dlsym(RTLD_NEXT, "execv");

    if (last_pid != 0 &&
        strncmp(path, PINENTRY_WRAPPER, sizeof(PINENTRY_WRAPPER) + 1) == 0) {
        char env_var[40];
        if (snprintf(env_var, 40, "_CLIENT_PID=%d", last_pid) < 0)
            return -1;
        if (putenv(env_var) < 0)
            return -1;
    }

    last_pid = 0;
    return _execv(path, argv);
}