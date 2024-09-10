void MemFini( void )
{
#ifdef TRMEM
    MemTrackFini();
#elif defined( __WATCOMC__ )

    struct _heapinfo    h_info;
    int                 status;
    char                buf[50];
    char                *end;

    if( getenv( "TRMEMFILE" ) == NULL )
        return;
    h_info._pentry = NULL;
    for( ;; ) {
        status = _heapwalk( &h_info );
        if( status != _HEAPOK )
            break;
#ifndef NDEBUG
        if( h_info._useflag == _USEDENTRY ) {
            end = Format( buf, "%s block",
                h_info._useflag == _USEDENTRY ? "Used" : "Free" );
            WriteText( STD_OUT, buf, end - buf );
        }
#endif
    }
    switch( status ) {
    case _HEAPBADBEGIN:
        end = Format( buf, Heap_Corupt, "bad header info" );
        WriteText( STD_OUT, buf, end - buf );
        break;
    case _HEAPBADPTR:
        end = Format( buf, Heap_Corupt, "bad pointer" );
        WriteText( STD_OUT, buf, end - buf );
        break;
    case _HEAPBADNODE:
        end = Format( buf, Heap_Corupt, "bad node" );
        WriteText( STD_OUT, buf, end - buf );
        break;
    default:
        break;
    }
#endif
}