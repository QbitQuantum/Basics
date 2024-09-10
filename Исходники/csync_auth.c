int csync_getpass(const char *prompt,
                char *buf,
                size_t len,
                int echo,
                int verify,
                void *userdata
               ) {
    /* unused variables */
    (void) userdata;

    HANDLE h;
    DWORD mode = 0;
    int ok;

    /* fgets needs at least len - 1 */
    if (prompt == NULL || buf == NULL || len < 2) {
        return -1;
    }

    /* get stdin and mode */
    h = GetStdHandle(STD_INPUT_HANDLE);
    if (!GetConsoleMode(h, &mode)) {
        return -1;
    }

    /* disable echo */
    if (!echo) {
        if (!SetConsoleMode(h, mode & ~ENABLE_ECHO_INPUT)) {
            return -1;
        }
    }

    ok = csync_gets(prompt, buf, len, verify);

    /* reset echo */
    SetConsoleMode(h, mode);

    if (!ok) {
        memset (buf, '\0', len);
        return -1;
    }

    /* force termination */
    buf[len - 1] = '\0';

    return 0;
}