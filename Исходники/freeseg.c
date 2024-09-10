static int DoFreeSeg( __segment seg )
{
    #if defined(__WINDOWS_286__)
        HANDLE hmem;

        hmem = (HANDLE)GlobalHandle( seg );
        if( hmem == NULL ) {
            return( -1 );
        }
        GlobalUnlock( hmem );
        if( GlobalFree( hmem ) == hmem ) {
            return( -1 );
        }
        return( 0 );
    #else
        return( DosFreeSeg( seg ) );
    #endif
}