int __cdecl _putw (
        int word,
        FILE *str
        )
{
        REG1 FILE *stream;
        REG3 int bytecount = sizeof(int);
        REG2 char *byteptr = (char *)&word;
        int retval;

        _VALIDATE_RETURN((str != NULL), EINVAL, EOF);

        /* Init stream pointer */
        stream = str;

        _lock_str(stream);
        __try {

        while (bytecount--)
        {
            _putc_nolock(*byteptr,stream);
            ++byteptr;
        }
        retval = (ferror(stream) ? EOF : word);

        }
        __finally {
            _unlock_str(stream);
        }

        return(retval);
}