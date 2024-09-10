/*************************************************************************
* Custom mscanf() routine
**************************************************************************/
int mscanf(char *format,...)
{
    char *new_format;
    int rc;
    va_list argp;

    gk_strstr_replace(format, D_PATTERN, D_SCAN_REPLACEMENT, "g", &new_format);

    /*mprintf("new_format: %s\n", new_format);*/

    va_start(argp, format);
    rc = vscanf((char *)new_format, argp);
    va_end(argp);

    gk_free((void **)&new_format, LTERM);

    return rc;
}