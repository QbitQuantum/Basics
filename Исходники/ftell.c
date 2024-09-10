long __cdecl ftell(
    FILE* stream
) {
    long retval;
    _VALIDATE_RETURN((stream != NULL), EINVAL, (-1L));
    _lock_str(stream);

    __try {
        retval = _ftell_nolock(stream);
    } __finally {
        _unlock_str(stream);
    }

    return (retval);
}