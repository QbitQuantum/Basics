UInt32
GUCEFSetEnv( const char* key   ,
             const char* value )
{GUCEF_TRACE;

    #ifdef GUCEF_MSWIN_BUILD

    UInt32 retval;
    char* envstr = (char*) malloc( strlen( key ) + strlen( value )+2 );
    sprintf( envstr, "%s=%s", key, value );
    retval = _putenv( envstr );
    free( envstr );
    return retval == 0;

    #else

    return setenv( key, value, 1 ) == 0;

    #endif
}