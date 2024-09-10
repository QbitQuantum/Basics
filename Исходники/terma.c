void
run()
{
    /* Using Xlib event handling to use the keyboard helpers */
    XEvent          event;
    fd_set          fds;
    struct timeval  timeout;
    struct timeval  now;
    uint32_t        usec_sleep = 1000000 / config.HZ;
    uint32_t        usec_sleep_passive = 1000000 / config.HZ_passive;

    int Xfd = XConnectionNumber(X.dpy);

    /* If there is no user activity, we can spend more time between screen
     * updates without the user feeling less responsiveness. Passive mode
     * means that there are no X events to respond to, and we could slow down
     * rendering a bit, offering more throughput
     */
    struct timeval last_event;
    last_event.tv_sec = 0;
    last_event.tv_usec = 0;
    bool passive = false;

    for (;;) {
        FD_ZERO(&fds);
        FD_SET(Xfd, &fds);
        FD_SET(shell_fd, &fds);


        timeout.tv_sec  = 0;
        timeout.tv_usec = usec_sleep; /* TODO: set to blinking time? */

        if (select(max(Xfd, shell_fd) + 1, &fds, NULL, NULL, &timeout) < 0) {
            if (errno == EINTR)
                continue;
            die("select failed");
        }

        if (FD_ISSET(shell_fd, &fds)) {
            sh_read(term_write); /* short circuit shell output and term input */
        }

        while (XPending(X.dpy)) {
            XNextEvent(X.dpy, &event);
            if (XFilterEvent(&event, X.window))
                continue;

            passive = false;
            if (event.type < (int)LENGTH(x_handler) && x_handler[event.type])
                (x_handler[event.type])(&event);
        }

        gettimeofday(&now, NULL);
        if (timediff_usec(now, X.last_draw) > (passive ? usec_sleep_passive : usec_sleep)) {
            x_draw();
        }

        if (FD_ISSET(Xfd, &fds)) {
            gettimeofday(&last_event, NULL);
            passive = false;
        }
        else {
            passive = timediff_usec(now, last_event) > usec_sleep_passive;
        }

        if (!FD_ISSET(shell_fd, &fds) && passive) {
            term_gc(); /* Clean up term if we have time to spare */
        }
    }
}