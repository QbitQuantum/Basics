static unsigned int sad32x32(const uint8_t *src_ptr, int src_stride,
                             const uint8_t *ref_ptr, int ref_stride) {
  __m256i s1, s2, r1, r2;
  __m256i sum = _mm256_setzero_si256();
  __m128i sum_i128;
  int i;

  for (i = 0; i < 16; ++i) {
    r1 = _mm256_loadu_si256((__m256i const *)ref_ptr);
    r2 = _mm256_loadu_si256((__m256i const *)(ref_ptr + ref_stride));
    s1 = _mm256_sad_epu8(r1, _mm256_loadu_si256((__m256i const *)src_ptr));
    s2 = _mm256_sad_epu8(
        r2, _mm256_loadu_si256((__m256i const *)(src_ptr + src_stride)));
    sum = _mm256_add_epi32(sum, _mm256_add_epi32(s1, s2));
    ref_ptr += ref_stride << 1;
    src_ptr += src_stride << 1;
  }

  sum = _mm256_add_epi32(sum, _mm256_srli_si256(sum, 8));
  sum_i128 = _mm_add_epi32(_mm256_extracti128_si256(sum, 1),
                           _mm256_castsi256_si128(sum));
  return _mm_cvtsi128_si32(sum_i128);
}