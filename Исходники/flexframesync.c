// decode header
void flexframesync_decode_header(flexframesync _q)
{
#if DEMOD_HEADER_SOFT
    // soft decoding operates on 'header_mod' array directly;
    // no need to pack bits
#else
    // pack 256 1-bit header symbols into 32 8-bit bytes
    unsigned int num_written;
    liquid_pack_bytes(_q->header_mod, FLEXFRAME_H_SYM,
                      _q->header_enc, FLEXFRAME_H_ENC,
                      &num_written);
    assert(num_written==FLEXFRAME_H_ENC);
#endif 

#if DEBUG_FLEXFRAMESYNC_PRINT
    unsigned int i;
    // print header (encoded)
    printf("header rx (enc) : ");
    for (i=0; i<FLEXFRAME_H_ENC; i++)
        printf("%.2X ", _q->header_enc[i]);
    printf("\n");
#endif

    // unscramble header and run packet decoder
#if DEMOD_HEADER_SOFT
    // soft demodulation operates on header_mod directly
    unscramble_data_soft(_q->header_mod, FLEXFRAME_H_ENC);
    _q->header_valid =
    packetizer_decode_soft(_q->p_header, _q->header_mod, _q->header);
#else
    unscramble_data(_q->header_enc, FLEXFRAME_H_ENC);
    _q->header_valid =
    packetizer_decode(_q->p_header, _q->header_enc, _q->header);
#endif

    // return if header is invalid
    if (!_q->header_valid)
        return;

    // first several bytes of header are user-defined
    unsigned int n = FLEXFRAME_H_USER;

    // first byte is for expansion/version validation
    if (_q->header[n+0] != FLEXFRAME_VERSION) {
        fprintf(stderr,"warning: flexframesync_decode_header(), invalid framing version\n");
        _q->header_valid = 0;
        return;
    }

    // strip off payload length
    unsigned int payload_dec_len = (_q->header[n+1] << 8) | (_q->header[n+2]);
    _q->payload_dec_len = payload_dec_len;

    // strip off modulation scheme/depth
    unsigned int mod_scheme = _q->header[n+3];

    // strip off CRC, forward error-correction schemes
    //  CRC     : most-significant 3 bits of [n+4]
    //  fec0    : least-significant 5 bits of [n+4]
    //  fec1    : least-significant 5 bits of [n+5]
    unsigned int check = (_q->header[n+4] >> 5 ) & 0x07;
    unsigned int fec0  = (_q->header[n+4]      ) & 0x1f;
    unsigned int fec1  = (_q->header[n+5]      ) & 0x1f;

    // validate properties
    if (mod_scheme == 0 || mod_scheme >= LIQUID_MODEM_NUM_SCHEMES) {
        fprintf(stderr,"warning: flexframesync_decode_header(), invalid modulation scheme\n");
        _q->header_valid = 0;
        return;
    }
    if (check >= LIQUID_CRC_NUM_SCHEMES) {
        fprintf(stderr,"warning: flexframesync_decode_header(), decoded CRC exceeds available\n");
        _q->header_valid = 0;
        return;
    }
    if (fec0 >= LIQUID_FEC_NUM_SCHEMES) {
        fprintf(stderr,"warning: flexframesync_decode_header(), decoded FEC (inner) exceeds available\n");
        _q->header_valid = 0;
        return;
    }
    if (fec1 >= LIQUID_FEC_NUM_SCHEMES) {
        fprintf(stderr,"warning: flexframesync_decode_header(), decoded FEC (outer) exceeds available\n");
        _q->header_valid = 0;
        return;
    }

    // configure payload receiver
    if (_q->header_valid) {
        // recreate modem
        _q->ms_payload    = mod_scheme;
        _q->bps_payload   = modulation_types[mod_scheme].bps;
        _q->demod_payload = modem_recreate(_q->demod_payload, _q->ms_payload);

        // set new packetizer properties
        _q->check  = check;
        _q->fec0   = fec0;
        _q->fec1   = fec1;

        // recreate packetizer object
        _q->p_payload = packetizer_recreate(_q->p_payload,
                                            _q->payload_dec_len,
                                            _q->check,
                                            _q->fec0,
                                            _q->fec1);

        // re-compute payload encoded message length
        _q->payload_enc_len = packetizer_get_enc_msg_len(_q->p_payload);

        // re-compute number of modulated payload symbols
        div_t d = div(8*_q->payload_enc_len, _q->bps_payload);
        _q->payload_mod_len = d.quot + (d.rem ? 1 : 0);
        
        // re-allocate buffers accordingly
        // (give encoded a few extra bytes to compensate for repacking)
        _q->payload_mod = (unsigned char*) realloc(_q->payload_mod, (_q->payload_mod_len  )*sizeof(unsigned char));
        _q->payload_enc = (unsigned char*) realloc(_q->payload_enc, (_q->payload_enc_len+8)*sizeof(unsigned char));
        _q->payload_dec = (unsigned char*) realloc(_q->payload_dec, (_q->payload_dec_len  )*sizeof(unsigned char));

        if (_q->payload_mod == NULL || _q->payload_enc == NULL || _q->payload_dec == NULL) {
            fprintf(stderr,"error: flexframesync_decode_header(), could not re-allocate payload arrays\n");
            _q->header_valid = 0;
            return;
        }
    }
    
#if DEBUG_FLEXFRAMESYNC_PRINT
    // print results
    printf("flexframesync_decode_header():\n");
    printf("    header crc      : %s\n", _q->header_valid ? "pass" : "FAIL");
    printf("    check           : %s\n", crc_scheme_str[check][1]);
    printf("    fec (inner)     : %s\n", fec_scheme_str[fec0][1]);
    printf("    fec (outer)     : %s\n", fec_scheme_str[fec1][1]);
    printf("    mod scheme      : %s\n", modulation_types[mod_scheme].name);
    printf("    payload dec len : %u\n", _q->payload_dec_len);
    printf("    payload enc len : %u\n", _q->payload_enc_len);
    printf("    payload mod len : %u\n", _q->payload_mod_len);

    printf("    user data       :");
    for (i=0; i<FLEXFRAME_H_USER; i++)
        printf(" %.2x", _q->header[i]);
    printf("\n");
#endif
}