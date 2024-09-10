CxContext* icxGetContext()
{
#ifdef CX_DLL
#ifdef WIN32
    CxContext* pContext = (CxContext*)TlsGetValue( g_TlsIndex );
    if( !pContext )
    {
    pContext = icxCreateContext();

    if( !pContext )
    {
        FatalAppExit( 0, "OpenCX. Problem to allocate memory for TLS OpenCX context." );
    }
    TlsSetValue( g_TlsIndex, pContext );
    }
    return pContext;
#else
    CxContext* pContext = (CxContext*)pthread_getspecific( g_TlsIndex );
    if( !pContext )
    {
    pContext = icxCreateContext();
    if( !pContext )
    {
            fprintf(stderr,"OpenCX. Problem to allocate memory for OpenCX context.");
        exit(1);
    }
    pthread_setspecific( g_TlsIndex, pContext );
    }
    return pContext;
#endif
#else /* CX_DLL */
    static CxContext* pContext = 0;

    if( !pContext )
    pContext = icxCreateContext();

    return pContext;
#endif
}