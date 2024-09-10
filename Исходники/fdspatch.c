int action_convert ( const class_t* cls,
                     byte_t* buf,
                     size_t len,
                     const char* fn )
{
    char * tmpfn = NULL,
         * tmpdir,
         * fncpy;
    FILE* tmpfh;
    size_t fnlen, wlen;

    if ( cls->has_hdr )
        return 0;

    fnlen = strlen ( fn );
    if ( ! ( fncpy = ( char * ) malloc ( fnlen + 1 ) ) )
        abort ( );
    memcpy ( fncpy, fn, fnlen + 1 );

    printf ( "Patching %s ", fn );
    PROGRESS_STEP

    memmove ( buf + HDR_SIZE, buf, len );
    memcpy ( buf, cls->num_dsk == 2 ? header_2d : header_1d, HDR_SIZE );
    len += HDR_SIZE;
    PROGRESS_STEP

    if ( ! ( tmpdir = dirname ( fncpy ) ) )
        PROGRESS_FAIL2( "Failed to get dir name of %s\n", fn );
    PROGRESS_STEP

    if ( ! ( tmpfn = tempnam ( tmpdir, "FP" ) ) )
        PROGRESS_FAIL1( "Failed to create temp file name\n" )
    PROGRESS_STEP

    if ( ! ( tmpfh = fopen ( tmpfn, "wb" ) ) )
        PROGRESS_FAIL2( "Failed to open temp file %s\n", tmpfn )
    PROGRESS_STEP

    if ( ( wlen = fwrite ( buf, 1, len, tmpfh ) ) != len )
        PROGRESS_FAIL2( "Failed to write to temp file %s\n", tmpfn )
    PROGRESS_STEP

    if ( fclose ( tmpfh ) )
        PROGRESS_FAIL2( "Failed to close temp file %s\n", tmpfn );
    PROGRESS_STEP

    if ( unlink ( fn ) )
        PROGRESS_FAIL2( "Failed to remove original %s\n", fn );
    PROGRESS_STEP

    if ( rename ( tmpfn, fn ) )
        PROGRESS_FAIL2( "Failed to copy temp file %s over original\n",
                        tmpfn );
    printf ( "OK\n" );
    return 0;

fail:
    if ( tmpfn )
        unlink ( tmpfn );
    return 1;
}