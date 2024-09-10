/**
 * salsa20_8(B):
 * Apply the salsa20/8 core to the provided block.
 */
static void salsa20_8(__m128i B[4]) {
    __m128i X0, X1, X2, X3;
    __m128i T;
    size_t i;

    X0 = B[0];
    X1 = B[1];
    X2 = B[2];
    X3 = B[3];

    for (i = 0; i < 8; i += 2) {
        /* Operate on "columns". */
        T = _mm_add_epi32(X0, X3);
        X1 = _mm_xor_si128(X1, _mm_slli_epi32(T, 7));
        X1 = _mm_xor_si128(X1, _mm_srli_epi32(T, 25));
        T = _mm_add_epi32(X1, X0);
        X2 = _mm_xor_si128(X2, _mm_slli_epi32(T, 9));
        X2 = _mm_xor_si128(X2, _mm_srli_epi32(T, 23));
        T = _mm_add_epi32(X2, X1);
        X3 = _mm_xor_si128(X3, _mm_slli_epi32(T, 13));
        X3 = _mm_xor_si128(X3, _mm_srli_epi32(T, 19));
        T = _mm_add_epi32(X3, X2);
        X0 = _mm_xor_si128(X0, _mm_slli_epi32(T, 18));
        X0 = _mm_xor_si128(X0, _mm_srli_epi32(T, 14));

        /* Rearrange data. */
        X1 = _mm_shuffle_epi32(X1, 0x93);
        X2 = _mm_shuffle_epi32(X2, 0x4E);
        X3 = _mm_shuffle_epi32(X3, 0x39);

        /* Operate on "rows". */
        T = _mm_add_epi32(X0, X1);
        X3 = _mm_xor_si128(X3, _mm_slli_epi32(T, 7));
        X3 = _mm_xor_si128(X3, _mm_srli_epi32(T, 25));
        T = _mm_add_epi32(X3, X0);
        X2 = _mm_xor_si128(X2, _mm_slli_epi32(T, 9));
        X2 = _mm_xor_si128(X2, _mm_srli_epi32(T, 23));
        T = _mm_add_epi32(X2, X3);
        X1 = _mm_xor_si128(X1, _mm_slli_epi32(T, 13));
        X1 = _mm_xor_si128(X1, _mm_srli_epi32(T, 19));
        T = _mm_add_epi32(X1, X2);
        X0 = _mm_xor_si128(X0, _mm_slli_epi32(T, 18));
        X0 = _mm_xor_si128(X0, _mm_srli_epi32(T, 14));

        /* Rearrange data. */
        X1 = _mm_shuffle_epi32(X1, 0x39);
        X2 = _mm_shuffle_epi32(X2, 0x4E);
        X3 = _mm_shuffle_epi32(X3, 0x93);
    }

    B[0] = _mm_add_epi32(B[0], X0);
    B[1] = _mm_add_epi32(B[1], X1);
    B[2] = _mm_add_epi32(B[2], X2);
    B[3] = _mm_add_epi32(B[3], X3);
}