/** Drain and close the socket
 * @param sd        socket to close
 * @param l         logger
 * @return          -1: socket to close is invalid
 *                  -1: some kind of error occured (!WIN32)
 *                  SOCKET_ERROR: some kind of error occured  (WIN32)
 *                  0: success
 * @remark          Does not change errno
 */
int jk_shutdown_socket(jk_sock_t sd, jk_logger_t *l)
{
    char dummy[512];
    char buf[DUMP_SINFO_BUF_SZ];
    char *sb = NULL;
    int rc = 0;
    size_t rd = 0;
    size_t rp = 0;
    int save_errno;
    int timeout = MS_TO_LINGER;
    time_t start = time(NULL);

    JK_TRACE_ENTER(l);

    if (!IS_VALID_SOCKET(sd)) {
        JK_TRACE_EXIT(l);
        return -1;
    }

    save_errno = errno;
    if (JK_IS_DEBUG_LEVEL(l)) {
        sb = jk_dump_sinfo(sd, buf, sizeof(buf));
        jk_log(l, JK_LOG_DEBUG, "About to shutdown socket %d [%s]",
               sd, sb);
    }
    /* Shut down the socket for write, which will send a FIN
     * to the peer.
     */
    if (shutdown(sd, SHUT_WR)) {
        rc = jk_close_socket(sd, l);
        if (JK_IS_DEBUG_LEVEL(l))
            jk_log(l, JK_LOG_DEBUG,
                   "Failed sending SHUT_WR for socket %d [%s]",
                   sd, sb);
        errno = save_errno;
        JK_TRACE_EXIT(l);
        return rc;
    }

    do {
        rp = 0;
        if (jk_is_input_event(sd, timeout, l)) {
            /* Do a restartable read on the socket
             * draining out all the data currently in the socket buffer.
             */
            int num = 0;
            do {
                num++;
#if defined(WIN32) || (defined(NETWARE) && defined(__NOVELL_LIBC__))
                rc = recv(sd, &dummy[0], sizeof(dummy), 0);
                if (JK_IS_SOCKET_ERROR(rc))
                    JK_GET_SOCKET_ERRNO();
#else
                rc = read(sd, &dummy[0], sizeof(dummy));
#endif
                if (rc > 0)
                    rp += rc;
            } while (JK_IS_SOCKET_ERROR(rc) && (errno == EINTR || errno == EAGAIN) && num < MAX_READ_RETRY);

            if (rc < 0) {
                /* Read failed.
                 * Bail out from the loop.
                 */
                break;
            }
        }
        else {
            /* Error or timeout (reason is logged within jk_is_input_event)
             * Exit the drain loop
             */
            break;
        }
        rd += rp;
        if (rp < sizeof(dummy)) {
            if (timeout > MS_TO_LINGER_LAST) {
                /* Try one last time with a short timeout
                */
                timeout = MS_TO_LINGER_LAST;
                continue;
            }
            /* We have read less then size of buffer
             * It's a good chance there will be no more data
             * to read.
             */
            if ((rc = sononblock(sd))) {
                rc = jk_close_socket(sd, l);
                if (JK_IS_DEBUG_LEVEL(l))
                    jk_log(l, JK_LOG_DEBUG,
                           "error setting socket %d [%s] to nonblocking",
                           sd, sb);
                errno = save_errno;
                JK_TRACE_EXIT(l);
                return rc;
            }
            if (JK_IS_DEBUG_LEVEL(l))
                jk_log(l, JK_LOG_DEBUG,
                       "shutting down the read side of socket %d [%s]",
                       sd, sb);
            shutdown(sd, SHUT_RD);
            break;
        }
        timeout = MS_TO_LINGER;
    } while ((rd < MAX_LINGER_BYTES) && (difftime(time(NULL), start) < MAX_SECS_TO_LINGER));

    rc = jk_close_socket(sd, l);
    if (JK_IS_DEBUG_LEVEL(l))
        jk_log(l, JK_LOG_DEBUG,
               "Shutdown socket %d [%s] and read %d lingering bytes in %d sec.",
               sd, sb, rd, (int)difftime(time(NULL), start));
    errno = save_errno;
    JK_TRACE_EXIT(l);
    return rc;
}