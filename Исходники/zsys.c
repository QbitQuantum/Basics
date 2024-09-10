char *
zsys_vprintf (const char *format, va_list argptr)
{
    int size = 256;
    char *string = (char *) malloc (size);
    int required = vsnprintf (string, size, format, argptr);
#if defined (__WINDOWS__)
    if (required < 0 || required >= size)
        required = _vscprintf (format, argptr);
#endif
    //  If formatted string cannot fit into small string, reallocate a
    //  larger buffer for it.
    if (required >= size) {
        size = required + 1;
        string = (char *) realloc (string, size);
        if (!string)
            return NULL;
        vsnprintf (string, size, format, argptr);
    }
    return string;
}