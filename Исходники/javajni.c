/* a hook for a function that redirects all VM messages. */
static jint JNICALL __apxJniVfprintf(FILE *fp, const char *format, va_list args)
{
    jint rv;
    CHAR sBuf[1024+16];
    rv = wvsprintfA(sBuf, format, args);
    if (apxLogWrite(APXLOG_MARK_INFO "%s", sBuf) == 0)
        fputs(sBuf, stdout);
    return rv;
}