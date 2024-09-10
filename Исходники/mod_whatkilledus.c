static void exception_hook(ap_exception_info_t *ei)
{
    int msg_len;
    int logfd;
    char msg_prefix[60];
    time_t now;
    char *newline;
    int using_errorlog = 1;

    time(&now);
    ap_snprintf(msg_prefix, sizeof msg_prefix,
                "[%s pid %ld mod_whatkilledus",
                asctime(localtime(&now)),
                (long)getpid());
    newline = strchr(msg_prefix, '\n'); /* dang asctime() */
    if (newline) {                      /* silly we are */
        *newline = ']';
    }

    if (log_fname) {
        logfd = open(log_fname, O_WRONLY|O_APPEND|O_CREAT, 0644);
        if (logfd == -1) {
            logfd = 2; /* unix, so fd 2 is the web server error log */
            ap_snprintf(buffer, sizeof buffer,
                        "%s error %d opening %s\n",
                        msg_prefix, errno, log_fname);
            write(logfd, buffer, strlen(buffer));
        }
        else {
            using_errorlog = 0;
        }
    }
    else {
        logfd = 2;
    }

    msg_len = ap_snprintf(buffer, sizeof buffer,
                          "%s sig %d crash\n",
                          msg_prefix, ei->sig);
    write(logfd, buffer, msg_len);

    if (local_addr) {
        msg_len = ap_snprintf(buffer, sizeof buffer,
                              "%s active connection: %s->%s\n",
                              msg_prefix, remote_addr, local_addr);
    }
    else {
        msg_len = ap_snprintf(buffer, sizeof buffer,
                              "%s no active connection at crash\n",
                              msg_prefix);
    }

    write(logfd, buffer, msg_len);

    if (request_plus_headers) {
        msg_len = ap_snprintf(buffer, sizeof buffer,
                              "%s active request:\n",
                              msg_prefix);
        write(logfd, buffer, msg_len);
        write(logfd, request_plus_headers, strlen(request_plus_headers));
    }
    else {
        msg_len = ap_snprintf(buffer, sizeof buffer,
                              "%s no request active at crash\n",
                              msg_prefix);
        write(logfd, buffer, msg_len);
    }
    msg_len = ap_snprintf(buffer, sizeof buffer,
                          "%s end of report\n",
                          msg_prefix);
    write(logfd, buffer, msg_len);
    if (!using_errorlog) {
        close(logfd);
    }
}