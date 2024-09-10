int norx_aead_decrypt(
    unsigned char *m, size_t *mlen,
    const unsigned char *a, size_t alen,
    const unsigned char *c, size_t clen,
    const unsigned char *z, size_t zlen,
    const unsigned char *nonce,
    const unsigned char *key
    )
{
    const __m256i K = LOADU(key);
    __m256i A, B, C, D;

    if (clen < BYTES(NORX_T)) { return -1; }

    *mlen = clen - BYTES(NORX_T);

    INITIALISE(A, B, C, D, nonce, K);
    ABSORB_DATA(A, B, C, D, a, alen, HEADER_TAG);
    DECRYPT_DATA(A, B, C, D, m, c, clen - BYTES(NORX_T));
    ABSORB_DATA(A, B, C, D, z, zlen, TRAILER_TAG);
    FINALISE(A, B, C, D, K);

    /* Verify tag */
    D = _mm256_cmpeq_epi8(D, LOADU(c + clen - BYTES(NORX_T)));
    return (((_mm256_movemask_epi8(D) & 0xFFFFFFFFULL) + 1) >> 32) - 1;
}