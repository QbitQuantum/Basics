    /* parse headers for Content-Length */
    size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream) {
        int r;
        long len = 0;

#if defined(Q_OS_WIN)
        /* _snscanf() is Win32 specific */
        r = _snscanf((const char *)ptr, size * nmemb, "Content-Length: %ld\n", &len);
#else
        r = std::sscanf((const char *)ptr, "Content-Length: %ld\n", &len);
#endif

        if (r) { /* Microsoft: we don't read the specs */
            *((long *)stream) = len;
        }

        return size * nmemb;
    }