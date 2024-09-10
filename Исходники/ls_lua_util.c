ls_lua_api_t * ls_lua_dl_loadModule( const char * name, char * errbuf )
{
    register ls_lua_api_t   *dlp;

    errbuf[0] = 0;
    if ( (dlp = findModuleByName( name )) )
    {
        return dlp;
    }
    dlp = ( ls_lua_api_t * )malloc( sizeof( ls_lua_api_t ) + strlen( name ) + 1 );
    if ( !dlp )
    {
        snprintf( errbuf, MAX_ERRBUF_SIZE, "NO MEMORY" );
        return NULL;
    }
    if ( !( dlp->moduleName = strdup( name ) ) )
    {
        snprintf( errbuf, MAX_ERRBUF_SIZE, "NO MEMORY" );
        free( dlp );
        return NULL;
    }

    if ( loadModule( dlp, errbuf ) )
    {
        /* problem in load module */
        free( dlp->moduleName );
        free( dlp );
        return NULL;
    }
    return dlp;
}