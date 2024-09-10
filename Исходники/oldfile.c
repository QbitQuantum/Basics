char *FindOld( char *name )
{
    char        temp[_MAX_PATH];
    int         retcode;

    _splitpath( name, drive, dir, fname, ext );
    _makepath( temp, "", "", fname, ext );
    retcode = 1;
    #if defined( INSTALL_PROGRAM )
    {
        retcode = SecondaryPatchSearch( name, path );
    }
    #endif
    if( retcode && path[0] == '\0' ) {
        _searchenv( temp, "PATH", path );
    }
    if( path[ 0 ] == '\0' ) {
        FilePatchError( ERR_CANT_OPEN, temp );
        return( NULL );
    }
    return( path );
}