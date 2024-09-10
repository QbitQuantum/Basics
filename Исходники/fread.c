/* define locking/unlocking version */
size_t __cdecl fread_s(
    void *buffer,
    size_t bufferSize,
    size_t elementSize,
    size_t count,
    FILE *stream
)
{
    size_t retval = 0;

    if (elementSize == 0 || count == 0)
    {
        return 0;
    }

    /* validation */
    _VALIDATE_RETURN((buffer != NULL), EINVAL, 0);
    if (stream == NULL || count > (SIZE_MAX / elementSize))
    {
        if (bufferSize != SIZE_MAX)
        {
            memset(buffer, _BUFFER_FILL_PATTERN, bufferSize);
        }

        _VALIDATE_RETURN((stream != NULL), EINVAL, 0);
        _VALIDATE_RETURN(count <= (SIZE_MAX / elementSize), EINVAL, 0);
    }

    _lock_str(stream);
    __try
    {
        /* do the read; _fread_nolock_s will make sure we do not buffer overrun */
        retval = _fread_nolock_s(buffer, bufferSize, elementSize, count, stream);
    }
    __finally
    {
        _unlock_str(stream);
    }

    return retval;
}