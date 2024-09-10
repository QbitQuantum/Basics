static int heap_size( struct heap_stat *stat ) {
    struct _heapinfo h_info;
    int heap_status;
    h_info._pentry = NULL;
    stat->free = 0;
    stat->used = 0;
    for( ; (heap_status = _heapwalk( &h_info )) == _HEAPOK; ) {
        if( h_info._useflag == _USEDENTRY ) {
            stat->used += h_info._size;
        } else {
            stat->free += h_info._size;
        }
    }
    return( heap_status );
}