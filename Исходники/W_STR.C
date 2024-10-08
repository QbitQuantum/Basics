BOOL __cdecl __crtGetStringTypeW(
        DWORD    dwInfoType,
        LPCWSTR  lpSrcStr,
        int      cchSrc,
        LPWORD   lpCharType,
        int      code_page,
        int      lcid
        )
{
        static int f_use = 0;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if (0 == f_use)
        {
            unsigned short dummy;

            if (0 != GetStringTypeW(CT_CTYPE1, L"\0", 1, &dummy))
                f_use = USE_W;

            else if (0 != GetStringTypeA(0, CT_CTYPE1, "\0", 1, &dummy))
                f_use = USE_A;

            else
                return FALSE;
        }

        /* Use "W" version */

        if (USE_W == f_use)
        {
            return GetStringTypeW(dwInfoType, lpSrcStr, cchSrc, lpCharType);
        }

        /* Use "A" version */

        if (USE_A == f_use)
        {
            int buff_size;
            BOOL retbool;
            unsigned char *buffer;
            WORD * pwCharInfo;

            /*
             * Convert string and return the requested information. Note that
             * we are converting to a multibyte string so there is not a
             * one-to-one correspondence between number of wide chars in the
             * input string and the number of *bytes* in the buffer. However,
             * there had *better be* a one-to-one correspondence between the
             * number of wide characters and the number of WORDs in the
             * return buffer.
             */

            /*
             * Use __lc_codepage for conversion if code_page not specified
             */

            if (0 == code_page)
                code_page = __lc_codepage;

            /* find out how big a buffer we need */
            if ( 0 == (buff_size = WideCharToMultiByte( code_page,
                                                        WC_COMPOSITECHECK |
                                                            WC_SEPCHARS,
                                                        lpSrcStr,
                                                        cchSrc,
                                                        NULL,
                                                        0,
                                                        NULL,
                                                        NULL )) )
                return FALSE;

            /* allocate enough space for chars */
            __try {
                buffer = (unsigned char *)_alloca( sizeof(char) * buff_size );
                (void)memset( buffer, 0, sizeof(char) * buff_size );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                buffer = NULL;
            }

            if ( buffer == NULL )
                return FALSE;

            /* do the conversion */
            if ( 0 == WideCharToMultiByte( code_page,
                                           WC_COMPOSITECHECK | WC_SEPCHARS,
                                           lpSrcStr,
                                           cchSrc,
                                           buffer,
                                           buff_size,
                                           NULL,
                                           NULL ) )
                return FALSE;

            /* allocate enough space for result (+1 for sanity check) */
            __try {
                pwCharInfo = (WORD *)_alloca( sizeof(WORD) * (buff_size + 1) );
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) {
                pwCharInfo = NULL;
            }

            if ( pwCharInfo == NULL )
                return FALSE;

            /* do we use default lcid */
            if (0 == lcid)
                lcid = __lc_handle[LC_CTYPE];

            /* set to known value */
            pwCharInfo[cchSrc - 1] = pwCharInfo[cchSrc] = 0xFFFF;

            /* obtain result */
            retbool = GetStringTypeA( lcid, dwInfoType, buffer, buff_size,
                                      pwCharInfo );

            /*
             * GetStringTypeA does not reveal how many WORDs have been
             * modifed - to be safe we use another buffer and then
             * verify that EXACTLY cchSrc WORDs were modified. Note that
             * not all multibyte LCID/codepage combos are guaranteed to work.
             */

            if (pwCharInfo[cchSrc - 1] == 0xFFFF || pwCharInfo[cchSrc] != 0xFFFF)
                return FALSE;

            memmove(lpCharType, pwCharInfo, cchSrc * sizeof(WORD));

            return retbool;
        }