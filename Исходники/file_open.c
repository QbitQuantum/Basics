static int win32_open(const char *filename_utf8, int oflag, int pmode)
{
    int fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    if (utf8towchar(filename_utf8, &filename_w))
        return -1;
    if (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    if (fd != -1 || (oflag & O_CREAT))
        return fd;

fallback:
    /* filename may be in CP_ACP */
    return _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}