void __CommonTerm( void )
{
    struct _heapinfo    hinfo;
    void _WCNEAR        *moffs;

    /* Run the normal termination first. */
    (*__int23_exit)();
    __FiniRtns( FINI_PRIORITY_EXIT, 255 );
    (*__int23_exit)();
    __FiniRtns( 0, FINI_PRIORITY_EXIT-1 );
    /* Now try to free "forgotten" memory. */
    hinfo._pentry = NULL;
    for( ;; ) {
        if( _heapwalk( &hinfo ) != _HEAPOK )
            break;
        if( hinfo._useflag ) {
            moffs = (void _WCNEAR *)FP_OFF( hinfo._pentry );
            free( (char *)moffs + sizeof( void * ) );
        }
    }
    /* Return freed memory back to the OS. */
    _heapshrink();
}