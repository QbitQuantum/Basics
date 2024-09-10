static int64_t wfile_seek(URLContext *h, int64_t pos, int whence)
{
#if defined(_MSC_VER)
    int fd = (intptr_t) h->priv_data;
    if (whence == AVSEEK_SIZE) 
    {
        struct _stat64 st;
        int ret = _fstat64(fd, &st);
        return ret < 0 ? AVERROR(errno) : st.st_size;
    }
    return _lseeki64(fd, pos, whence);
#else
    int fd = (intptr_t) h->priv_data;
    if (whence == AVSEEK_SIZE) 
    {
        struct stat st;
        int ret = fstat(fd, &st);
        return ret < 0 ? AVERROR(errno) : st.st_size;
    }
    return _lseeki64(fd, pos, whence);

#endif
}