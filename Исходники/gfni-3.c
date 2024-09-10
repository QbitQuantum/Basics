void extern
avx512vl_test (void)
{
    x3 = _mm256_gf2p8affineinv_epi64_epi8(x3, x4, 3);
    x5 = _mm_gf2p8affineinv_epi64_epi8(x5, x6, 3);
    x3 = _mm256_gf2p8affine_epi64_epi8(x3, x4, 3);
    x5 = _mm_gf2p8affine_epi64_epi8(x5, x6, 3);
    x3 = _mm256_gf2p8mul_epi8(x3, x4);
    x5 = _mm_gf2p8mul_epi8(x5, x6);
}