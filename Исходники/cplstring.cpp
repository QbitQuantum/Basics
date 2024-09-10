CPLString CPLOPrintf( const char *pszFormat, ... )

{
    va_list args;
    va_start( args, pszFormat );

    CPLString osTarget;
    osTarget.vPrintf( pszFormat, args );

    va_end( args );

    return osTarget;
}