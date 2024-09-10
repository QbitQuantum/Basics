/*
 * GetFromEnv - get file name from environment
 */
static void GetFromEnv( char *what, char *path )
{
    _searchenv( what, "EDPATH", path );
    if( path[0] != 0 ) {
        return;
    }
    _searchenv( what, "PATH", path );

} /* GetFromEnv */