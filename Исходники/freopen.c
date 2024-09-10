errno_t __cdecl _tfreopen_helper(
    FILE** pfile,
    const _TSCHAR* filename,
    const _TSCHAR* mode,
    FILE* str,
    int shflag
) {
    REG1 FILE* stream;
    _VALIDATE_RETURN_ERRCODE((pfile != NULL), EINVAL);
    *pfile = NULL;
    _VALIDATE_RETURN_ERRCODE((filename != NULL), EINVAL);
    _VALIDATE_RETURN_ERRCODE((mode != NULL), EINVAL);
    _VALIDATE_RETURN_ERRCODE((str != NULL), EINVAL);

    /* We deliberately don't hard-validate for emptry strings here. All other invalid
    path strings are treated as runtime errors by the inner code in _open and openfile.
    This is also the appropriate treatment here. Since fopen is the primary access point
    for file strings it might be subjected to direct user input and thus must be robust to
    that rather than aborting. The CRT and OS do not provide any other path validator (because
    WIN32 doesn't allow such things to exist in full generality).
    */
    if (*filename == _T('\0')) {
        errno = EINVAL;
        return errno;
    }

    /* Init stream pointer */
    stream = str;
    _lock_str(stream);

    __try {
        /* If the stream is in use, try to close it. Ignore possible
         * error (ANSI 4.9.5.4). */
        if (inuse(stream)) {
            _fclose_nolock(stream);
        }

        stream->_ptr = stream->_base = NULL;
        stream->_cnt = stream->_flag = 0;
#ifdef _UNICODE
        *pfile = _wopenfile(filename, mode, shflag, stream);
#else  /* _UNICODE */
        *pfile = _openfile(filename, mode, shflag, stream);
#endif  /* _UNICODE */
    } __finally {
        _unlock_str(stream);
    }

    if (*pfile) {
        return 0;
    }

    return errno;
}