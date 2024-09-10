_WCRTLINK int unlock( int hid, unsigned long offset, unsigned long nbytes )
{
    __handle_check( hid, -1 );

    if( !UnlockFile( __getOSHandle( hid ), offset, 0L, nbytes, 0L ) ) {
        return( __set_errno_nt() );
    }
    return( 0 );
}