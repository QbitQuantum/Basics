/* Unlocks a file. */
static void unlock(MVMThreadContext *tc, MVMOSHandle *h) {
    MVMIOFileData *data = (MVMIOFileData *)h->body.data;

#ifdef _WIN32

    const DWORD len = 0xffffffff;
    const HANDLE hf = (HANDLE)_get_osfhandle(data->fd);
    OVERLAPPED offset;

    if (hf == INVALID_HANDLE_VALUE) {
        MVM_exception_throw_adhoc(tc, "Failed to seek in filehandle: bad file descriptor");
    }

    memset (&offset, 0, sizeof(offset));
    MVM_gc_mark_thread_blocked(tc);
    if (UnlockFileEx(hf, 0, len, len, &offset)) {
        MVM_gc_mark_thread_unblocked(tc);
        return;
    }
    MVM_gc_mark_thread_unblocked(tc);

    MVM_exception_throw_adhoc(tc, "Failed to unlock filehandle: %d", GetLastError());
#else

    struct flock l;
    ssize_t r;
    const int fd = data->fd;

    l.l_whence = SEEK_SET;
    l.l_start = 0;
    l.l_len = 0;
    l.l_type = F_UNLCK;

    do {
        MVM_gc_mark_thread_blocked(tc);
        r = fcntl(fd, F_SETLKW, &l);
        MVM_gc_mark_thread_unblocked(tc);
    } while (r == -1 && errno == EINTR);

    if (r == -1) {
        MVM_exception_throw_adhoc(tc, "Failed to unlock filehandle: %d", errno);
    }
#endif
}