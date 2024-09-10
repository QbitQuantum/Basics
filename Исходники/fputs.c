int __cdecl fputs(
    const char* string,
    FILE* stream
) {
    REG2 int buffing;
    REG1 size_t length;
    REG3 size_t ndone;
    _VALIDATE_RETURN((string != NULL), EINVAL, EOF);
    _VALIDATE_RETURN((stream != NULL), EINVAL, EOF);
    _VALIDATE_STREAM_ANSI_RETURN(stream, EINVAL, EOF);
    length = strlen(string);
    _lock_str(stream);

    __try {
        buffing = _stbuf(stream);
        ndone = _fwrite_nolock(string, 1, length, stream);
        _ftbuf(buffing, stream);
    } __finally {
        _unlock_str(stream);
    }

    return (ndone == length ? 0 : EOF);
}