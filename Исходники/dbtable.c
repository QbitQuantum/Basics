RcStatus OpenTable( char *fname, char *path )
{
    WResFileID  handle;
    RcStatus    ret;

    ret = RS_OK;
    _searchenv( fname, "PATH", path );
    if( path[0] == '\0' )
        return( RS_FILE_NOT_FOUND );
    handle = RCOPEN( path, O_RDONLY | O_BINARY, PMODE_RW );
    if( handle == NIL_HANDLE ) {
        ret = RS_OPEN_ERROR;
    }
    if( ret == RS_OK )
        ret = readDBHeader( handle );
    if( ret == RS_OK )
        ret = readDBRanges( handle );
    if( ret == RS_OK )
        ret = readDBIndex( handle );
    if( ret == RS_OK )
        ret = readDBTable( handle );
    if( ret != RS_OPEN_ERROR )
        RCCLOSE( handle );
    if( ret == RS_OK ) {
        ConvToUnicode = DBStringToUnicode;
    }
    return( ret );
}