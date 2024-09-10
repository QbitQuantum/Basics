// Pushes a character ("ungets" it) back into a stream.  It is possible to push
// back one character.  It may not be possible to push back more than one
// character in a row.  Returns the pushed-back character on success; returns
// WEOF on failure.  Ungetting WEOF is expressly forbidden.
extern "C" wint_t __cdecl ungetwc(wint_t const c, FILE* const stream)
{
    _VALIDATE_RETURN(stream != nullptr, EINVAL, WEOF);

    wint_t return_value = WEOF;

    _lock_file(stream);
    __try
    {
        return_value = _ungetwc_nolock(c, stream);
    }
    __finally
    {
        _unlock_file(stream);
    }

    return return_value;
}