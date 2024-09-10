pch_absorb PCHeaderAbsorb( char *include_file )
/*********************************************/
{
    pch_absorb ret;
    int status;
    auto jmp_buf restore_state;
#ifndef NDEBUG
    clock_t start;
    clock_t stop;

    start = clock();
#endif
    if( ErrCount != 0 ) {
        return( PCHA_ERRORS_PRESENT );
    }
    if( CompFlags.fhw_switch_used ) {
        return( PCHA_IGNORE );
    }
    pchFile = sopen3( PCHFileName(), O_RDONLY | O_BINARY, SH_DENYWR );
    if( pchFile == -1 ) {
        return( PCHA_NOT_PRESENT );
    }
    ioBuffer = CMemAlloc( IO_BUFFER_SIZE );
    pch_buff_eob = ioBuffer + IO_BUFFER_SIZE;
    pch_buff_cur = pch_buff_eob;
    ret = PCHA_OK;
    abortData = &restore_state;
    status = setjmp( restore_state );
    if( status == 0 ) {
        if( initialRead() == 0 ) {
            ret = PCHA_NOT_PRESENT;
        } else {
            auto precompiled_header_header header;
#ifdef OPT_BR
            unsigned long br_posn;
#endif

            PCHReadVar( header );
#ifdef OPT_BR
            br_posn = header.browse_info;
#endif
            if( headerIsOK( &header ) ) {
                if( ! stalePCH( include_file ) ) {
                    execInitFunctions( FALSE );
                    execControlFunctions( FALSE, readFunctions );
                    execFiniFunctions( FALSE );
#ifdef OPT_BR
                    if( 0 != br_posn ) {
                        BrinfPchRead();
                    }
#endif
                } else {
                    ret = PCHA_STALE;
                }
            } else {
                pchWarn( WARN_PCH_CONTENTS_HEADER_ERROR );
                ret = PCHA_HEADER;
            }
        }
    } else {
        CErr1( ERR_PCH_READ_ERROR );
    }
    abortData = NULL;
    CMemFreePtr( &ioBuffer );
    close( pchFile );
    if( CompFlags.pch_debug_info_opt && ret == PCHA_OK ) {
        CompFlags.pch_debug_info_read = TRUE;
    }
#ifndef NDEBUG
    stop = clock();
    printf( "%u ticks to load pre-compiled header\n", (unsigned)( stop - start ) );
#endif
    return( ret );
}