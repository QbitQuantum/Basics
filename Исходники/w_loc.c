static int __cdecl __crtGetLocaleInfoW_stat(
    _locale_t plocinfo,
    LCID    Locale,
    LCTYPE  LCType,
    LPWSTR  lpLCData,
    int     cchData,
    int     code_page
) {
    static int f_use = 0;

    /*
     * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
     * Must actually call the function to ensure it's not a stub.
     */

    if (0 == f_use) {
        if (0 != GetLocaleInfoW(0, LOCALE_ILANGUAGE, NULL, 0)) {
            f_use = USE_W;
        } else if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED) {
            f_use = USE_A;
        }
    }

    /* Use "W" version */

    if (USE_W == f_use) {
        return GetLocaleInfoW(Locale, LCType, lpLCData, cchData);
    }

    /* Use "A" version */

    if (USE_A == f_use || f_use == 0) {
        int retval = 0;
        int buff_size;
        unsigned char* buffer;

        /*
         * Use __lc_codepage for conversion if code_page not specified
         */

        if (0 == code_page) {
            code_page = plocinfo->locinfo->lc_codepage;
        }

        /* find out how big buffer needs to be */
        if (0 == (buff_size = GetLocaleInfoA(Locale, LCType, NULL, 0))) {
            return 0;
        }

        /* allocate buffer */
        buffer = (unsigned char*)_calloca(buff_size, sizeof(char));

        if (buffer == NULL) {
            return 0;
        }

        /* get the info in ANSI format */
        if (0 == GetLocaleInfoA(Locale, LCType, (char*)buffer, buff_size)) {
            goto error_cleanup;
        }

        if (0 == cchData) {
            /* find out how much space needed */
            retval = MultiByteToWideChar(code_page,
                                         MB_PRECOMPOSED,
                                         (const char*)buffer,
                                         -1,
                                         NULL,
                                         0);
        } else {
            /* convert into user buffer */
            retval = MultiByteToWideChar(code_page,
                                         MB_PRECOMPOSED,
                                         (const char*)buffer,
                                         -1,
                                         lpLCData,
                                         cchData);
        }

    error_cleanup:
        _freea(buffer);
        return retval;
    } else { /* f_use is neither USE_A nor USE_W */
        return 0;
    }
}