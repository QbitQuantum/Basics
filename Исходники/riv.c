int decrypt_final(riv_context_t* ctx, 
                  const unsigned char* ciphertext,
                  const unsigned long long ciphertext_length, 
                  const unsigned char* header,
                  const unsigned long long header_length, 
                  const unsigned char tag[TAGLEN], 
                  unsigned char* plaintext)
{
    ALIGN(16) uint8_t iv[TAGLEN];
    ALIGN(16) uint8_t iv_prime[TAGLEN];

    clhash(&(ctx->prf_context), 
        header, header_length, DOMAIN_1, ciphertext, ciphertext_length, iv);

    cdms(iv, iv, ctx->expanded_key);
    xor_bytes(iv, iv, tag, TAGLEN);

    cdms(iv_prime, iv, ctx->expanded_key);
    sct_mode(ctx, iv_prime, (const __m128i*)ciphertext, 
        ciphertext_length, (__m128i*)plaintext);
    
    clhash(&(ctx->prf_context), 
        header, header_length, DOMAIN_0, plaintext, ciphertext_length, iv_prime);

    cdms(iv_prime, iv_prime, ctx->expanded_key);
    return (_mm_testc_si128(load(iv), load(iv_prime)) - 1)
        | (_mm_testc_si128(load((iv+BLOCKLEN)), load((iv_prime+BLOCKLEN))) - 1);
}