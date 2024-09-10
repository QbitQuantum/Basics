static inline void hyperloglog_count_avx2(const uint8_t *registers,
                                          uint32_t n_registers,
                                          float *inverse_sum, uint32_t *n_zeros)
{
  const __m256i ones = (__m256i)_mm256_set1_ps(1.0f);
  __m256 agg = _mm256_set1_ps(0.0f);

  for (size_t i = 0; i < n_registers / sizeof(__m256i); ++i) {
    const __m256i simd = _mm256_load_si256((__m256i *)registers + i);
    /* For some reason, VPSRLDQ works on lane of 128bits instead of 256. */
    const __m128i low = _mm256_extracti128_si256(simd, 0);
    const __m128i high = _mm256_extracti128_si256(simd, 1);

    __m256i sums = inverse_power_avx2(low);
    agg = _mm256_add_ps(agg, (__m256)sums);

    sums = inverse_power_avx2(_mm_srli_si128(low, 8));
    agg = _mm256_add_ps(agg, (__m256)sums);

    sums = inverse_power_avx2(high);
    agg = _mm256_add_ps(agg, (__m256)sums);

    sums = inverse_power_avx2(_mm_srli_si128(high, 8));
    agg = _mm256_add_ps(agg, (__m256)sums);

    *n_zeros += _mm256_cntz_epi8(simd);
  }

  *inverse_sum = horizontal_sum_avx2(agg);
}