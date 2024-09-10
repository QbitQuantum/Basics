errno_t __cdecl rand_s
(
    unsigned int *_RandomValue
)
{
    PGENRANDOM pfnRtlGenRandom = (PGENRANDOM) DecodePointer(g_pfnRtlGenRandom);
    _VALIDATE_RETURN_ERRCODE( _RandomValue != NULL, EINVAL );
    *_RandomValue = 0; // Review : better value to initialize it to?

    if ( pfnRtlGenRandom == NULL )
    {
        PGENRANDOM encoded;
        void* enull;
#ifdef _CORESYS
#define RAND_DLL L"cryptbase.dll"
#else  /* _CORESYS */
#define RAND_DLL L"ADVAPI32.DLL"
#endif  /* _CORESYS */
        // advapi32.dll/cryptbase.dll is unloaded when the App exits.
        HMODULE hRandDll = LoadLibraryExW(RAND_DLL, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
#ifndef _CORESYS
        if (!hRandDll && GetLastError() == ERROR_INVALID_PARAMETER)
        {
            // LOAD_LIBRARY_SEARCH_SYSTEM32 is not supported on this platfrom,
            // try one more time using default options
            hRandDll = LoadLibraryExW(RAND_DLL, NULL, 0);
        }
#endif  /* _CORESYS */
        if (!hRandDll)
        {
            _VALIDATE_RETURN_ERRCODE(("rand_s is not available on this platform", 0), EINVAL);
        }

        pfnRtlGenRandom = ( PGENRANDOM ) GetProcAddress( hRandDll, _TO_STR( RtlGenRandom ) );
        if ( pfnRtlGenRandom == NULL )
        {
            _VALIDATE_RETURN_ERRCODE(("rand_s is not available on this platform", 0), _get_errno_from_oserr(GetLastError()));
        }
        encoded = (PGENRANDOM) EncodePointer(pfnRtlGenRandom);
        enull = EncodePointer(NULL);
#ifdef _M_IX86
        if ( (void*)(LONG_PTR)InterlockedExchange(
                ( LONG* )&g_pfnRtlGenRandom,
                ( LONG )( LONG_PTR )encoded)
            != enull )
#else  /* _M_IX86 */
        if ( InterlockedExchangePointer(
                ( void** )&g_pfnRtlGenRandom,
                ( void* )encoded)
            != enull )
#endif  /* _M_IX86 */
        {
            /* A different thread has already loaded advapi32.dll/cryptbase.dll. */
            FreeLibrary( hRandDll );
        }
    }

    if ( !(*pfnRtlGenRandom)( _RandomValue, ( ULONG )sizeof( unsigned int ) ) )
    {
        errno = ENOMEM;
        return errno;
    }
    return 0;
}