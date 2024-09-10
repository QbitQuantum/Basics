/* should return 0 on success, 1 on detected virus, -1 on error */
int check_data( struct mem_chunk *root ) {

    struct mem_chunk *next = root;

    char *buf, *p;
    size_t total = 0;
    int rc = 0;

    if ( no_check )
        return 0;

    while ( next != NULL && next->b != NULL ) {
        total += next->size + 2;
        next = next->next;
    }
    debug( "total data for check: %d", total );

    if ( total == 0 ) {
        error("check_data: zero data");
        return 0;
    }

    buf = malloc( total );
    
    if ( buf == NULL ) {
        Perror( "malloc");
        return 0;
    }
    
    p = buf;
    next = root;
    while ( next != NULL && next->b != NULL ) {
        strncpy( p, next->b, next->size );
        p += next->size;
        strncpy( p, "\r\n", 2);
        p += 2;
        next = next->next;
    }

    rc = dw_scan( buf, total );
    free( buf );
    return rc;
}