static int wrap_gzclose( int fd )
{
    if ( !gzHandles.contains( fd )) return -1;
    int result = gzclose( gzHandles[ fd ] );
    gzHandles.remove( fd );
    return result;
}