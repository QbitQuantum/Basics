void extern
avx2_test (void)
{
    x = _mm256_cmpgt_epi32 (x, x);
}