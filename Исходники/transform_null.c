static int transop_decode_null( ntvl_trans_op_t * arg,
                                uint8_t * outbuf,
                                size_t out_len,
                                const uint8_t * inbuf,
                                size_t in_len ) {
    int retval = -1;

    traceEvent( TRACE_DEBUG, "decode_null %lu", in_len );
    if ( out_len >= in_len ) {
        memcpy( outbuf, inbuf, in_len );
        retval = in_len;
    } else traceEvent( TRACE_DEBUG, "decode_null %lu too big for packet buffer", in_len );        

    return retval;
}