static int openUnicodeFile( char *filename )
{
    int fh;
    char fullpath[ _MAX_PATH ];

#if defined(__QNX__)
    _searchenv( filename, "ETC_PATH", fullpath );
    if( fullpath[0] == '\0' ) {
        #define ETC "/usr/watcom"
        strcpy( fullpath, ETC );
        strcpy( &fullpath[ sizeof( ETC ) - 1 ], filename );
    }
#else
    _searchenv( filename, "PATH", fullpath );
#endif
    fh = -1;
    if( fullpath[0] != '\0' ) {
        fh = open( fullpath, O_RDONLY | O_BINARY );
    }
    return( fh );
}