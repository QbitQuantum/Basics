static walk_result FindTheMad( mad_handle mh, void *d )
{
    struct find_mad     *fd = d;
    char                buff[80];
//    char                *p;

    MADNameFile( mh, buff, sizeof( buff ) );
//    p = SkipPathInfo( buff, 0 );
    SkipPathInfo( buff, 0 );
    if( memicmp( buff, fd->name, fd->len ) == 0 ) {
        fd->mad = mh;
        return( WR_STOP );
    }
    MADNameDescription( mh, buff, sizeof( buff ) );
    NormalizeString( buff );
    if( memicmp( buff, fd->name, fd->len ) == 0 ) {
        fd->mad = mh;
        return( WR_STOP );
    }
    return( WR_CONTINUE );
}