static void
win32iocr_set_handle (struct win32iocr_thread *iocr_thr,
                      struct win32overlapped *ov)
{
    static WSABUF buf = {0, 0};

    struct event *ev = ov->e.ev;
    unsigned int rw_flags;
    sd_t sd;

    if (!ev) goto ready;

    sd = (sd_t) ev->fd;
    rw_flags = ov->ih.rw_flags;
    ov->ih.rw_flags = 0;

    if (rw_flags == EVENT_READ) {
        DWORD flags = 0;

        if (!WSARecv(sd, &buf, 1, NULL, &flags, (OVERLAPPED *) ov,
                     (LPWSAOVERLAPPED_COMPLETION_ROUTINE) win32iocr_completion)
                || WSAGetLastError() == WSA_IO_PENDING)
            return;
    } else {
        if (!WSASend(sd, &buf, 1, NULL, 0, (OVERLAPPED *) ov,
                     (LPWSAOVERLAPPED_COMPLETION_ROUTINE) win32iocr_completion)
                || WSAGetLastError() == WSA_IO_PENDING)
            return;
    }
    ov->il.err = WSAGetLastError();
ready:
    win32iocr_list_put(iocr_thr->ov_list, ov);
}