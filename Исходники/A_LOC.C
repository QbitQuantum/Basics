int __cdecl __crtGetLocaleInfoA(
        LCID    Locale,
        LCTYPE  LCType,
        LPSTR   lpLCData,
        int     cchData,
        int     code_page
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if (0 == f_use)
        {
            if (0 != GetLocaleInfoW(0, LOCALE_ILANGUAGE, NULL, 0))
                f_use = USE_W;

            else if (0 != GetLocaleInfoA(0, LOCALE_ILANGUAGE, NULL, 0))
                f_use = USE_A;

            else
                return 0;
        }

        /* Use "A" version */

        if (USE_A == f_use)
        {
            return GetLocaleInfoA(Locale, LCType, lpLCData, cchData);
        }

        /* Use "W" version */

        if (USE_W == f_use)
        {
            int retval;
            int buff_size;
            wchar_t *wbuffer;

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /* find out how big buffer needs to be */
            if (0 == (buff_size = GetLocaleInfoW(Locale, LCType, NULL, 0)))
                return 0;

            /* allocate buffer */
            __try {
                wbuffer = (wchar_t *)_alloca( buff_size * sizeof(wchar_t) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                wbuffer = NULL;
            }

            if ( wbuffer == NULL )
                return 0;

            /* get the info in wide format */
            if (0 == GetLocaleInfoW(Locale, LCType, wbuffer, buff_size))
                return 0;

            /* convert from Wide Char to ANSI */
            if (0 == cchData)
            {
                /* convert into local buffer */
                retval = WideCharToMultiByte( code_page,
                                              WC_COMPOSITECHECK | WC_SEPCHARS,
                                              wbuffer,
                                              -1,
                                              NULL,
                                              0,
                                              NULL,
                                              NULL );
            }
            else {
                /* convert into user buffer */
                retval = WideCharToMultiByte( code_page,
                                              WC_COMPOSITECHECK | WC_SEPCHARS,
                                              wbuffer,
                                              -1,
                                              lpLCData,
                                              cchData,
                                              NULL,
                                              NULL );
            }

            return retval;
        }