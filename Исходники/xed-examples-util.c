xed_uint_t disas_decode_encode_binary(const xed_state_t* dstate,
                                      const xed_uint8_t* decode_text_binary,
                                      const unsigned int bytes,
                                      xed_decoded_inst_t* xedd, 
                                      xed_uint64_t runtime_address)   {
    // decode then encode
    unsigned int retval_olen = 0;
    // decode it...
    xed_bool_t decode_okay =  disas_decode_binary(dstate, decode_text_binary,
                                                  bytes, xedd, 
                                                  runtime_address);
    if (decode_okay)     {
        xed_error_enum_t encode_okay;
        unsigned int enc_olen, ilen = XED_MAX_INSTRUCTION_BYTES;
        xed_uint8_t array[XED_MAX_INSTRUCTION_BYTES];
        // they are basically the same now
        xed_encoder_request_t* enc_req = xedd; 
        // convert decode structure to proper encode structure
        xed_encoder_request_init_from_decode(xedd);
        
        // encode it again...
        encode_okay =  xed_encode(enc_req, array, ilen, &enc_olen);
        if (encode_okay != XED_ERROR_NONE) {
            if (CLIENT_VERBOSE) {
                char buf[XED_TMP_BUF_LEN];
                char buf2[XED_TMP_BUF_LEN];
                int blen=XED_TMP_BUF_LEN;
                xed_encode_request_print(enc_req, buf, XED_TMP_BUF_LEN);
                blen = xed_strncpy(buf2,"Could not re-encode: ", blen);
                blen = xed_strncat(buf2, buf, blen);
                blen = xed_strncat(buf2,"\nError code was: ",blen);
                blen = xed_strncat(buf2,
                                   xed_error_enum_t2str(encode_okay),blen);
                blen = xed_strncat(buf2, "\n",blen);
                xedex_dwarn(buf2);
            }
        }
        else         {
            retval_olen = enc_olen;
            // See if it matched the original...
            if (CLIENT_VERBOSE) {
                char buf[XED_HEX_BUFLEN];
                xed_uint_t dec_length; 
                xed_print_hex_line(buf,array, enc_olen, XED_HEX_BUFLEN);
                printf("Encodable! %s\n",buf);
                dec_length = xed_decoded_inst_get_length(xedd);
                if ((enc_olen != dec_length ||
                     memcmp(decode_text_binary, array, enc_olen)  )) {
                    char buf2[XED_TMP_BUF_LEN];
                    char buf3[XED_TMP_BUF_LEN];
                    printf("Discrepenacy after re-encoding. dec_len= " 
                           XED_FMT_U " ", dec_length);
                    xed_print_hex_line(buf, decode_text_binary, 
                                       dec_length,XED_HEX_BUFLEN);
                    printf("[%s] ", buf);
                    printf("enc_olen= " XED_FMT_U "", enc_olen);
                    xed_print_hex_line(buf, array, enc_olen, XED_HEX_BUFLEN);
                    printf(" [%s] ", buf);
                    printf("for instruction: ");
                    xed_decoded_inst_dump(xedd, buf3,XED_TMP_BUF_LEN);
                    printf("%s\n", buf3);
                    printf("vs Encode  request: ");
                    xed_encode_request_print(enc_req, buf2, XED_TMP_BUF_LEN);
                    printf("%s\n", buf2);
                }
                else 
                    printf("Identical re-encoding\n");
            }
        }
    }
    return retval_olen;
}