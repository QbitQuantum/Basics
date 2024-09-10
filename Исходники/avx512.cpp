int main(int, char**argv)
{
    /* AVX512 Foundation */
    __m512i i;
    __m512d d;
    __m512 f;
    __mmask16 m = ~1;
    i = _mm512_maskz_loadu_epi32(0, argv);
    d = _mm512_loadu_pd((double *)argv + 64);
    f = _mm512_loadu_ps((float *)argv + 128);

#ifdef __AVX512ER__
    /* AVX512 Exponential and Reciprocal */
    f =  _mm512_exp2a23_round_ps(f, 8);
#endif
#ifdef __AVX512CD__
    /* AVX512 Conflict Detection */
    i = _mm512_maskz_conflict_epi32(m, i);
#endif
#ifdef __AVX512PF__
    /* AVX512 Prefetch */
    _mm512_mask_prefetch_i64scatter_pd(argv, 0xf, i, 2, 2);
#endif
#ifdef __AVX512DQ__
    /* AVX512 Doubleword and Quadword support */
    m = _mm512_movepi32_mask(i);
#endif
#ifdef __AVX512BW__
    /* AVX512 Byte and Word support */
    i =  _mm512_mask_loadu_epi8(i, m, argv - 8);
#endif
#ifdef __AVX512VL__
    /* AVX512 Vector Length */
    __m256i i2 = _mm256_maskz_loadu_epi32(0, argv);
    _mm256_mask_storeu_epi32(argv + 1, m, i2);
#endif
#ifdef __AVX512IFMA__
    /* AVX512 Integer Fused Multiply-Add */
    i = _mm512_madd52lo_epu64(i, i, i);
#endif
#ifdef __AVX512VBMI__
    /* AVX512 Vector Byte Manipulation Instructions */
    i = _mm512_permutexvar_epi8(i, i);
#endif

    _mm512_mask_storeu_epi64(argv, m, i);
    _mm512_mask_storeu_ps(argv + 64, m, f);
    _mm512_mask_storeu_pd(argv + 128, m, d);
    return 0;
}