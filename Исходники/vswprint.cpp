int __cdecl _vswprintf_helper (
    WOUTPUTFN woutfn,
    wchar_t *string,
    size_t count,
    const wchar_t *format,
    va_list ap
)
{
    miniFILE str;
    miniFILE *outfile = &str;
    int retval;

    _VALIDATE_RETURN( (format != NULL), EINVAL, -1);

    _VALIDATE_RETURN( (count == 0) || (string != NULL), EINVAL, -1 );

    outfile->_flag = _IOWRT|_IOSTRG;
    outfile->_ptr = outfile->_base = (char *) string;

    if(count>(INT_MAX/sizeof(wchar_t)))
    {
        /* old-style functions allow any large value to mean unbounded */
        outfile->_cnt = INT_MAX;
    }
    else
    {
        outfile->_cnt = (int)(count*sizeof(wchar_t));
    }

    retval = woutfn(outfile, format, ap );

    if(string==NULL)
    {
        return retval;
    }

    if((retval >= 0) && (_putc_nolock('\0',outfile) != EOF) && (_putc_nolock('\0',outfile) != EOF))
        return(retval);

    string[count - 1] = 0;
    if (outfile->_cnt < 0)
    {
        /* the buffer was too small; we return -2 to indicate truncation */
        return -2;
    }
    return -1;
}