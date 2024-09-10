errno_t __cdecl _tctime64_s (
        _TSCHAR * buffer,
        size_t sizeInChars,
        const __time64_t *timp
        )
{
        struct tm tmtemp;
        errno_t e;

        _VALIDATE_RETURN_ERRCODE(
            ( ( buffer != NULL ) && ( sizeInChars > 0 ) ),
            EINVAL
        )

        _RESET_STRING(buffer, sizeInChars);

        _VALIDATE_RETURN_ERRCODE( ( timp != NULL ), EINVAL )
        _VALIDATE_RETURN_ERRCODE_NOEXC( ( *timp >= 0 ), EINVAL )

        e = _localtime64_s(&tmtemp, timp);
        if ( e == 0 )
        {
            e = _tasctime_s(buffer, sizeInChars, &tmtemp);
        }
        return e;
}