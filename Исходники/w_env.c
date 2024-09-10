LPVOID __cdecl __crtGetEnvironmentStringsW(
        VOID
        )
{
        static int f_use = 0;
        void *penv = NULL;
        char *pch;
        wchar_t *pwch;
        wchar_t *wbuffer;
        int total_size = 0;
        int str_size;

        /*
         * Look for unstubbed 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if ( 0 == f_use )
        {
            if ( NULL != (penv = GetEnvironmentStringsW()) )
                f_use = USE_W;

            else if ( NULL != (penv = GetEnvironmentStringsA()) )
                f_use = USE_A;
            else
                return NULL;
        }

        /* Use "W" version */

        if ( USE_W == f_use )
        {
            if ( NULL == penv )
                if ( NULL == (penv = GetEnvironmentStringsW()) )
                    return NULL;

            /* find out how big a buffer is needed */

            pwch = penv;
            while ( *pwch != L'\0' ) {
                if ( *++pwch == L'\0' )
                    pwch++;
            }

            total_size = (char *)pwch - (char *)penv + sizeof( wchar_t );

            /* allocate the buffer */

            if ( NULL == (wbuffer = _malloc_crt( total_size )) ) {
                FreeEnvironmentStringsW( penv );
                return NULL;
            }

            /* copy environment strings to buffer */

            memcpy( wbuffer, penv, total_size );

            FreeEnvironmentStringsW( penv );

            return (LPVOID)wbuffer;
        }

        /* Use "A" version */

        if ( USE_A == f_use )
        {
            /*
             * Convert strings and return the requested information.
             */
            if ( NULL == penv )
                if ( NULL == (penv = GetEnvironmentStringsA()) )
                    return NULL;

            pch = penv;

            /* find out how big a buffer we need */
            while ( *pch != '\0' )
            {
                if ( 0 == (str_size =
                      MultiByteToWideChar( __lc_codepage,
                                           MB_PRECOMPOSED,
                                           pch,
                                           -1,
                                           NULL,
                                           0 )) )
                    return 0;

                total_size += str_size;
                pch += strlen(pch) + 1;
            }

            /* room for final NULL */
            total_size++;

            /* allocate enough space for chars */
            if ( NULL == (wbuffer = (wchar_t *)
                 _malloc_crt( total_size * sizeof( wchar_t ) )) )
            {
                FreeEnvironmentStringsA( penv );
                return NULL;
            }

            /* do the conversion */
            pch = penv;
            pwch = wbuffer;
            while (*pch != '\0')
            {
                if ( 0 == MultiByteToWideChar( __lc_codepage,
                                               MB_PRECOMPOSED,
                                               pch,
                                               -1,
                                               pwch,
                                               total_size - (pwch -
                                                 wbuffer) ) )
                {
                    _free_crt( wbuffer );
                    FreeEnvironmentStringsA( penv );
                    return NULL;
                }

                pch += strlen(pch) + 1;
                pwch += wcslen(pwch) + 1;
            }
            *pwch = L'\0';

            FreeEnvironmentStringsA( penv );

            return (LPVOID)wbuffer;

        }
        else   /* f_use is neither USE_A nor USE_W */
            return NULL;
}