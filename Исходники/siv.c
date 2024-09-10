static inline void aes_encrypt_n(__m128i *text, int num_blocks,
                                 __m128i *keys)
{
    int i, j;

    for(j = 1; j < 10 ; j++) {
        for(i = 0; i< num_blocks; i++) {
            text[i] = _mm_aesenc_si128(text[i], keys[j]);
        }
    }

    for(i = 0; i < num_blocks; i++) {
        text[i] = _mm_aesenclast_si128(text[i], keys[j]);
    }
}