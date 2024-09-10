// Writes data from the provided buffer to the specified stream.  The function
// writes 'count' elements of 'size' size to the stream, and returns when
// either all of the elements have been written or no more data can be written
// (e.g. if EOF is encountered or an error occurs).
//
// Returns the number of "whole" elements that were written to the stream.  This
// may be fewer than the requested number of an error occurs or EOF is encountered.
// In this case, ferror() or feof() should be used to distinguish between the two
// conditions.
extern "C" size_t __cdecl fwrite(
    void const* const buffer,
    size_t      const size,
    size_t      const count,
    FILE*       const stream
    )
{
    if (size == 0 || count == 0)
        return 0;

    // The _nolock version will do the rest of the validation.
    _VALIDATE_RETURN(stream != nullptr, EINVAL, 0);

    return __acrt_lock_stream_and_call(stream, [&]() -> size_t
    {
        __acrt_stdio_temporary_buffering_guard const buffering(stream);

        return _fwrite_nolock(buffer, size, count, stream);
    });
}