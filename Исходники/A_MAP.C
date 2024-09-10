static int __cdecl __crtLCMapStringA_stat(
        _locale_t plocinfo,
        LPCWSTR  LocaleName,
        DWORD    dwMapFlags,
        LPCSTR   lpSrcStr,
        int      cchSrc,
        LPSTR    lpDestStr,
        int      cchDest,
        int      code_page,
        BOOL     bError
        )
{
    /*
     * LCMapString will map past NULL. Must find NULL if in string
     * before cchSrc characters.
     */
    if (cchSrc > 0) {
        int cchSrcCnt = strncnt(lpSrcStr, cchSrc);
        /*
         * Include NULL in cchSrc if lpSrcStr terminated within cchSrc bytes.
         */
        if (cchSrcCnt < cchSrc) {
            cchSrc = cchSrcCnt + 1;
        } else {
            cchSrc = cchSrcCnt;
        }
    }

    int retval = 0;
    int inbuff_size;
    int outbuff_size;
    wchar_t *inwbuffer = NULL;
    wchar_t *outwbuffer = NULL;

    /*
     * Convert string and return the requested information. Note that
     * we are converting to a wide string so there is not a
     * one-to-one correspondence between number of wide chars in the
     * input string and the number of *bytes* in the buffer. However,
     * there had *better be* a one-to-one correspondence between the
     * number of wide characters and the number of multibyte characters
     * or the resulting mapped string will be worthless to the user.
     */

    /*
     * Use __lc_codepage for conversion if code_page not specified
     */

    if (0 == code_page)
        code_page = plocinfo->locinfo->lc_codepage;

    /* find out how big a buffer we need (includes NULL if any) */
    if ( 0 == (inbuff_size =
               MultiByteToWideChar( code_page,
                                    bError ? MB_PRECOMPOSED |
                                        MB_ERR_INVALID_CHARS :
                                        MB_PRECOMPOSED,
                                    lpSrcStr,
                                    cchSrc,
                                    NULL,
                                    0 )) )
        return 0;

    /* allocate enough space for wide chars */
    inwbuffer = (wchar_t *)_calloca( inbuff_size, sizeof(wchar_t) );
    if ( inwbuffer == NULL ) {
        return 0;
    }

    /* do the conversion */
    if ( 0 == MultiByteToWideChar( code_page,
                                   MB_PRECOMPOSED,
                                   lpSrcStr,
                                   cchSrc,
                                   inwbuffer,
                                   inbuff_size) )
        goto error_cleanup;

    /* get size required for string mapping */
    if ( 0 == (retval = __crtLCMapStringEx( LocaleName,
                                      dwMapFlags,
                                      inwbuffer,
                                      inbuff_size,
                                      NULL,
                                      0)) )
        goto error_cleanup;

    if (dwMapFlags & LCMAP_SORTKEY) {
        /* retval is size in BYTES */

        if (0 != cchDest) {

            if (retval > cchDest)
                goto error_cleanup;

            /* do string mapping */
            if ( 0 == __crtLCMapStringEx( LocaleName,
                                    dwMapFlags,
                                    inwbuffer,
                                    inbuff_size,
                                    (LPWSTR)lpDestStr,
                                    cchDest) )
                goto error_cleanup;
        }
    }
    else {
        /* retval is size in wide chars */

        outbuff_size = retval;

        /* allocate enough space for wide chars (includes NULL if any) */
        outwbuffer = (wchar_t *)_calloca( outbuff_size, sizeof(wchar_t) );
        if ( outwbuffer == NULL ) {
            goto error_cleanup;
        }

        /* do string mapping */
        if ( 0 == __crtLCMapStringEx( LocaleName,
                                dwMapFlags,
                                inwbuffer,
                                inbuff_size,
                                outwbuffer,
                                outbuff_size) )
            goto error_cleanup;

        if (0 == cchDest) {
            /* get size required */
            if ( 0 == (retval =
                       WideCharToMultiByte( code_page,
                                            0,
                                            outwbuffer,
                                            outbuff_size,
                                            NULL,
                                            0,
                                            NULL,
                                            NULL )) )
                goto error_cleanup;
        }
        else {
            /* convert mapping */
            if ( 0 == (retval =
                       WideCharToMultiByte( code_page,
                                            0,
                                            outwbuffer,
                                            outbuff_size,
                                            lpDestStr,
                                            cchDest,
                                            NULL,
                                            NULL )) )
                goto error_cleanup;
        }
    }

error_cleanup:
    if ( outwbuffer != NULL )
        _freea(outwbuffer);

    _freea(inwbuffer);

    return retval;
}