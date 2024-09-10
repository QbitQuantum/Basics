static ssize_t fd_write(hFILE *fpv, const void *buffer, size_t nbytes)
{
    hFILE_fd *fp = (hFILE_fd *) fpv;
    ssize_t n;
    do {
        n = write(fp->fd, buffer, nbytes);
    } while (n < 0 && errno == EINTR);
#ifdef _WIN32
        // On windows we have no SIGPIPE.  Instead write returns
        // EINVAL.  We check for this and our fd being a pipe.
        // If so, we raise SIGTERM instead of SIGPIPE.  It's not
        // ideal, but I think the only alternative is extra checking
        // in every single piece of code.
        if (n < 0 && errno == EINVAL &&
            GetLastError() == ERROR_NO_DATA &&
            GetFileType((HANDLE)_get_osfhandle(fp->fd)) == FILE_TYPE_PIPE) {
            raise(SIGTERM);
        }
#endif
    return n;
}