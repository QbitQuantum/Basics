int win_open(const char *pathname, int flags, ...)
{
    va_list args;
    mode_t mode;
    int fd;
    wchar_t *winpath;

    va_start(args, flags);
    mode = va_arg(args, int);

    va_end(args);

    winpath = intpath2winpath(pathname);
    if (!winpath) {
	errno = EINVAL;
	return -1;
    }

    fd = _wopen(winpath, flags | O_BINARY, mode);
    free(winpath);
    if (fd < 0) {
	return fd;
    }

    return add_fdname(fd, pathname);

}