int
APIENTRY
lstrcmpA(
    LPCSTR lpString1,
    LPCSTR lpString2
    )
{
    int retval;

    retval = CompareStringA( GetThreadLocale(),
                             LOCALE_USE_CP_ACP,
                             lpString1,
                             -1,
                             lpString2,
                             -1 );
    if (retval == 0)
    {
        //
        // The caller is not expecting failure.  Try the system
        // default locale id.
        //
        retval = CompareStringA( GetSystemDefaultLCID(),
                                 LOCALE_USE_CP_ACP,
                                 lpString1,
                                 -1,
                                 lpString2,
                                 -1 );
    }

    if (retval == 0)
    {
        if (lpString1 && lpString2)
        {
            //
            // The caller is not expecting failure.  We've never had a
            // failure indicator before.  We'll do a best guess by calling
            // the C runtimes to do a non-locale sensitive compare.
            //
            return strcmp(lpString1, lpString2);
        }
        else if (lpString1)
        {
            return (1);
        }
        else if (lpString2)
        {
            return (-1);
        }
        else
        {
            return (0);
        }
    }

    return (retval - 2);
}