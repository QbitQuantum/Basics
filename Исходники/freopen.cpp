static errno_t __cdecl common_freopen(
    FILE**             const result,
    Character const*   const file_name,
    Character const*   const mode,
    __crt_stdio_stream const stream,
    int                const share_flag
    ) throw()
{
    typedef __acrt_stdio_char_traits<Character> stdio_traits;

    _VALIDATE_RETURN_ERRCODE(result != nullptr, EINVAL);
    *result = nullptr;

    // C11 7.21.5.4/3:  "If filename is a null pointer, the freopen function
    // attempts to change the mode of the stream to that specified by mode, as
    // if the name of the file currently associated with the stream had been
    // used. It is implementation-defined which changes of mode are permitted
    // (if any), and under what circumstances."
    //
    // In our implementation, we do not currently support changing the mode
    // in this way.  In the future, we might consider use of ReOpenFile to
    // implement support for changing the mode.
    _VALIDATE_RETURN_ERRCODE_NOEXC(file_name != nullptr, EBADF);

    _VALIDATE_RETURN_ERRCODE(mode      != nullptr, EINVAL);
    _VALIDATE_RETURN_ERRCODE(stream.valid()      , EINVAL);

    // Just as in the common_fsopen function, we do not hard-validate empty
    // 'file_name' strings in this function:
    _VALIDATE_RETURN_ERRCODE_NOEXC(*file_name != 0, EINVAL);

    errno_t return_value = 0;

    _lock_file(stream.public_stream());
    __try
    {
        // If the stream is in use, try to close it, ignoring possible errors:
        if (stream.is_in_use())
            _fclose_nolock(stream.public_stream());

        stream->_ptr  = nullptr;
        stream->_base = nullptr;
        stream->_cnt  = 0;
        stream.unset_flags(-1);

        // We may have called fclose above, which will deallocate the stream.
        // We still hold the lock on the stream, though, so we can just reset
        // the allocated flag to retain ownership.
        stream.set_flags(_IOALLOCATED);

        *result = stdio_traits::open_file(file_name, mode, share_flag, stream.public_stream());
        if (*result == nullptr)
        {
            stream.unset_flags(_IOALLOCATED);
            return_value = errno;
        }
    }
    __finally
    {
        _unlock_file(stream.public_stream());
    }

    return return_value;
}