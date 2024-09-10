static errno_t __cdecl _wcslwr_s_l_stat (
        wchar_t * wsrc,
        size_t sizeInWords,
        _locale_t plocinfo
        )
{

    wchar_t *p;             /* traverses string for C locale conversion */
    wchar_t *wdst;          /* wide version of string in alternate case */
    int dstsize;            /* size in wide chars of wdst string buffer (include null) */
    errno_t e = 0;
    size_t stringlen;

    /* validation section */
    _VALIDATE_RETURN_ERRCODE(wsrc != NULL, EINVAL);
    stringlen = wcsnlen(wsrc, sizeInWords);
    if (stringlen >= sizeInWords)
    {
        _RESET_STRING(wsrc, sizeInWords);
        _RETURN_DEST_NOT_NULL_TERMINATED(wsrc, sizeInWords);
    }
    _FILL_STRING(wsrc, sizeInWords, stringlen + 1);

    if ( plocinfo->locinfo->locale_name[LC_CTYPE] == NULL)
    {
        for ( p = wsrc ; *p ; p++ )
        {
            if ( (*p >= (wchar_t)L'A') && (*p <= (wchar_t)L'Z') )
            {
                *p -= L'A' - L'a';
            }
        }

        return 0;
    }   /* C locale */

    /* Inquire size of wdst string */
    if ( (dstsize = __crtLCMapStringW(
                    plocinfo->locinfo->locale_name[LC_CTYPE],
                    LCMAP_LOWERCASE,
                    wsrc,
                    -1,
                    NULL,
                    0
                    )) == 0 )
    {
        errno = EILSEQ;
        return errno;
    }

    if (sizeInWords < (size_t)dstsize)
    {
        _RESET_STRING(wsrc, sizeInWords);
        _RETURN_BUFFER_TOO_SMALL(wsrc, sizeInWords);
    }

    /* Allocate space for wdst */
    wdst = (wchar_t *)_calloca(dstsize, sizeof(wchar_t));
    if (wdst == NULL)
    {
        errno = ENOMEM;
        return errno;
    }

    /* Map wrc string to wide-character wdst string in alternate case */
    if (__crtLCMapStringW(
                plocinfo->locinfo->locale_name[LC_CTYPE],
                LCMAP_LOWERCASE,
                wsrc,
                -1,
                wdst,
                dstsize
                ) != 0)
    {
        /* Copy wdst string to user string */
        e = wcscpy_s(wsrc, sizeInWords, wdst);
    }
    else
    {
        e = errno = EILSEQ;
    }

    _freea(wdst);

    return e;
}