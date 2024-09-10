int __cdecl fputws (
        const wchar_t *string,
        FILE *stream
        )
{
        size_t length;
        int retval = 0;

        _VALIDATE_RETURN((string != NULL), EINVAL, WEOF);
        _VALIDATE_RETURN((stream != NULL), EINVAL, WEOF);

        length = wcslen(string);

        _lock_str(stream);
        __try {

        while (length--)
        {
            if (_putwc_nolock(*string++, stream) == WEOF)
            {
                retval = -1;
                break;
            }
        }

        }
        __finally {
            _unlock_str(stream);
        }

        return(retval);
}