ssize_t
send(int fd, const void *buf, size_t len, int flags)
{
    ssize_t                  retval;
    static send_handle       orig_send = NULL;

    dd("calling my send");

    if ((get_mocking_type() & MOCKING_WRITES)
        && fd <= MAX_FD
        && polled_fds[fd]
        && written_fds[fd]
        && !(active_fds[fd] & POLLOUT))
    {
        if (get_verbose_level()) {
            fprintf(stderr, "mockeagain: mocking \"send\" on fd %d to "
                    "signal EAGAIN\n", fd);
        }

        errno = EAGAIN;
        return -1;
    }

    written_fds[fd] = 1;

    init_libc_handle();

    if (orig_send == NULL) {
        orig_send = dlsym(libc_handle, "send");
        if (orig_send == NULL) {
            fprintf(stderr, "mockeagain: could not find the underlying send: "
                    "%s\n", dlerror());
            exit(1);
        }
    }

    if ((get_mocking_type() & MOCKING_WRITES)
        && fd <= MAX_FD
        && polled_fds[fd]
        && len)
    {
        if (get_verbose_level()) {
            fprintf(stderr, "mockeagain: mocking \"send\" on fd %d to emit "
                    "1 byte data only\n", fd);
        }

        if (pattern && len) {
            char          *p;
            size_t         len;
            char           c;

            c = *(char *) buf;

            if (matchbufs[fd] == NULL) {

                matchbufs[fd] = malloc(matchbuf_len);
                if (matchbufs[fd] == NULL) {
                    fprintf(stderr, "mockeagain: ERROR: failed to allocate memory.\n");
                }

                p = matchbufs[fd];
                memset(p, 0, matchbuf_len);

                p[0] = c;

                len = 1;

            } else {
                p = matchbufs[fd];

                len = strlen(p);

                if (len < matchbuf_len - 1) {
                    p[len] = c;
                    len++;

                } else {
                    memmove(p, p + 1, matchbuf_len - 2);

                    p[matchbuf_len - 2] = c;
                }
            }

            /* test if the pattern matches the matchbuf */

            dd("matchbuf: %.*s (len: %d)", (int) len, p,
                    (int) matchbuf_len - 1);

            if (len == matchbuf_len - 1 && strncmp(p, pattern, len) == 0) {
                if (get_verbose_level()) {
                    fprintf(stderr, "mockeagain: \"writev\" has found a match for "
                            "the timeout pattern \"%s\" on fd %d.\n", pattern, fd);
                }

                snd_timeout_fds[fd] = 1;
            }
        }

        retval = (*orig_send)(fd, buf, 1, flags);
        active_fds[fd] &= ~POLLOUT;

    } else {

        dd("calling the original send on fd %d", fd);

        retval = (*orig_send)(fd, buf, len, flags);
    }

    return retval;
}