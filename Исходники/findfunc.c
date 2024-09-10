static int get_dev_func( void )
{
    char    *   end         = NULL;
    int         i;
    size_t      position;
    size_t      scanned;
    size_t      unscanned;
    
    if( cur_file->scanptr == NULL ) {

        /* First call: start by getting data into the buffer. */

        cur_file->usedlen = fread( cur_file->filebuf, 1, \
                                            cur_file->buflen, cur_file->fp );
        if( ferror( cur_file->fp ) ) return( FAILURE );
        if( cur_file->usedlen == 0 ) return( FAILURE );

        cur_file->scanptr = cur_file->filebuf;
    }

    /* Initialize the output values to clear any old data. */

    cur_token->start = NULL;
    cur_token->count = 0;

    for( ;; ) {        

        /* Find the next device function name. */

        position = cur_file->scanptr - cur_file->filebuf;
        for( i = 0; i < cur_file->usedlen - position; i++ ){
            if( *cur_file->scanptr == '%' ) break;
            cur_file->scanptr++;
        }

        if( *cur_file->scanptr == '%' ) {

            /* cur_file->scanptr points to the start of a device
             * function name.
             */

            cur_token->start = cur_file->scanptr;

            /* Find the length of the device function name. */

            end = cur_token->start;
            position = cur_file->scanptr - cur_file->filebuf;
            for( i = 0; i < cur_file->usedlen - position; i++ ){
                if( *end == '(' ) break;
                end++;
            }

            if( *end == '(' ) {

            /* end points to one position beyond the end of the name. */

                cur_file->scanptr = end;
                cur_token->count = end - cur_token->start;
                break;
            }

            if( feof( cur_file->fp ) ) return( FAILURE );

            /* If we get here, we ran out of data before finding the end of
             * the device function name: reset the buffer to start with the
             * start of the device function name and read more data in.
             */

            scanned = cur_token->start - cur_file->filebuf;
            unscanned = &cur_file->filebuf[cur_file->usedlen] - \
                                                            cur_token->start;
            memmove_s( cur_file->filebuf, cur_file->buflen, \
                                                cur_token->start, unscanned );

            cur_file->usedlen = fread( &cur_file->filebuf[ unscanned ], 1, \
                                cur_file->buflen - unscanned, cur_file->fp );
            cur_file->usedlen += unscanned;
            if( ferror( cur_file->fp ) ) return( FAILURE );
            if( cur_file->usedlen == 0 ) return( FAILURE );

            cur_file->scanptr = cur_file->filebuf;
            continue;
        }

        if( feof( cur_file->fp ) ) return( FAILURE );

        /* If we get here, then we ran out of buffer before finding the start
         * of a device function name: replace the entire buffer.
         */

        cur_file->usedlen = fread( cur_file->filebuf, 1, \
                                            cur_file->buflen, cur_file->fp );
        if( ferror( cur_file->fp ) ) return( FAILURE );
        if( cur_file->usedlen == 0 ) return( FAILURE );

        cur_file->scanptr = cur_file->filebuf;
    }
    
    return( SUCCESS ) ;
}