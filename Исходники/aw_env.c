LPVOID __cdecl __crtGetEnvironmentStringsA(
	VOID
	)
{
        static int f_use = 0;
	wchar_t *wEnv;
	wchar_t *wTmp;
	char *aEnv;
	char *aTmp;
	int nSizeW;
	int nSizeA;

        /* 
         * Look for 'preferred' flavor. Otherwise use available flavor.
         * Must actually call the function to ensure it's not a stub.
         */

        if ( 0 == f_use )
        {
            if ( NULL != (wEnv = GetEnvironmentStringsW()) )
                f_use = USE_W;

            else if ( NULL != (aEnv = GetEnvironmentStringsA()) )
                f_use = USE_A;

            else
                return NULL;
        }

        /* Use "W" version */

        if (USE_W == f_use)
        {
            /* obtain wide environment block */
	    if ( NULL == wEnv )
		if ( NULL == (wEnv = GetEnvironmentStringsW()) )
		    return NULL;

            /* look for double null that indicates end of block */
            wTmp = wEnv;
	    while ( *wTmp != L'\0' ) {
                if ( *++wTmp == L'\0' )
                    wTmp++;
            }

            /* calculate total size of block, including all nulls */
            nSizeW = wTmp - wEnv + 1;

            /* find out how much space needed for multi-byte environment */
            nSizeA = WideCharToMultiByte(   CP_ACP,
                                            0,
                                            wEnv,
                                            nSizeW,
                                            NULL,
                                            0,
                                            NULL,
                                            NULL );

            /* allocate space for multi-byte string */
            if ( (nSizeA == 0) || 
		 ((aEnv = (char *)_malloc_crt(nSizeA)) == NULL) )
	    {
		FreeEnvironmentStringsW( wEnv );
                return NULL;
	    }

            /* do the conversion */
            if ( !WideCharToMultiByte(  CP_ACP,
                                        0,
                                        wEnv,
                                        nSizeW,
                                        aEnv,
                                        nSizeA,
                                        NULL,
                                        NULL ) )
	    {
		_free_crt( aEnv );
                aEnv = NULL; 
	    }

            FreeEnvironmentStringsW( wEnv );
            return aEnv;
        }

        /* Use "A" version */

        if ( USE_A == f_use )
        {
	    if ( NULL == aEnv )
		if ( NULL == (aEnv = GetEnvironmentStringsA()) )
		    return NULL;

	    /* determine how big a buffer is needed */

	    aTmp = aEnv;

	    while ( *aTmp != '\0' ) {
		if ( *++aTmp == '\0' )
		    aTmp++;
	    }
	
	    nSizeA = aTmp - aEnv + 1;

	    if ( NULL == (aTmp = _malloc_crt( nSizeA )) ) {
		FreeEnvironmentStringsA( aEnv );
		return NULL;
	    }

	    memcpy( aTmp, aEnv, nSizeA );

	    FreeEnvironmentStringsA( aEnv );

	    return aTmp;
        }

        return NULL;
}