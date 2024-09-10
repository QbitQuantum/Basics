static int cmp_all (void *binary, int count)
{
#ifdef _OPENMP
    int i;

    for (i = 0; i < count; i++)
        if (((uint32_t *) binary)[0] == crypt_key[0][i])
             return 1;
    return 0;
#else
    static const __m128i zero = {0};

    __m128i tmp;
    __m128i bin;
    __m128i digest;

    digest = _mm_load_si128 ((__m128i *) crypt_key[0]);
    bin    = _mm_set1_epi32 (((uint32_t *) binary)[0]);
    tmp    = _mm_cmpeq_epi32 (bin, digest);

    return _mm_movemask_epi8 (_mm_cmpeq_epi32 (tmp, zero)) != 0xffff;
#endif
}