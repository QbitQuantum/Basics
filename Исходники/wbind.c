void FindExtender( char *extname, char *winext )
{
    char        *watcom;

    _searchenv( extname, "PATH", winext );
    if( winext[0] == '\0' ) {
        watcom = getenv( "WATCOM" );
        if( watcom != NULL ) {
            strcpy( winext, watcom );
#if defined( __UNIX__ )
            strcat( winext, "/binw/" );
#else
            strcat( winext, "\\binw\\" );
#endif
            strcat( winext, extname );
            if( access( winext, R_OK ) == -1 ) {
                winext[0] = '\0';               // indicate file not found
            }
        }
        if( winext[0] == '\0' ) {
            doError( "Could not find \"%s\" in your path", extname );
        }
    }
}