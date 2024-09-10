/** The twofish packet format consists of:
 *
 *  - a 8-bit twofish encoding version in clear text
 *  - a 32-bit SA number in clear text
 *  - ciphertext encrypted from a 32-bit nonce followed by the payload.
 *
 *  [V|SSSS|nnnnDDDDDDDDDDDDDDDDDDDDD]
 *         |<------ encrypted ------>|
 */
static int transop_encode_twofish( ntvl_trans_op_t * arg,
                                   uint8_t * outbuf,
                                   size_t out_len,
                                   const uint8_t * inbuf,
                                   size_t in_len ) {
    int len=-1;
    transop_tf_t * priv = (transop_tf_t *)arg->priv;
    uint8_t assembly[NTVL_PKT_BUF_SIZE];
    uint32_t * pnonce;

    if ( (in_len + TRANSOP_TF_NONCE_SIZE) <= NTVL_PKT_BUF_SIZE ) {
        if ( (in_len + TRANSOP_TF_NONCE_SIZE + TRANSOP_TF_SA_SIZE + TRANSOP_TF_VER_SIZE) <= out_len ) {
            size_t idx=0;
            sa_twofish_t * sa;
            size_t tx_sa_num = 0;

            /* The transmit sa is periodically updated */
            tx_sa_num = tf_choose_tx_sa( priv );

            sa = &(priv->sa[tx_sa_num]); /* Proper Tx SA index */

            traceEvent( TRACE_DEBUG, "encode_twofish %lu with SA %lu.", in_len, sa->sa_id );

            /* Encode the twofish format version. */
            encode_uint8( outbuf, &idx, NTVL_TWOFISH_TRANSFORM_VERSION );

            /* Encode the security association (SA) number */
            encode_uint32( outbuf, &idx, sa->sa_id );

            /* The assembly buffer is a source for encrypting data. The nonce is
             * written in first followed by the packet payload. The whole
             * contents of assembly are encrypted. */
            pnonce = (uint32_t *)assembly;
            *pnonce = rand();
            memcpy( assembly + TRANSOP_TF_NONCE_SIZE, inbuf, in_len );

            /* Encrypt the assembly contents and write the ciphertext after the SA. */
            len = TwoFishEncryptRaw( assembly, /* source */
                                     outbuf + TRANSOP_TF_VER_SIZE + TRANSOP_TF_SA_SIZE,
                                     in_len + TRANSOP_TF_NONCE_SIZE, /* enc size */
                                     sa->enc_tf);
            if ( len > 0 ) len += TRANSOP_TF_VER_SIZE + TRANSOP_TF_SA_SIZE; /* size of data carried in UDP. */
            else traceEvent( TRACE_ERROR, "encode_twofish encryption failed." );
        } else traceEvent( TRACE_ERROR, "encode_twofish outbuf too small." );
    } else traceEvent( TRACE_ERROR, "encode_twofish inbuf too big to encrypt." );

    return len;
}