/*
 * assume that b is lower case and allow plural
 */
static int specialcmplowerwiths (char *a,char *b)
{
    register char ca, cb;

    if (!a || !b)
        return 0;

    while (1)
    {
        ca = *a;
        cb = *b;
        if (isascii(ca) && isupper(ca))
        {  /* lowercasify */
#ifdef _tolower
            ca = _tolower (ca);
#else

            ca = tolower (ca);
#endif

        }
        if (ca != cb || ca == '\0')
            break;  /* if not eq else both nul */
        a++, b++;
    }
    if (cb == '\0' && (ca == '\0' || (ca == 's' && a[1] == '\0')))
        return 1;

    return 0;
}