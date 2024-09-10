void hcache_done()
{
    FILE       * f;
    HCACHEDATA * c;
    int          header_count = 0;
    const char * hcachename;
    int          maxage;

    if ( !hcachehash )
        return;

    if ( !( hcachename = cache_name() ) )
        goto cleanup;

    if ( !( f = fopen( hcachename, "wb" ) ) )
        goto cleanup;

    maxage = cache_maxage();

    /* Print out the version. */
    write_netstring( f, CACHE_FILE_VERSION );

    c = hcachelist;
    for ( c = hcachelist; c; c = c->next )
    {
        LISTITER iter;
        LISTITER end;
        char time_secs_str[ 30 ];
        char time_nsecs_str[ 30 ];
        char age_str[ 30 ];
        char includes_count_str[ 30 ];
        char hdrscan_count_str[ 30 ];

        if ( maxage == 0 )
            c->age = 0;
        else if ( c->age > maxage )
            continue;

        sprintf( includes_count_str, "%lu", (long unsigned)list_length(
            c->includes ) );
        sprintf( hdrscan_count_str, "%lu", (long unsigned)list_length(
            c->hdrscan ) );
        sprintf( time_secs_str, "%lu", (long unsigned)c->time.secs );
        sprintf( time_nsecs_str, "%lu", (long unsigned)c->time.nsecs );
        sprintf( age_str, "%lu", (long unsigned)c->age );

        write_netstring( f, CACHE_RECORD_HEADER );
        write_netstring( f, object_str( c->boundname ) );
        write_netstring( f, time_secs_str );
        write_netstring( f, time_nsecs_str );
        write_netstring( f, age_str );
        write_netstring( f, includes_count_str );
        for ( iter = list_begin( c->includes ), end = list_end( c->includes );
            iter != end; iter = list_next( iter ) )
            write_netstring( f, object_str( list_item( iter ) ) );
        write_netstring( f, hdrscan_count_str );
        for ( iter = list_begin( c->hdrscan ), end = list_end( c->hdrscan );
            iter != end; iter = list_next( iter ) )
            write_netstring( f, object_str( list_item( iter ) ) );
        fputs( "\n", f );
        ++header_count;
    }
    write_netstring( f, CACHE_RECORD_END );

    if ( DEBUG_HEADER )
        printf( "hcache written to %s.   %d dependencies, %.0f%% hit rate\n",
            hcachename, header_count, queries ? 100.0 * hits / queries : 0 );

    fclose ( f );

cleanup:
    for ( c = hcachelist; c; c = c->next )
    {
        list_free( c->includes );
        list_free( c->hdrscan );
        object_free( c->boundname );
    }

    hcachelist = 0;
    if ( hcachehash )
        hashdone( hcachehash );
    hcachehash = 0;
}