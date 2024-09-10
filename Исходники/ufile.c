U_CAPI UFILE* U_EXPORT2
u_fopen_u(const UChar   *filename,
        const char    *perm,
        const char    *locale,
        const char    *codepage)
{
    UFILE     *result;
    char buffer[256];

    u_austrcpy(buffer, filename);

    result = u_fopen(buffer, perm, locale, codepage);
#if U_PLATFORM_USES_ONLY_WIN32_API
    /* Try Windows API _wfopen if the above fails. */
    if (!result) {
        FILE *systemFile = _wfopen(filename, (UChar*)perm);
        if (systemFile) {
            result = finit_owner(systemFile, locale, codepage, TRUE);
        }
        if (!result) {
            /* Something bad happened.
               Maybe the converter couldn't be opened. */
            fclose(systemFile);
        }
    }
#endif
    return result; /* not a file leak */
}