/* Relay data between a socket and a process until the process dies or stops
   sending or receiving data. The socket descriptor and process pipe handles
   are in the data argument, which must be a pointer to struct subprocess_info.

   This function is a workaround for the fact that we can't just run a process
   after redirecting its input handles to a socket. If the process, for
   example, redirects its own stdin, it somehow confuses the socket and stdout
   stops working. This is exactly what ncat does (as part of the Windows stdin
   workaround), so it can't be ignored.

   This function can be invoked through CreateThread to simulate fork+exec, or
   called directly to simulate exec. It frees the subprocess_info struct and
   closes the socket and pipe handles before returning. Returns the exit code
   of the subprocess. */
static DWORD WINAPI subprocess_thread_func(void *data)
{
    struct subprocess_info *info;
    char pipe_buffer[BUFSIZ];
    OVERLAPPED overlap = { 0 };
    HANDLE events[3];
    DWORD ret, rc;
    int crlf_state = 0;

    info = (struct subprocess_info *) data;

    /* Three events we watch for: socket read, pipe read, and process end. */
    events[0] = (HANDLE) WSACreateEvent();
    WSAEventSelect(info->fdn.fd, events[0], FD_READ | FD_CLOSE);
    events[1] = info->child_out_r;
    events[2] = info->proc;

    /* To avoid blocking or polling, we use asynchronous I/O, or what Microsoft
       calls "overlapped" I/O, on the process pipe. WaitForMultipleObjects
       reports when the read operation is complete. */
    ReadFile(info->child_out_r, pipe_buffer, sizeof(pipe_buffer), NULL, &overlap);

    /* Loop until EOF or error. */
    for (;;) {
        DWORD n_r, n_w;
        int i, n;

        i = WaitForMultipleObjects(3, events, FALSE, INFINITE);
        if (i == WAIT_OBJECT_0) {
            /* Read from socket, write to process. */
            char buffer[BUFSIZ];
            int pending;

            ResetEvent(events[0]);
            do {
                n = ncat_recv(&info->fdn, buffer, sizeof(buffer), &pending);
                if (n <= 0)
                    goto loop_end;
                n_r = n;
                if (WriteFile(info->child_in_w, buffer, n_r, &n_w, NULL) == 0)
                    break;
                if (n_w != n)
                    goto loop_end;
            } while (pending);
        } else if (i == WAIT_OBJECT_0 + 1) {
            char *crlf = NULL, *wbuf;
            /* Read from process, write to socket. */
            if (GetOverlappedResult(info->child_out_r, &overlap, &n_r, FALSE)) {
                wbuf = pipe_buffer;
                if (o.crlf) {
                    n = n_r;
                    if (fix_line_endings((char *) pipe_buffer, &n, &crlf, &crlf_state))
                        wbuf = crlf;
                    n_r = n;
                }
                /* The above call to WSAEventSelect puts the socket in
                   non-blocking mode, but we want this send to block, not
                   potentially return WSAEWOULDBLOCK. We call block_socket, but
                   first we must clear out the select event. */
                WSAEventSelect(info->fdn.fd, events[0], 0);
                block_socket(info->fdn.fd);
                n = ncat_send(&info->fdn, wbuf, n_r);
                if (crlf != NULL)
                    free(crlf);
                if (n != n_r)
                    break;
                /* Restore the select event (and non-block the socket again.) */
                WSAEventSelect(info->fdn.fd, events[0], FD_READ | FD_CLOSE);
                /* Queue another ansychronous read. */
                ReadFile(info->child_out_r, pipe_buffer, sizeof(pipe_buffer), NULL, &overlap);
            } else {
                if (GetLastError() != ERROR_IO_PENDING)
                    /* Error or end of file. */
                    break;
            }
        } else if (i == WAIT_OBJECT_0 + 2) {
            /* The child died. There are no more writes left in the pipe
               because WaitForMultipleObjects guarantees events with lower
               indexes are handled first. */
            break;
        } else {
            break;
        }
    }

loop_end:

    WSACloseEvent(events[0]);

    rc = unregister_subprocess(info->proc);
    ncat_assert(rc != -1);

    GetExitCodeProcess(info->proc, &ret);
    if (ret == STILL_ACTIVE) {
        if (o.debug > 1)
            logdebug("Subprocess still running, terminating it.\n");
        rc = TerminateProcess(info->proc, 0);
        if (rc == 0) {
            if (o.debug > 1)
                logdebug("TerminateProcess failed with code %d.\n", rc);
        }
    }
    GetExitCodeProcess(info->proc, &ret);
    if (o.debug > 1)
        logdebug("Subprocess ended with exit code %d.\n", ret);

    shutdown(info->fdn.fd, 2);
    subprocess_info_close(info);
    free(info);

    rc = WaitForSingleObject(pseudo_sigchld_mutex, INFINITE);
    ncat_assert(rc == WAIT_OBJECT_0);
    if (pseudo_sigchld_handler != NULL)
        pseudo_sigchld_handler();
    rc = ReleaseMutex(pseudo_sigchld_mutex);
    ncat_assert(rc != 0);

    return ret;
}