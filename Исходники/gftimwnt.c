_WCRTLINK unsigned _dos_getftime( int hid, unsigned *date, unsigned *time )
{
    FILETIME        ctime, atime, wtime;
    unsigned short  d, t;

    if( GetFileTime( __getOSHandle( hid ), &ctime, &atime, &wtime ) ) {
        __MakeDOSDT( &wtime, &d, &t );
        *date = d;
        *time = t;
        return( 0 );
    }
    return( __set_errno_nt_reterr() );
}