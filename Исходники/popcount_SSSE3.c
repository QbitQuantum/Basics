/**
 * Count the number of bits set within the intersection of two
 * fingerprints using the SSSE3 instruction set.
 * @warning  1) fp1 & fp2 must be aligned to 16 byte boundaries.
 *           2) Use (get_cpuid_flags() & bit_SSSE3) from cpuid.h to
 *              test if the CPU supports the SSSE3 instructions.
 */
int chemfp_intersect_popcount_SSSE3(int size, const unsigned *fp1, const unsigned *fp2) {
#if defined(GENERATE_SSSE3)
  /* 2^5 loop iters might overflow 8-bit counter,
     so cap it at 2^4 iters per chunk */
  const int iters = 1 << 4;
  const int N = (size + 3) / 4;
  int i, count;
  __m128i count32 = _mm_setzero_si128();
  for (i = 0; i + iters * 4 <= N; i += iters * 4) {
    count32 = _mm_add_epi32(count32, intersect_popcount_SSSE3_helper(&fp1[i], &fp2[i], iters));
  }
  if (i < N) {
    count32 = _mm_add_epi32(count32, intersect_popcount_SSSE3_helper(&fp1[i], &fp2[i], (N - i + 3) / 4));
  }
  /* Layout coming from PSADBW accumulation is 2*{0,32}: 0 S1 0 S0 */
  count = _mm_cvt_ss2si(_mm_cvtepi32_ps(_mm_add_epi32(
     count32, _mm_shuffle_epi32(count32, _MM_SHUFFLE(2, 2, 2, 2)))));
  return count;
#else
  UNUSED(size);
  UNUSED(fp1);
  UNUSED(fp2);
  return 0;
#endif
}