static FILE *OpenUnicodeFile( const char *filename )
{
    FILE        *fp;
    char        fullpath[_MAX_PATH];

#if defined(__QNX__)
    _searchenv( filename, "ETC_PATH", fullpath );
    if( fullpath[0] == '\0' ) {
        #define ETC "/etc/"
        memcpy( fullpath, ETC, sizeof( ETC ) - 1 );
        strcpy( fullpath + sizeof( ETC ) - 1, filename );
    }
#else
    _searchenv( filename, "PATH", fullpath );
#endif
    fp = NULL;
    if( fullpath[0] != '\0' ) {
        fp = fopen( fullpath, "r" );
    }
    return( fp );
}