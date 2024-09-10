void dumpheap( void )
{
#if 0
    struct _heapinfo h;
    int         status;

    h._pentry = NULL;
    for( ;; ) {
        status = _heapwalk( &h );
        if( status != _HEAPOK )
            break;
        printf( "%s block at %Fp of size %4.4X\r\n",
                (h._useflag == _USEDENTRY ? "USED": "FREE"),
                h._pentry, h._size );
    }
    switch( status ) {
    case _HEAPEND:
        printf( "OK - end of heap\r\n" );
        break;
    case _HEAPEMPTY:
        printf( "OK - heap is empty\r\n" );
        break;
    case _HEAPBADBEGIN:
        printf( "ERROR - heap is damaged\r\n" );
        break;
    case _HEAPBADPTR:
        printf( "ERROR - bad pointer to heap\r\n" );
        break;
    case _HEAPBADNODE:
        printf( "ERROR - bad node in heap\r\n" );
        break;
    }
#endif
}