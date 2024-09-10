static void NOINLINE transposeX8( const __m256 *v1, __m256 *vout )
{
#if 0 // AVX1
    __m256 a0 = _mm256_unpacklo_ps( v1[ 0 ], v1[ 1 ] );
    __m256 a1 = _mm256_unpackhi_ps( v1[ 0 ], v1[ 1 ] );
    __m256 b0 = _mm256_permute2f128_ps( a0, a1, _MM_SHUFFLE( 0, 2, 0, 0 ) );
    __m256 b1 = _mm256_permute2f128_ps( a0, a1, _MM_SHUFFLE( 0, 3, 0, 1 ) );
    __m256 c0 = _mm256_unpacklo_ps( b0, b1 );
    __m256 c1 = _mm256_unpackhi_ps( b0, b1 );
    vout[ 0 ] = _mm256_permute2f128_ps( c0, c1, _MM_SHUFFLE( 0, 2, 0, 0 ) );
    vout[ 1 ] = _mm256_permute2f128_ps( c0, c1, _MM_SHUFFLE( 0, 3, 0, 1 ) );
#else // AVX2
    static const int ALIGN32 p1[ 8 ] = { 0, 4, 2, 6, 1, 5, 3, 7 };
    static const int ALIGN32 p2[ 8 ] = { 2, 6, 0, 4, 3, 7, 1, 5 };
    const __m256i perm1 = _mm256_load_si256( reinterpret_cast< const __m256i* >( p1 ) );
    const __m256i perm2 = _mm256_load_si256( reinterpret_cast< const __m256i* >( p2 ) );
    __m256 a0 = _mm256_permutevar8x32_ps( v1[ 0 ], perm1 );
    __m256 a1 = _mm256_permutevar8x32_ps( v1[ 1 ], perm2 );
    vout[ 0 ] = _mm256_blend_ps( a0, a1, 0xCC );
    vout[ 1 ] = _mm256_shuffle_ps( a0, a1, 0x4E );
#endif
}