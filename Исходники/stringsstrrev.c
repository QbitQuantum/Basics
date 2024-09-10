/*----------------------------------------------------------------------------*/
char* scistrrev(char* str)
{
    char *revstr = NULL;
    if (str)
    {
        wchar_t *wcstr = to_wide_string(str);
#ifdef _MSC_VER
        wchar_t *wcrevstr = _wcsrev(wcstr);
        revstr = wide_string_to_UTF8(wcrevstr);
#else
        int i = 0;
        int t = 0;
        int j = 0, k = 0;

        if (wcstr)
        {
            i = (int)wcslen(wcstr);
        }
        t = !(i % 2) ? 1 : 0;   // check the length of the string .

        /* copy character by character to reverse string */
        k = 0;
        for (j = i - 1; j > (i / 2 - t) ; j-- )
        {
            /* j starts from end of string */
            /* k starts from beginning of string */
            wchar_t ch  = wcstr[j]; /* ch temp. character */
            wcstr[j]   = wcstr[k]; /* end and beginning characters are exchanged */
            wcstr[k++] = ch;
        }
        revstr = wide_string_to_UTF8(wcstr);
#endif
        FREE(wcstr);
    }
    return revstr;
}