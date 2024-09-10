int __cdecl __crtCompareStringW(
        LCID     Locale,
        DWORD    dwCmpFlags,
        LPCWSTR  lpString1,
        int      cchCount1,
        LPCWSTR  lpString2,
        int      cchCount2,
        int      code_page
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if (0 == f_use)
        {
            if (0 != CompareStringW(0, 0, L"\0", 1, L"\0", 1))
                f_use = USE_W;

            else if (0 != CompareStringA(0, 0, "\0", 1, "\0", 1))
                f_use = USE_A;

            else
                return 0;
        }

        /*
         * CompareString will compare past NULL. Must find NULL if in string
         * before cchCountn wide characters.
         */

        if (cchCount1 > 0)
            cchCount1= wcsncnt(lpString1, cchCount1);
        if (cchCount2 > 0)
            cchCount2= wcsncnt(lpString2, cchCount2);

        if (!cchCount1 || !cchCount2)
            return (cchCount1 - cchCount2 == 0) ? 2 :
                   (cchCount1 - cchCount2 < 0) ? 1 : 3;

        /* Use "W" version */

        if (USE_W == f_use)
        {
            return CompareStringW( Locale,
                                   dwCmpFlags,
                                   lpString1,
                                   cchCount1,
                                   lpString2,
                                   cchCount2 );
        }

        /* Use "A" version */

        if (USE_A == f_use)
        {
            int buff_size1;
            int buff_size2;
            unsigned char *buffer1;
            unsigned char *buffer2;

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /*
             * Convert strings and return the requested information.
             */

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (buff_size1 = WideCharToMultiByte( code_page,
                                                         WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                         lpString1,
                                                         cchCount1,
                                                         NULL,
                                                         0,
                                                         NULL,
                                                         NULL )) )
                return 0;

            /* allocate enough space for chars */
            __try {
                buffer1 = (unsigned char *)_alloca( buff_size1 * sizeof(char) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                buffer1 = NULL;
            }

            if ( buffer1 == NULL )
                return 0;

            /* do the conversion */
            if ( 0 == WideCharToMultiByte( code_page,
                                           WC_COMPOSITECHECK | WC_SEPCHARS,
                                           lpString1,
                                           cchCount1,
                                           buffer1,
                                           buff_size1,
                                           NULL,
                                           NULL ) )
                return 0;

            /* find out how big a buffer we need (includes NULL if any) */
            if ( 0 == (buff_size2 = WideCharToMultiByte( code_page,
                                                         WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                         lpString2,
                                                         cchCount2,
                                                         NULL,
                                                         0,
                                                         NULL,
                                                         NULL )) )
                return 0;

            /* allocate enough space for chars */
            __try {
                buffer2 = (unsigned char *)_alloca( buff_size2 * sizeof(char) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                buffer2 = NULL;
            }

            if ( buffer2 == NULL )
                return 0;

            /* do the conversion */
            if ( 0 == WideCharToMultiByte( code_page,
                                           WC_COMPOSITECHECK | WC_SEPCHARS,
                                           lpString2,
                                           cchCount2,
                                           buffer2,
                                           buff_size2,
                                           NULL,
                                           NULL ) )
                return 0;

            return CompareStringA( Locale,
                                   dwCmpFlags,
                                   buffer1,
                                   buff_size1,
                                   buffer2,
                                   buff_size2 );
        }