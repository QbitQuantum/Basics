int __cdecl _getw(
    FILE* str
) {
    REG1 FILE* stream;
    REG2 int bytecount = sizeof(int);
    int word;
    char* byteptr = (char*)&word;
    int retval;
    _VALIDATE_RETURN((str != NULL), EINVAL, EOF);
    /* Init stream pointer */
    stream = str;
    _lock_str(stream);

    __try {
        while (bytecount--) {
            *byteptr++ = (char)_getc_nolock(stream);
        }

        retval = ((feof(stream) || ferror(stream)) ? EOF : word);
    } __finally {
        _unlock_str(stream);
    }

    return (retval);
}